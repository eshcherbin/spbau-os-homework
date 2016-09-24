#include "serial.h"
#include "io.h"
#include "interrupt.h"
#include "timer.h"
 
static void qemu_gdb_hang(void)
{
#ifdef DEBUG
	static volatile int wait = 1;

	while (wait);
#endif
}

void init()
{
    init_serial_port();
    init_interrupt();
}

void main(void)
{
	qemu_gdb_hang();

    init();

    // printf test
    printf("Hello, world! %%\nThis is a printf test\nint: %d\n", -117);
    printf("unsigned long long: %llu\noct: %o\nhex: %x\nstring: %s\n", 1000000000000000000ULL, 117, 117, "test string");
    printf("int min: %d\nshort min: %hd\nlong min: %ld\nlong long min: %lld\n",
            -2147483648U, -32768, -9223372036854775808ULL, -9223372036854775808ULL);
    puts("\n\n");

    // interrupt test
    __asm__ volatile("int $225");

    start_timer();

	while (1);
} 
