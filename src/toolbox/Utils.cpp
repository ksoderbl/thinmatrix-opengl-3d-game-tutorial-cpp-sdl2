#include "Utils.h"

#include <sys/time.h>

double Utils::Rand()
{
	int x = rand();
	double f = (double)x / RAND_MAX;
	return f;
}

int Utils::RandInt(int modulo)
{
	int x = rand() % modulo;
	return x;
}

void Utils::SeedRand(int seed)
{
	srand((unsigned int)seed);
}

uint64_t Utils::GetMicroSeconds()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);

	return ((uint64_t) tv.tv_sec) * 1000000 + tv.tv_usec;
}
