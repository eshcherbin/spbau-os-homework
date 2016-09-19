#include "serial.h"
 
static void qemu_gdb_hang(void)
{
#ifdef DEBUG
	static volatile int wait = 1;

	while (wait);
#endif
}

void main(void)
{
	qemu_gdb_hang();
    puts("Hello, world!");
	while (1);
} 
