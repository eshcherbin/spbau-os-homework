#include "serial.h"
#include "io.h"
#include "interrupt.h"
#include "timer.h"
#include "backtrace.h"
#include "memmap.h"
#include "buddy_alloc.h"
#include "paging.h"
#include "block_alloc.h"
#include "mem_alloc.h"
 
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
    init_paging();
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
    /*void* page_addr_0 = (void*) alloc_buddy(0);
    printf("%llx\n", page_addr_0);
    void* page_addr_1 = (void*) alloc_buddy(0);
    printf("%llx\n", page_addr_1);
    free_buddy((uint64_t) page_addr_0);
    page_addr_0 = (void*) alloc_buddy(5);
    printf("%llx\n", page_addr_0);
    free_buddy((uint64_t) page_addr_0);
    page_addr_0 = (void*) alloc_buddy(5);
    printf("%llx\n", page_addr_0);
    free_buddy((uint64_t) page_addr_0);
    free_buddy((uint64_t) page_addr_1);
    page_addr_0 = (void*) alloc_buddy(1);
    printf("%llx\n", page_addr_0);*/

    // block allocator test
    struct block_allocator_ctl *ctl_0 = create_block_allocator(PAGE_SIZE / 8);
    for (int i = 0; i < 11; i++)
    {
        void *addr = alloc_block(ctl_0);
        printf("0: %llx\n", addr);
    }
    struct block_allocator_ctl *ctl_1 = create_block_allocator(PAGE_SIZE);
    for (int i = 0; i < 11; i++)
    {
        void *addr = alloc_block(ctl_1);
        printf("1: %llx\n", addr);
    }

    // malloc test
    void *page_addr_2 = malloc(10 * sizeof(int));
    printf("%llx\n", page_addr_2);
    void *page_addr_3 = malloc(100 * sizeof(int));
    printf("%llx\n", page_addr_3);
    free(page_addr_3);
    page_addr_3 = malloc(100 * sizeof(int));
    printf("%llx\n", page_addr_3);
    free(page_addr_3);
    void *page_addr_4 = malloc(10117 * sizeof(int));
    printf("%llx\n", page_addr_4);
    free(page_addr_4);
    page_addr_4 = malloc(100117 * sizeof(int));
    printf("%llx\n", page_addr_4);
    free(page_addr_4);

    while (1);
}
