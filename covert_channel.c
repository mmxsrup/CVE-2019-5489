#include "covert_channel.h"

#define SIZE 4096 * 64

// The two "valid" signal are used to
// avoid any race conditions in the protocol
// between the transmisison of two subsequent messages.
__attribute__ ((aligned(SIZE))) int func_valid0() { return 0; }
__attribute__ ((aligned(SIZE))) int func_valid1() { return 0; }
__attribute__ ((aligned(SIZE))) int func_ready()  { return 0; }
__attribute__ ((aligned(SIZE))) int func_last()   { return 0; }

__attribute__ ((aligned(SIZE))) int func_0() { return 0; }
__attribute__ ((aligned(SIZE))) int func_1() { return 1; }
__attribute__ ((aligned(SIZE))) int func_2() { return 2; }
__attribute__ ((aligned(SIZE))) int func_3() { return 3; }
__attribute__ ((aligned(SIZE))) int func_4() { return 4; }
__attribute__ ((aligned(SIZE))) int func_5() { return 5; }
__attribute__ ((aligned(SIZE))) int func_6() { return 6; }
__attribute__ ((aligned(SIZE))) int func_7() { return 7; }

__attribute__ ((aligned(SIZE))) int dummy()  { return 0; }
