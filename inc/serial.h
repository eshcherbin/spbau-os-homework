#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <stdint.h>

#define SERIAL_PORT(n) (0x3f8 + n)

void init_serial_port();

void putc(char c);

void puts(const char* s);

#endif
