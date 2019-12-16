#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "covert_channel.h"
#include "util.h"

#define SIZE 131072 // 32*4096
// #define DEBUG

// A secret value that cannot be logically read from other processes
static const char key[] = "PassWord";


// send key[index] by using page cache side channel
void send_data(const int index) {
	char c = key[index];

	// send data singal
	if (c & (1 << 0)) {
		func_0();
	}
	if (c & (1 << 1)) {
		func_1();
	}
	if (c & (1 << 2)) {
		func_2();
	}
	if (c & (1 << 3)) {
		func_3();
	}
	if (c & (1 << 4)) {
		func_4();
	}
	if (c & (1 << 5)) {
		func_5();
	}
	if (c & (1 << 6)) {
		func_6();
	}
	if (c & (1 << 7)) {
		func_7();
	}
}


// wait ready signal
void wait() {
	while (1) {
		if (check_state(func_ready)) {
			break;
		}
		sleep(1);
	}
}


// evict page cache by reading huge file
void evict() {
#ifdef DEBUG
		debug_print();
#endif

	FILE *file = fopen("file", "r");
	fseek(file, 0, SEEK_END);
	long fsize = ftell(file);
	fseek(file, 0, SEEK_SET);

	char* buf = malloc(SIZE * sizeof(char));

	off_t chunk = 0;
	int    flag = 0;
	while (chunk < fsize) {
		if (cache_count() == 0) {
			flag = 1;
			break;
		}
		fread(buf, sizeof(char), SIZE, file); // first read
		fseek(file, -SIZE, SEEK_CUR);
		fread(buf, sizeof(char), SIZE, file); // second read
		chunk += SIZE;
	}

	if (!flag) {
		printf("Failed to evict page cache\n");
		debug_print();
		exit(0);
	}

	free(buf);
	fclose(file);
}


int main(void) {
	printf("Sender process\n");

	for (int i = 0; i < sizeof(key) / sizeof(char); i++) {
		printf("ecicting page cache ...\n");
		evict();

		printf("sending %dth character ...\n", i + 1);
		// send data to reciver
		send_data(i);

		// send valid signal to reciver
		if (i % 2 == 0) {
			func_valid0();
		} else {
			func_valid1();
		}

		// send last signal to reciver
		if (i == (sizeof(key) / sizeof(char) - 1)) {
			func_last();
		}

		// wait ready signal from receiver
		wait();
	}
	return 0;
}
