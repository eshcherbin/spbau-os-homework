#include "serial.h"
#include "io.h"
#include "interrupt.h"
 
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
    /*printf("Hello, world! %%\nThis is a printf test\nint: %d\n", -117);
    printf("unsigned long long: %llu\noct: %o\nhex: %x\nstring: %s\n", 1000000000000000000ULL, 117, 117, "test string");
    printf("int min: %d\nshort min: %hd\nlong min: %ld\nlong long min: %lld\n",
            -2147483648U, -32768, -9223372036854775808ULL, -9223372036854775808ULL);
    puts("\n");
    char s[100];
    snprintf(s, 100, "Hello, world! %%\nThis is a snprintf test\nint: %d\n", -117);
    puts(s);
    snprintf(s, 100, "unsigned long long: %llu\noct: %o\nhex: %x\nstring: %s\n", 1000000000000000000ULL, 117, 117, "test string");
    puts(s);
    snprintf(s, 100, "unsigned long long: %llu\noct: %o\nhex: %x\nstring: %s\n", 1000000000000000000ULL, 117, 117, "test string");
    snprintf(s, 100, "int min: %d\nshort min: %hd\nlong min: %ld\nlong long min: %lld\n",
            -2147483648U, -32768, -9223372036854775808ULL, -9223372036854775808ULL);
    puts(s);*/

    __asm__ volatile("int $0");

	while (1);
} 
