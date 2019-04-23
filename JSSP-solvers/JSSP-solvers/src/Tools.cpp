


#include "Tools.h"

//UTILS
double doubleRand(double max, bool includeNegativeRange) {
	double randomNumber = (rand()) / (double(RAND_MAX) + 1.0) *max;

	if (includeNegativeRange)
	{
		if ((rand()) / (double(RAND_MAX) + 1.0) > 0.5)
		{
			randomNumber = randomNumber * -1.0;
		}
	}
	return randomNumber;
}
