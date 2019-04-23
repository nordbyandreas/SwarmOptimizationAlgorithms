#pragma once


#include "Solution.h"
#include "Bee.h"
#include "Tools.h"

class BA
{
public:
	
	vector<Bee> m_population;
	vector<Bee> m_elites;
	vector<Bee> m_selectedSites;


	BA();


	void initializePopulation(JobList jobList);


	void evaluateFitnessOfPopulation();

	void sortPopulation();

	void selectEliteBees();
	void selectSites();

	vector<Bee> searchElites();
	vector<Bee> searchSelectedSites();
	vector<Bee> randomSearch();

	void makeNextGeneration(vector<Bee> fittestFromEliteSites, vector<Bee> fittestFromSelectedSites, vector<Bee> remainingRandom);

	Bee beeOptimize(JobList jobList);


};