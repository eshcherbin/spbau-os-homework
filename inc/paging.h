#ifndef __PAGING_H__
#define __PAGING_H__

#include <stdint.h>
#include "memory.h"

void init_paging(void);
void map_large_page(uint64_t phys_addr, uint64_t virt_addr);

#endif
