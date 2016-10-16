#include "mem_alloc.h"
#include "memmap.h"
#include "io.h"
#include <limits.h>

#define BUDDY_ID(id, level) ((id) ^ (1 << (level)))

uint8_t num_levels;
uint32_t *level_heads;
struct buddy_page_desc *descriptors;

void init_buddy()
{
    // range of physical memory used for allocation
    uint64_t pm_l = ULLONG_MAX;
    uint64_t pm_r = ULLONG_MAX;
    uint32_t memmap_table_index = UINT_MAX;
    
    for (uint32_t i = 0; i < memmap_table_length; i++)
    {
        if (memmap_table[i].type != MEMMAP_TYPE_AVAILABLE)
            continue;
        if (memmap_table_index == UINT_MAX ||
                memmap_table[memmap_table_index].len < memmap_table[i].len)
            memmap_table_index = i;
    }

    if (memmap_table_index == UINT_MAX)
    {
        printf("error: no place for buddy allocator\n");
        return;
    }

    memmap_table[memmap_table_index].type = MEMMAP_TYPE_ALLOC;
    pm_l = memmap_table[memmap_table_index].addr;
    pm_r = pm_l + memmap_table[memmap_table_index].len;
    // align to PAGE_SIZE
    if (pm_l % PAGE_SIZE)
        pm_l += (PAGE_SIZE - pm_l % PAGE_SIZE);
    pm_r -= pm_r % PAGE_SIZE;

    // assume that heads won't occupy more than a 
    pm_r -= PAGE_SIZE;
    level_heads = (uint32_t*) pm_r;

    uint32_t max_pages = (pm_r - pm_l) / (PAGE_SIZE + sizeof(struct buddy_page_desc));
    if (pm_r < pm_l || max_pages == 0)
    {
        printf("error: no place for buddy allocator\n");
        return;
    }
    num_levels = 0;
    while ((1ULL << num_levels) <= max_pages)
        num_levels++;
    uint32_t num_pages = 1ULL << (num_levels - 1);
    pm_r = pm_l + PAGE_SIZE * num_pages;
    descriptors = (struct buddy_page_desc*) pm_r;

    for (uint32_t i = 0; i < num_pages; i++) 
    {
        descriptors[i].next = i;
        descriptors[i].prev = i;
        descriptors[i].level = 0;
        descriptors[i].free = 0;
    }
    descriptors[0].level = num_levels - 1;
    descriptors[0].free = 1;
    for (uint8_t i = 0; i < num_levels; i++)
        level_heads[i] = UINT_MAX;
    level_heads[num_levels - 1] = 0;

    printf("Buddy allocator initialized\n");
    printf("num_levels: %hhu\n", num_levels);
    printf("num_pages: %u\n", num_pages);
}

uint32_t find_buddy(uint8_t level)
{
    while (level < num_levels && level_heads[level] == UINT_MAX)
        level++;
    if (level >= num_levels)
        return UINT_MAX;
    return level_heads[level];
}

void occupy_buddy(uint32_t page_id, uint8_t level)
{

}
