#ifndef __UTILS_H__
#define __UTILS_H__

#include "memory.h"
#include <stdint.h>

#define BIT(n) (1 << (n))

uint64_t virt_addr(uint64_t p);
uint64_t phys_addr(uint64_t p);

#endif
