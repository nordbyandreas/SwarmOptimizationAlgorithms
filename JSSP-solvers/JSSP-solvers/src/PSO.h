#pragma once

#include <ctime>

#include "Particle.h"
#include "Job.h"


// Particle Swarm Optimization - algorithm, contains all PSO methods
class PSO
{
public:
	int m_numParticles;
	JobList m_jobList;
	vector<Particle> m_swarm;
	vector<Particle> m_localBestList;

	Particle m_globalBest;

	//Constructor, init swarm
	PSO(JobList jobList, int numParticles);
	
	

	void decode_representationsToSolutions();
	

	void updatePositionsAndVelocities();


	void printAllSolutions();

	void printAllPositions();

	void printAllSolutionsMakespan();

	Particle swarmOptimize();
	


	void determineLocalAndGlobalBest();
	

	void setGlobalBest();
	

};
