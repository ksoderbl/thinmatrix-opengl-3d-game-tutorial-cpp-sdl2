#ifndef UTILS_H
#define UTILS_H

#include "../Headers.h"

class Utils {
public:
	static void SeedRand(int seed);
	static double Rand();
	static int RandInt(int modulo);
	static uint64_t GetMicroSeconds();
};

#endif
