#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <assert.h>
#include <covert_channel.h>

int check_state(void* addr) {
	size_t page_size = sysconf(_SC_PAGESIZE);
	unsigned char vec[1] = {0};
	int res = mincore(addr, page_size, vec);
	assert(res == 0);
	return vec[0] & 1;
}

void print_states(void* addr, int size) {
	size_t page_size = sysconf(_SC_PAGESIZE);
	unsigned char* vec = calloc(size, sizeof(unsigned char));
	int res = mincore(addr, page_size * size, vec);
	assert(res == 0);
	for (int i = 0; i < size; i++) {
		printf("%d ", vec[i] & 1);
	}
	printf("\n");
}

void debug_print() {
	printf("----------------------------------------------\n");
	printf("func_valid0: "); print_states(func_valid0, 16);
	printf("func_valid1: "); print_states(func_valid1, 16);
	printf("func_ready:  "); print_states(func_ready,  16);
	printf("func_last:   "); print_states(func_last,   16);
	printf("func_func0:  "); print_states(func_0, 16);
	printf("func_func1:  "); print_states(func_1, 16);
	printf("func_func2:  "); print_states(func_2, 16);
	printf("func_func3:  "); print_states(func_3, 16);
	printf("func_func4:  "); print_states(func_4, 16);
	printf("func_func5:  "); print_states(func_5, 16);
	printf("func_func6:  "); print_states(func_6, 16);
	printf("func_func7:  "); print_states(func_7, 16);
	printf("----------------------------------------------\n");
}

// calculate the number of functions in the page cache
int cache_count() {
	int count = 0;
	count += check_state(func_valid0);
	count += check_state(func_valid1);
	count += check_state(func_ready);
	count += check_state(func_last);
	count += check_state(func_0);
	count += check_state(func_1);
	count += check_state(func_2);
	count += check_state(func_3);
	count += check_state(func_4);
	count += check_state(func_5);
	count += check_state(func_6);
	count += check_state(func_7);
	return count;
}
