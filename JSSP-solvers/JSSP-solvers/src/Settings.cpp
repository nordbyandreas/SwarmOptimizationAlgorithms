

#include "Settings.h";

namespace Settings 
{
	// (updated by datareader)
	extern int NUM_JOBS = 0;
	extern int NUM_MACHINES = 0;
}

namespace BASettings
{
	 
	extern const int NUM_ITERATIONS = 1000;

	extern const int N = 100;    // num bees | (num scout bees)
	extern const int M = 20;    // num selected points/patches/sites
	extern const int E = 5;    // num elites

	extern const int NEP = 7;  // num recruited bees for elite points
	extern const int NSP = 3;  // num recruited bees for non-elite selected points
	extern const double NGH = 3;  //size of patches | neighbourhood range  == how "far" recruited bees can search

}



namespace PSOSettings 
{

	
	extern const int SWARM_SIZE = 100;
	extern const int NUM_ITERATIONS = 1000;


	// update particle
	extern double INERTIA_WEIGHT_VAL = 0.9;
	extern double INERTIA_WEIGHT = 0.9;
	extern double INERTTIA_WEIGHT_MIN = 0.4;
	extern double INERTIA_WEIGHT_DECREMENT_VALUE = setIntertiaDecrementValue(NUM_ITERATIONS, INERTIA_WEIGHT, INERTTIA_WEIGHT_MIN);           //updated in run, based 
	
	extern const double ACCELERATION_CONSTANT_LOCAL = 2;
	extern const double ACCELERATION_CONSTANT_GLOBAL = 2;
	// ---------------

}

double setIntertiaDecrementValue(double num_iterations, double max, double min)
{
	return (max - min) / num_iterations;
}

