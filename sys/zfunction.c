
#include "zfunction.h"

long zfunction(long x) {
	x = x & 0xFFFFF00F;
	x = x << 8;
	x = x |0xFF;

	return x;
}

