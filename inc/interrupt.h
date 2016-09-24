#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <stdint.h>

struct idt_entry
{
    uint16_t offset_1;
    uint16_t segsel;
    uint16_t spec;
    uint16_t offset_2;
    uint32_t offset_3;
    uint32_t reserved;
} __attribute__((packed));

void init_idt();

void init_interrupt();

void common_handler(uint64_t interrupt_id);

void add_idt_entry(int index, uint64_t entry);

#endif
