#include "Utils.h"

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
