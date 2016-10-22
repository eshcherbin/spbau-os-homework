#include "memmap.h"
#include "io.h"

uint32_t memmap_table_length = 0;
struct memmap_entry memmap_table[MAX_MEMMAP_TABLE_LENGTH];
uint64_t mem_size;

extern uint64_t multiboot_info;
extern uint64_t text_phys_begin;
extern uint64_t bss_phys_end;
extern uint32_t multiboot_header[];

void read_memmap(void)
{
    struct memmap_entry kernel_entry;
    kernel_entry.addr = multiboot_header[4]; // text_phys_begin
    kernel_entry.len = multiboot_header[6] - kernel_entry.addr; // bss_phys_end
    kernel_entry.type = 0;
    memmap_table[memmap_table_length++] = kernel_entry;

    uint32_t memmap_size = *((uint32_t*) ((char*)multiboot_info + 44));
    char *memmap_addr = *((char**) ((char*)multiboot_info + 48));
    while (memmap_size > 0)
    {
        uint32_t size = *((uint32_t*) memmap_addr);
        memmap_addr += sizeof(size);
        struct memmap_entry entry;
        entry.addr = *((uint64_t*) memmap_addr);
        entry.len = *((uint64_t*) (memmap_addr + 8));
        entry.type = *((uint32_t*) (memmap_addr + 16));
        memmap_size -= sizeof(size) + size;
        memmap_addr += size;

        // handle intersection with kernel
        uint64_t kl = kernel_entry.addr, 
                 kr = kl + kernel_entry.len,
                 l = entry.addr,
                 r = l + entry.len;
        if (!((kr <= l) || (r <= kl))) 
        {
            if (kl <= l)
            {
                if (r > kr)
                {
                    entry.addr = kr;
                    entry.len = kr - r;
                }
                else
                    continue;
            }
            else
            {
                entry.len = kl - l;
                if (kr < r)
                {
                    struct memmap_entry new_entry;
                    new_entry.addr = kr;
                    new_entry.len = r - kr;
                    new_entry.type = entry.type;
                    memmap_table[memmap_table_length++] = new_entry;
                }
            }
        }

        memmap_table[memmap_table_length++] = entry;
    }

    for (uint32_t i = 0; i < memmap_table_length; i++)
        if (mem_size < memmap_table[i].addr + memmap_table[i].len)
            mem_size = memmap_table[i].addr + memmap_table[i].len;
}

void print_memmap(void)
{
    for (uint32_t i = 0; i < memmap_table_length; i++) 
    {
        printf("memory range %d: %llx - %llx, type %u, length %llu bytes\n", i, memmap_table[i].addr, 
               memmap_table[i].addr + memmap_table[i].len - 1, memmap_table[i].type, memmap_table[i].len);
    }
}
