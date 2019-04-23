#pragma once

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>

#include "Job.h"
#include "Solution.h"
#include "Settings.h"


using namespace std;





class Position
{
public:
	int m_operation;
	double m_position;

	Position(int operation, double position);
	
};

bool comparePositionValue(Position p1, Position p2);





class Particle
{
public:
	// MAKE THESE GLOBAL VARIABLES
	int positionInitMax = 2;
	int positionInitMin = 0;
	int velocityInitMax = 2;
	int velocityInitMin = -2;
	// --------------------------

	vector<Position> m_positions;
	vector<double> m_velocities;
	int m_makespan;


	// Joblist does not need to be saved in every particle
	JobList m_jobList;

	Solution m_solution;



	Particle();

	Particle(JobList jobList);

	//COPY CONSTRUCTOR
	Particle(const Particle &particle);
	
	vector<Position> copyPositions(vector<Position> originalPositions);

	void calculateMakespan();

	//update positions and velocities
	void updateParticle(Particle localBest, Particle globalBest);


	//test if solution is valid
	void printSolution();


	void printParticle();

};
