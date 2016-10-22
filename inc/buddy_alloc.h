#ifndef __BUDDY_ALLOC_H__
#define __BUDDY_ALLOC_H__

#include "memory.h"
#include <stdint.h>

struct buddy_page_desc
{
    uint64_t next;
    uint64_t prev;
    uint8_t level;
    uint8_t free;
    uint8_t height;
} __attribute__((packed));

extern struct buddy_page_desc *descriptors;

void init_buddy(void);
uint64_t find_buddy(uint8_t level);
void occupy_buddy(uint64_t page_id, uint8_t level);
uint64_t alloc_buddy(uint8_t level);
void free_buddy(uint64_t page_ptr);

#endif
