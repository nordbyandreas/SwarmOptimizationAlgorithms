#pragma once

#include <vector>
#include <algorithm>

#include "Particle.h"



class Bee 
{
public:
	vector<Position> m_positions;

	Solution m_solution;
	JobList m_jobList;

	int m_makespan;


	Bee();

	Bee(JobList jobList);

	vector<Position> copyPositions(vector<Position> originalPositions);


	void calculateMakespan();
};