#include "buddy_alloc.h"
#include "memmap.h"
#include "io.h"
#include <limits.h>
#include "utils.h"

#define BUDDY_ID(id, level) ((id) ^ (1 << (level)))

uint8_t num_levels;
extern uint64_t* level_heads;
struct buddy_page_desc *descriptors;

void delete_from_list(uint32_t page_id, uint8_t level)
{
    if (descriptors[page_id].next != page_id)
    {
        descriptors[descriptors[page_id].next].prev = descriptors[page_id].prev;
        descriptors[descriptors[page_id].prev].next = descriptors[page_id].next;
        level_heads[level] = descriptors[page_id].next;
        descriptors[page_id].next = page_id;
        descriptors[page_id].prev = page_id;
    }
    else
        level_heads[level] = ULLONG_MAX;
}

void add_to_list(uint32_t page_id, uint8_t level)
{
    if (level_heads[level] != ULLONG_MAX)
    {
        descriptors[page_id].next = level_heads[level];
        descriptors[page_id].prev = descriptors[level_heads[level]].prev;
        descriptors[descriptors[page_id].next].prev = page_id;
        descriptors[descriptors[page_id].prev].next = page_id;
    }
    level_heads[level] = page_id;
}

void init_buddy(void)
{
    num_levels = 0;

    uint64_t total_pages = mem_size / PAGE_SIZE;
    for (uint32_t i = 0; i < memmap_table_length; i++)
    {
        if (memmap_table[i].type != MEMMAP_TYPE_AVAILABLE)
            continue;
        if (memmap_table[i].len >= total_pages * sizeof(struct buddy_page_desc))
        {
            descriptors = (struct buddy_page_desc*) memmap_table[i].addr;
            memmap_table_length++;
            memmap_table[memmap_table_length - 1].type = MEMMAP_TYPE_KERNEL;
            memmap_table[memmap_table_length - 1].len = total_pages * sizeof(struct buddy_page_desc);
            memmap_table[memmap_table_length - 1].addr = memmap_table[i].addr;
            memmap_table[i].len -= total_pages * sizeof(struct buddy_page_desc);
            memmap_table[i].addr += total_pages * sizeof(struct buddy_page_desc);
            break;
        }
    }

    uint64_t num_pages = 0;

    for (uint32_t i = 0; i < memmap_table_length; i++)
    {
        if (memmap_table[i].type != MEMMAP_TYPE_AVAILABLE)
            continue;
        uint64_t pm_l = memmap_table[i].addr;
        uint64_t pm_r = pm_l + memmap_table[i].len;
        // align to PAGE_SIZE
        if (pm_l % PAGE_SIZE)
            pm_l += (PAGE_SIZE - pm_l % PAGE_SIZE);
        pm_r -= pm_r % PAGE_SIZE;
        if (pm_r <= pm_l)
            continue;
        memmap_table[i].type = MEMMAP_TYPE_ALLOC;

        num_pages += (pm_r - pm_l) / PAGE_SIZE;

        for (uint8_t j = 0; (1ULL << j) * PAGE_SIZE <= mem_size; j++)
            level_heads[j] = ULLONG_MAX;
        while (pm_l < pm_r)
        {
            uint8_t height = 0;
            uint64_t page_id = pm_l / PAGE_SIZE;
            while (pm_l + PAGE_SIZE * (1ULL << (height + 1)) <= pm_r && BUDDY_ID(page_id, height) >= page_id)
                height++;
            if (num_levels < height + 1)
                num_levels = height + 1;
            uint64_t stop_id = page_id + (1ULL << height);
            while (page_id < stop_id)
            {
                descriptors[page_id].next = page_id;
                descriptors[page_id].prev = page_id;
                descriptors[page_id].level = height;
                descriptors[page_id].free = 0;
                descriptors[page_id].height = UCHAR_MAX;
                page_id++;
            }
            page_id = pm_l / PAGE_SIZE;
            descriptors[page_id].height = height;
            free_buddy(pm_l);
            pm_l += PAGE_SIZE * (1ULL << height);
        }
    }

    printf("Buddy allocator initialized with %lld pages\n", num_pages);
}

uint64_t find_buddy(uint8_t level)
{
    while (level < num_levels && level_heads[level] == ULLONG_MAX)
        level++;
    if (level >= num_levels)
        return ULLONG_MAX;
    return level_heads[level];
}

void occupy_buddy(uint64_t page_id, uint8_t level)
{
    while (level < descriptors[page_id].level)
    {
        //split
        delete_from_list(page_id, descriptors[page_id].level);
        descriptors[page_id].level--;
        descriptors[BUDDY_ID(page_id, descriptors[page_id].level)].free = 1;
        descriptors[BUDDY_ID(page_id, descriptors[page_id].level)].level = descriptors[page_id].level;
        add_to_list(page_id, descriptors[page_id].level);
        add_to_list(BUDDY_ID(page_id, descriptors[page_id].level), descriptors[page_id].level);
    }
    descriptors[page_id].free = 0;
    delete_from_list(page_id, level);
}

uint64_t alloc_buddy(uint8_t level)
{
    uint64_t page_id = find_buddy(level);
    if (page_id == ULLONG_MAX)
        return 0;
    occupy_buddy(page_id, level);
    return (uint64_t) page_id * PAGE_SIZE;
}

void free_buddy(uint64_t page_ptr)
{
    uint64_t page_id = page_ptr / PAGE_SIZE;
    descriptors[page_id].free = 1;
    while (descriptors[page_id].level < descriptors[page_id].height &&
            descriptors[BUDDY_ID(page_id, descriptors[page_id].level)].free)
    {
        //merge
        uint64_t buddy_id = BUDDY_ID(page_id, descriptors[page_id].level);
        delete_from_list(buddy_id, descriptors[buddy_id].level);
        if (page_id > buddy_id)
        {
            uint64_t tmp = page_id;
            page_id = buddy_id;
            buddy_id = tmp;
        }
        descriptors[buddy_id].free = 0;
        descriptors[page_id].level++;
    }
    add_to_list(page_id, descriptors[page_id].level);
}
