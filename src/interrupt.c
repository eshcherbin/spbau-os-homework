#include "interrupt.h"
#include "memory.h"
#include "utils.h"
#include "io.h"
#include "ioport.h"
#include "desc.h"
#include "ints.h"

static struct idt_entry idt[256];

extern uint64_t interrupt_handlers[];

void init_idt()
{
    for (int i = 0; i < NUM_HANDLERS; i++)
        add_idt_entry(i, interrupt_handlers[i]);
    struct desc_table_ptr idtr;
    idtr.addr = (uint64_t) idt;
    idtr.size = sizeof(idt) - 1;
    write_idtr(&idtr);
}

static unsigned char current_mask_slave = 0,
                     current_mask_master = 0;
void mask_devices_slave(unsigned char mask)
{
    current_mask_slave |= mask;
    out8(SLAVE_DATA_PORT, current_mask_slave);
}
void mask_devices_master(unsigned char mask)
{
    current_mask_master |= mask;
    out8(MASTER_DATA_PORT, current_mask_slave);
}
void unmask_devices_slave(unsigned char mask)
{
    current_mask_slave &= (0xff ^ mask);
    out8(SLAVE_DATA_PORT, current_mask_slave);
}
void unmask_devices_master(unsigned char mask)
{
    current_mask_master &= (0xff ^ mask);
    out8(MASTER_DATA_PORT, current_mask_master);
}

void init_pic()
{
    disable_ints();

    out8(MASTER_COMMAND_PORT, BIT(0) | BIT(4));
    out8(MASTER_DATA_PORT, 32);
    out8(MASTER_DATA_PORT, BIT(2));
    out8(MASTER_DATA_PORT, BIT(0));
    
    out8(SLAVE_COMMAND_PORT, BIT(0) | BIT(4));
    out8(SLAVE_DATA_PORT, 117);
    out8(SLAVE_DATA_PORT, 2);
    out8(SLAVE_DATA_PORT, BIT(0));

    mask_devices_slave(0xff);
    mask_devices_master(0xff);
    unmask_devices_master(BIT(2));

    enable_ints();
}

void init_interrupt()
{
    init_idt();
    init_pic();
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

void send_eoi(unsigned short port)
{
    out8(port, BIT(5));
}

void common_handler(uint64_t interrupt_id)
{
    printf("Interrupt %llu\n", interrupt_id);

    // Master EOI
    if (32 <= interrupt_id && interrupt_id < 40)
        send_eoi(MASTER_COMMAND_PORT);

    // Slave EOI
    if (117 <= interrupt_id && interrupt_id < 125)
    {
        send_eoi(MASTER_COMMAND_PORT);
        send_eoi(SLAVE_COMMAND_PORT);
    }
}
