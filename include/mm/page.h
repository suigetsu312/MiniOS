#ifndef PAGE_H
#define PAGE_H

#include "lib/types.h"

#define PAGE_SIZE 4096

paddr_t alloc_pages(size_t num_pages);


#endif /* PAGE_H */
