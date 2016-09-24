#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include <stdint.h>

#define NUM_HANDLERS 256

#define MASTER_COMMAND_PORT 0x20
#define MASTER_DATA_PORT 0x21
#define SLAVE_COMMAND_PORT 0xA0
#define SLAVE_DATA_PORT 0xA1

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

void mask_devices_slave(unsigned char mask);
void mask_devices_master(unsigned char mask);
void unmask_devices_slave(unsigned char mask);
void unmask_devices_master(unsigned char mask);

void init_pic();

void init_interrupt();

void add_idt_entry(int index, uint64_t entry);

void send_eoi(unsigned short port);

void common_handler(uint64_t interrupt_id);

#endif
