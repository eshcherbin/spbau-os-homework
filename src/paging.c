#include "paging.h"
#include "memmap.h"
#include "utils.h"
#include "buddy_alloc.h"

#define NUM_RECORDS (512)
#define PTE_PRESENT	(1 << 0)
#define PTE_WRITE	(1 << 1)
#define PTE_LARGE	(1 << 7)

#define GB (0x40000000)

extern uint64_t* bootstrap_pml4;

uint64_t* pml3_pages[NUM_RECORDS] = {0};

void write_pml3(uint8_t index)
{
    *((uint64_t*) bootstrap_pml4 + index) = (uint64_t) phys_addr((uint64_t) pml3_pages[index]) | PTE_PRESENT | PTE_WRITE;
}

void init_paging(void)
{
    uint32_t gb_to_map = mem_size / GB + (mem_size % GB == 0 ? 0 : 1);
    uint32_t pml3_to_map = gb_to_map / NUM_RECORDS + (gb_to_map % NUM_RECORDS == 0 ? 0 : 1);
    //find memory for pml3 pages in first 4Gb
    for (uint32_t i = 0; i < memmap_table_length; i++)
    {
        if (memmap_table[i].type != MEMMAP_TYPE_AVAILABLE)
            continue;
        uint64_t pm_l = memmap_table[i].addr;
        uint64_t pm_r = pm_l + memmap_table[i].len;
        if (pm_r > 4ULL * GB)
            pm_r = 4ULL * GB;
        if (pm_l % PAGE_SIZE != 0)
            pm_l += PAGE_SIZE - pm_l % PAGE_SIZE;
        if (pm_r <= pm_l)
            continue;
        uint64_t pages = (pm_r - pm_l) / PAGE_SIZE;
        if (pages >= pml3_to_map)
        {
            for (uint32_t j = 0; j < pml3_to_map; j++)
            {
                pml3_pages[j + NUM_RECORDS / 2] = (uint64_t*) virt_addr(pm_l);
                pm_l += PAGE_SIZE;
            }
            memmap_table_length++;
            memmap_table[memmap_table_length - 1].type = MEMMAP_TYPE_KERNEL;
            memmap_table[memmap_table_length - 1].len = pm_l - memmap_table[i].addr;
            memmap_table[memmap_table_length - 1].addr = memmap_table[i].addr;
            memmap_table[i].len -= pm_l - memmap_table[i].addr;
            memmap_table[i].addr = pm_l;
            break;
        }
    }
    for (uint32_t i = 0; i < gb_to_map; i++)
        map_large_page((uint64_t) GB * i, SHIFTED_BASE + ((uint64_t) GB * i));
}

void map_large_page(uint64_t phys_addr, uint64_t virt_addr)
{
    uint32_t gb_index = (virt_addr - (virt_addr < SHIFTED_BASE ? 0 : SHIFTED_BASE)) / GB;
    uint32_t pm3_index = gb_index / NUM_RECORDS + (virt_addr < SHIFTED_BASE ? 0 : NUM_RECORDS / 2);
    ((uint64_t*) (pml3_pages[pm3_index]))[gb_index % NUM_RECORDS] = phys_addr | PTE_WRITE | PTE_PRESENT | PTE_LARGE;
    write_pml3(pm3_index);
}
