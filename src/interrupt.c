#include "interrupt.h"
#include "memory.h"
#include "utils.h"
#include "io.h"
#include "desc.h"
#include "ints.h"

static struct idt_entry idt[256];

#define NUM_HANDLERS 256

extern uint64_t interrupt_handlers[];

void init_idt()
{
    for (int i = 0; i < NUM_HANDLERS; i++)
        add_idt_entry(i, interrupt_handlers[i]);
}

void init_interrupt()
{
    init_idt();
    struct desc_table_ptr idtr;
    idtr.addr = (uint64_t) idt;
    idtr.size = sizeof(idt) - 1;
    write_idtr(&idtr);
}

void add_idt_entry(int index, uint64_t entry)
{
    idt[index].offset_1 = (entry & 0xFFFF);
    idt[index].offset_2 = (((entry) >> 16) & 0xFFFF);
    idt[index].offset_3 = (((entry) >> 32) & 0xFFFFFFFF);
    idt[index].segsel = KERNEL_CS;
    idt[index].spec = BIT(15) | (14 << 8);
    idt[index].reserved = 0;
}

void common_handler(uint64_t interrupt_id)
{
    printf("Hi, i'm interrupt %llu\n", interrupt_id);
}
