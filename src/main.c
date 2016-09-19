#include "serial.h"
#include "io.h"
 
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
    printf("Hello, world! %%\nThis is a printf test\nint: %d\nunsigned long long: %llu\noct: %o\nhex: %x\nstring: %s\nint min: %d\nshort min: %hd\nlong min: %ld\nlong long min: %lld\n", -117, 1000000000000000000ULL, 117, 117, "test string", -2147483648U, -32768, -9223372036854775808ULL, -9223372036854775808ULL);
	while (1);
} 
