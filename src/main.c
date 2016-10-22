#include "serial.h"
#include "io.h"
#include "interrupt.h"
#include "timer.h"
#include "backtrace.h"
#include "memmap.h"
#include "buddy_alloc.h"
 
static void qemu_gdb_hang(void)
{
#ifdef DEBUG
	static volatile int wait = 1;

	while (wait);
#endif
}

void init(void)
{
    init_serial_port();
    init_interrupt();
    read_memmap();
    init_buddy();
}

void main(void)
{
	qemu_gdb_hang();

    init_backtrace((uint64_t*) __builtin_frame_address(0));
    init();

    // printf test
    /*printf("Hello, world! %%\nThis is a printf test\nint: %d\n", -117);
    printf("unsigned long long: %llu\noct: %o\nhex: %x\nstring: %s\n", 1000000000000000000ULL, 117, 117, "test string");
    printf("int min: %d\nshort min: %hd\nlong min: %ld\nlong long min: %lld\n",
            -2147483648U, -32768, -9223372036854775808ULL, -9223372036854775808ULL);
    puts("\n\n");*/

    // interrupt test
    //__asm__ volatile("int $225");

    // backtrace test
    //print_backtrace();

    //start_timer();
    print_memmap();

    // buddy test
    void* page_addr_0 = (void*) alloc_buddy(0);
    printf("%llx\n", page_addr_0);
    void* page_addr_1 = (void*) alloc_buddy(0);
    printf("%llx\n", page_addr_1);
    free_buddy(page_addr_0);
    page_addr_0 = (void*) alloc_buddy(1);
    printf("%llx\n", page_addr_0);
    free_buddy(page_addr_0);
    free_buddy(page_addr_1);
    page_addr_0 = (void*) alloc_buddy(1);
    printf("%llx\n", page_addr_0);

    while (1);
}
