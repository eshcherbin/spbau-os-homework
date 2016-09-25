#include "backtrace.h"
#include "io.h"

static uint64_t *main_frame_address;

void init_backtrace(uint64_t *main_frame_address_)
{
    main_frame_address = main_frame_address_;
}

void print_backtrace()
{
    printf("Stack trace:\n");
    int counter = 0;
    uint64_t* current_frame_address = (uint64_t*) __builtin_frame_address(0);
    while (current_frame_address != main_frame_address)
    {
        printf("(%d)  %llx%s in\n", counter, *(current_frame_address + 1), (counter == 0) ? " (current)" : ""); // return address is 8(%rbp)
        current_frame_address = (uint64_t*) *current_frame_address;
        counter++;
    }
    printf("(%d)  %llx (main)\n", counter, *(main_frame_address + 1));
}
