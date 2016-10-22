#include "block_alloc.h"
#include "memory.h"
#include "utils.h"

#define IS_SMALL(bs) ((bs) * 8 <= PAGE_SIZE)
#define SMALL_LEVEL 0
#define BIG_LEVEL 3

uint64_t allocate_pages(uint16_t block_size, struct block_allocator_ctl **ctl)
{
    uint8_t level = (IS_SMALL(block_size) ? SMALL_LEVEL : BIG_LEVEL);
    uint8_t num_pages = (1 << level);
    uint64_t pages = alloc_buddy(level);
    if (!pages)
        return 0;
    pages = virt_addr(pages);

    char *ptr = (char*) pages;
    char *stop = (char*) (pages + PAGE_SIZE * num_pages - (!*ctl ? sizeof(struct block_allocator_ctl) : 0));
    while (ptr + block_size <= stop)
    {
        ((struct block_desc*) ptr)->next = (struct block_desc*) (ptr + block_size);
        ptr += block_size;
    }
    ((struct block_desc*) (ptr - block_size))->next = 0;

    if (!*ctl)
    {
        *ctl = (struct block_allocator_ctl*) (pages + PAGE_SIZE * num_pages - sizeof(struct block_allocator_ctl));
        (*ctl)->block_size = block_size;
        (*ctl)->head = (struct block_desc*) pages;
    }
    for (uint64_t page_id = phys_addr(pages) / PAGE_SIZE; page_id < phys_addr(pages) / PAGE_SIZE + num_pages; page_id++)
        descriptors[page_id].block_ctl = *ctl;
    (*ctl)->head = (struct block_desc*) pages;

    return pages;
}

struct block_allocator_ctl* create_block_allocator(uint16_t block_size)
{
    if (block_size < sizeof(struct block_desc))
        block_size = sizeof(struct block_desc);
    struct block_allocator_ctl *ctl = 0;
    if (!allocate_pages(block_size, &ctl))
        return 0;
    return ctl;
}

void* alloc_block(struct block_allocator_ctl* ctl)
{
    if (ctl->head == 0 && !allocate_pages(ctl->block_size, &ctl))
        return 0;
    void *res = ctl->head;
    ctl->head = ctl->head->next;
    return res;
}


void free_block(void* ptr)
{
    uint64_t page_id = (uint64_t) phys_addr((uint64_t) ptr) / PAGE_SIZE;
    struct block_allocator_ctl *ctl = descriptors[page_id].block_ctl;
    ((struct block_desc*) ptr)->next = ctl->head;
    ctl->head = ptr;
}
