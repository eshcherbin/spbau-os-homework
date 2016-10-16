#include "utils.h"

uint64_t virt_addr(uint64_t p) { return p + SHIFTED_BASE; }
uint64_t phys_addr(uint64_t p) { return p - SHIFTED_BASE; }
