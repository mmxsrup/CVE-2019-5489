#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <sys/mman.h>
#include "util.h"
#include "covert_channel.h"


// wait valid0 signal
void wait_valid0() {
	while (1) {
		if (check_state(func_valid0)) {
			break;
		}
		usleep(1000000);
	}
}

// wait valid1 signal
void wait_valid1() {
	while (1) {
		if (check_state(func_valid1)) {
			break;
		}
		usleep(1000000);
	}
}


char read_data() {
#ifdef DEBUG
	debug_print();
#endif
	char data = 0;
	if (check_state(func_0)) {
		data |= (1 << 0);
	}
	if (check_state(func_1)) {
		data |= (1 << 1);
	}
	if (check_state(func_2)) {
		data |= (1 << 2);
	}
	if (check_state(func_3)) {
		data |= (1 << 3);
	}
	if (check_state(func_4)) {
		data |= (1 << 4);
	}
	if (check_state(func_5)) {
		data |= (1 << 5);
	}
	if (check_state(func_6)) {
		data |= (1 << 6);
	}
	if (check_state(func_7)) {
		data |= (1 << 7);
	}
	return data;
}

int main() {
	printf("Sender process\n");

	char buf[256] = {'\0'};
	int index = 0;

	while (1) {
		assert(index < 255);
		printf("waiting ...\n");

		// wait valid signal
		if (index % 2 == 0) {
			wait_valid0();
		} else {
			wait_valid1();
		}

		buf[index] = read_data();
		printf("recved caracter(%c)\n", buf[index]);

		// set ready signal
		func_ready();

		if (check_state(func_last)) { // is last ?
			break;
		}

		index++;
	}

	printf("Received key: %s\n", buf);
	return 0;
}
