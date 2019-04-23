#pragma once


namespace Settings
{

	extern int NUM_JOBS;
	extern int NUM_MACHINES;
}


namespace BASettings 
{
	extern const int NUM_ITERATIONS;

	extern const int N;    // num bees | (num scout bees)
	extern const int M;    // num selected points/patches/sites
	extern const int E;    // num elites

	extern const int NEP;  // num recruited bees for elite points
	extern const int NSP;  // num recruited bees for non-elite selected points
	extern const double NGH;  //size of patches | neighbourhood range  == how "far" recruited bees can search


}

namespace PSOSettings
{

	extern const int SWARM_SIZE;
	extern const int NUM_ITERATIONS;


	extern double INERTIA_WEIGHT_VAL;
	extern double INERTIA_WEIGHT;
	extern double INERTTIA_WEIGHT_MIN;
	extern double INERTIA_WEIGHT_DECREMENT_VALUE;

	extern const double ACCELERATION_CONSTANT_LOCAL;
	extern const double ACCELERATION_CONSTANT_GLOBAL;
}


double setIntertiaDecrementValue(double swarm_size, double max, double min);