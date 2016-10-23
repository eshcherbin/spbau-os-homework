#include "mem_alloc.h"
#include "buddy_alloc.h"
#include "block_alloc.h"
#include "utils.h"
#include "limits.h"

#define MALLOC_SMALL_SIZE_STEP 8
#define MALLOC_MAX_SMALL_SIZE 256

struct block_allocator_ctl *small_allocators[MALLOC_MAX_SMALL_SIZE / MALLOC_SMALL_SIZE_STEP];

void* malloc(size_t size)
{
    if (!size)
        return 0;
    if (size < MALLOC_MAX_SMALL_SIZE)
    {
        size = (size - 1) / MALLOC_SMALL_SIZE_STEP + 1;
        if (!small_allocators[size - 1])
            small_allocators[size - 1] = create_block_allocator(size * MALLOC_SMALL_SIZE_STEP);
        return alloc_block(small_allocators[size - 1]);
    }
    else
    {
        size += sizeof(size_t);
        if (size % PAGE_SIZE)
            size += PAGE_SIZE - size % PAGE_SIZE;
        uint8_t level = 0;
        while (PAGE_SIZE * (1ULL << (level + 1)) <= size)
            level++;
        uint64_t page_id = find_buddy(level);
        if (page_id == ULLONG_MAX)
            return 0;
        size_t *res = (size_t*) virt_addr(page_id * PAGE_SIZE);
        *res = size;

        level++;
        do
        {
            level--;
            if (size >= PAGE_SIZE * (1 << level))
            {
                size -= PAGE_SIZE * (1 << level);
                occupy_buddy(page_id, level);
                page_id += (1 << level);
            }
        }
        while (level > 0);

        return res + 1;
    }
}

void free(void* ptr)
{
    uint64_t page_id = phys_addr((uint64_t) ptr) / PAGE_SIZE;
    if (descriptors[page_id].block_ctl)
        free_block(ptr);
    else
    {
        size_t size = *((size_t*) ptr - 1);
        while (size)
        {
            size -= PAGE_SIZE * (1 << descriptors[page_id].level);
            uint64_t new_page_id = page_id + (1 << descriptors[page_id].level);
            free_buddy(page_id * PAGE_SIZE);
            page_id = new_page_id;
        }
    }
}
