#include "mm/page.h"
#include "kernel/kernel.h"
extern char __free_ram[], __free_ram_end[];

paddr_t alloc_pages(size_t num_pages)
{
    static paddr_t next_page_addr = (paddr_t) __free_ram; // Start of free memory
    paddr_t paddr = next_page_addr;
    next_page_addr += num_pages * PAGE_SIZE;

    if(next_page_addr > (paddr_t) __free_ram_end) {
        PANIC("Out of memory: cannot allocate %u pages\n", num_pages);
    }
    memset((void *) paddr, 0, num_pages * PAGE_SIZE); // Clear allocated pages
    return paddr;
}