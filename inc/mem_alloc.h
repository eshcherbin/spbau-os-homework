#ifndef __MEM_ALLOC_H__
#define __MEM_ALLOC_H__

#include <stdint.h>
#include <stddef.h>

void* malloc(size_t size);
void free(void* ptr);

#endif
