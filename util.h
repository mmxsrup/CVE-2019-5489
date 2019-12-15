#ifndef UTIL_H
#define UTIL_H

int check_state(void* addr);

void debug_print();

// calculate the number of functions in the page cache
int cache_count();

#endif
