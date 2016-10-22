#ifndef __BLOCK_ALLOC_H__
#define __BLOCK_ALLOC_H__

#include <stdint.h>
#include "buddy_alloc.h"

struct block_desc
{
    struct block_desc *next;
};

struct block_allocator_ctl
{
    struct block_desc *head;
    uint16_t block_size;
};

struct block_allocator_ctl* create_block_allocator(uint16_t block_size);
void* alloc_block(struct block_allocator_ctl* allocator);
void free_block(void* ptr);

#endif
