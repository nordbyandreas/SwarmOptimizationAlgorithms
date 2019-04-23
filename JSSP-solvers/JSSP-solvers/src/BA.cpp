
#include "BA.h"
#include "Settings.h"

BA::BA()
{


}


void BA::initializePopulation(JobList jobList) 
{
	
	for (int i = 0; i < BASettings::N; i++) 
	{
		Bee bee = Bee(jobList);
		m_population.push_back(bee);
	}

}

void BA::evaluateFitnessOfPopulation() 
{
	for (int i = 0; i < m_population.size(); i++)
	{
		m_population[i].calculateMakespan();
	}

}

bool compareMakespan(Bee b1, Bee b2)
{
	return (b1.m_makespan < b2.m_makespan);
}

void BA::sortPopulation() 
{

	sort(m_population.begin(), m_population.end(), compareMakespan);
}


void BA::selectEliteBees() 
{
	m_elites.clear();

	for (int i = 0; i < BASettings::E; i++) 
	{
		m_elites.push_back(m_population[i]);
	}
}

void BA::selectSites() 
{
	m_selectedSites.clear();
	for (int i = m_elites.size(); i < BASettings::M; i++)
	{
		m_selectedSites.push_back(m_population[i]);
	}
}

vector<Bee> BA::searchElites() 
{
	vector<Bee> fittestFromEliteSearch;

	for (int i = 0; i < m_elites.size(); i++) 
	{
		vector<Bee> recruits;
		for (int j = 0; j < BASettings::NEP; j++) 
		{
			//create new Bee
			Bee searchBee = Bee(m_elites[i].m_jobList);
		
			//copy positions
			searchBee.m_positions = searchBee.copyPositions(m_elites[i].m_positions);
		
			//search
			for (int k = 0; k < searchBee.m_positions.size(); k++) 
			{
				searchBee.m_positions[k].m_position += doubleRand(1, true) * BASettings::NGH;
			}
			searchBee.calculateMakespan();
			recruits.push_back(searchBee);

		}

		// add best recruit for that site to fittestFromEliteSearch
		sort(recruits.begin(), recruits.end(), compareMakespan);
		fittestFromEliteSearch.push_back(recruits[0]);

	}
	return fittestFromEliteSearch;
}

vector<Bee> BA::searchSelectedSites()
{
	vector<Bee> fittestFromSelectedSitesSearch;

	for (int i = 0; i < m_selectedSites.size(); i++)
	{
		vector<Bee> recruits;

		for (int j = 0; j < BASettings::NEP; j++)
		{
			//create new Bee
			Bee searchBee = Bee(m_selectedSites[i].m_jobList);

			//copy positions
			searchBee.m_positions = searchBee.copyPositions(m_selectedSites[i].m_positions);

			//search
			for (int k = 0; k < searchBee.m_positions.size(); k++)
			{
				searchBee.m_positions[k].m_position += doubleRand(1, true) * BASettings::NGH;
			}
			searchBee.calculateMakespan();
			recruits.push_back(searchBee);

		}

		// add best recruit for that site to fittestFromEliteSearch
		sort(recruits.begin(), recruits.end(), compareMakespan);
		fittestFromSelectedSitesSearch.push_back(recruits[0]);

	}
	return fittestFromSelectedSitesSearch;
}

vector<Bee> BA::randomSearch()
{
	vector<Bee> randomSearchResult;

	for (int i = BASettings::M; i < BASettings::N; i++) 
	{
		Bee randomBee = Bee(m_elites[0].m_jobList);
		randomBee.calculateMakespan();
	}

	return randomSearchResult;
}

void BA::makeNextGeneration(vector<Bee> fittestFromEliteSites, vector<Bee> fittestFromSelectedSites, vector<Bee> remainingRandom)
{
	m_population.clear();

	//insert elites
	m_population.insert(m_population.end(), m_elites.begin(), m_elites.end());

	//insert fittestFromSiteSearches
	m_population.insert(m_population.end(), fittestFromEliteSites.begin(), fittestFromEliteSites.end());
	m_population.insert(m_population.end(), fittestFromSelectedSites.begin(), fittestFromSelectedSites.end());

	//insert randomSearch
	m_population.insert(m_population.end(), remainingRandom.begin(), remainingRandom.end());
}



/*
1. Initialise population with random solutions.
2. Evaluate fitness of the population.
3. While(stopping criterion not met)
	//Forming new population.
	4. Select sites for neighbourhood search.
	5. Recruit bees for selected sites(more bees for best e sites) and evaluate fitnesses.
	6. Select the fittest bee from each patch.
	7. Assign remaining bees to search randomly and evaluate their fitnesses.
	8. End While.
*/

Bee BA::beeOptimize (JobList jobList) 
{
	// 1. init population with random solutions
	initializePopulation(jobList);
	
	// 2. evaluate fitness of the population
	// (evaluate makespan)
	evaluateFitnessOfPopulation();

	int c = 0;

	// 3. While (stopping criteria not met)  // forming new population
	while (c < BASettings::NUM_ITERATIONS) 
	{
		if ((c + 1) % 100 == 0 || c+1 == 1)
		{
			cout << "Iteration: " << (c + 1) << "   Makespan: " << to_string(m_population[0].m_makespan) << endl;
			
		}

		sortPopulation();



		// 4. select elite bees
		selectEliteBees();
			// sort based on makespan
			// select x best bees as elites

		// 5. select sites for neighbourhood search
		selectSites();
			//select the y next bees for neighbourhood search

		// 6. recruit bees around selected sites and evaluate fitness
		vector<Bee> fittestFromEliteSites = searchElites();
		vector<Bee> fittestFromSelectedSites = searchSelectedSites();
		// 7. select fittest bee from each site
			

		// 8. assign remaining bees to search randomly and evaluate their fitness
		vector<Bee> remainingRandom = randomSearch();

		//9. add elites, fittestFromElitesSearch, fittestFromSelectedSites and remainingRandom to m_population
		makeNextGeneration(fittestFromEliteSites, fittestFromSelectedSites, remainingRandom);

		c++;
	}


	sortPopulation();

	Bee bestSolution = m_population[0];

	return bestSolution;

}