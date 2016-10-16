#ifndef __MEMMAP_H__
#define __MEMMAP_H__

#include <stdint.h>

#define MEMMAP_TYPE_KERNEL    0
#define MEMMAP_TYPE_AVAILABLE 1
#define MEMMAP_TYPE_RESERVED  2
#define MEMMAP_TYPE_ALLOC     3
#define MAX_MEMMAP_TABLE_LENGTH 64

struct memmap_entry
{
    uint64_t addr;
    uint64_t len;
    uint32_t type;
} __attribute__((packed));

extern uint32_t memmap_table_length;
extern struct memmap_entry memmap_table[];

void read_memmap(void);
void print_memmap(void);

#endif
