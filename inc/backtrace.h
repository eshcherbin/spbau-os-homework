#ifndef __BACKTRACE_H__
#define __BACKTRACE_H__

#include <stdint.h>

void init_backtrace(uint64_t *main_frame_address_);
void print_backtrace(void);

#endif
