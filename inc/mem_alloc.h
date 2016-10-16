#ifndef __MEM_ALLOC_H__
#define __MEM_ALLOC_H__

#include "memory.h"
#include <stdint.h>

struct buddy_page_desc
{
    uint32_t next;
    uint32_t prev;
    uint8_t level;
    uint8_t free;
} __attribute__((packed));

void init_buddy();
uint32_t find_buddy(uint8_t level);
void occupy_buddy(uint32_t page_id, uint8_t level);
uint64_t alloc_buddy(uint8_t level);
void free_buddy(void *page_ptr, uint8_t level);

#endif
