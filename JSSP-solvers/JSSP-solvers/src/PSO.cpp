

#include "PSO.h"
#include "Settings.h"

// Particle Swarm Optimization - algorithm, contains all PSO methods

PSO::PSO(JobList jobList, int numParticles)
	{
		//seed random;
		srand(static_cast<unsigned int>(clock()));
		m_jobList = jobList;
		m_numParticles = numParticles;
		for (int i = 0; i < numParticles; i++)
		{

			Particle particle = Particle(m_jobList);
			particle.calculateMakespan();

			Particle copy = particle;
			copy.calculateMakespan();

			// add to swarm
			m_swarm.push_back(particle);

			// add initalcopy to local best for that particle
			m_localBestList.push_back(copy);

			// give global best a start value
			if (i == 0)
			{
				m_globalBest = copy;
			}
		}
		setGlobalBest();

	}

	void PSO::decode_representationsToSolutions()
	{
		/*
		// why doesnt this work, when the one below does?
		// det kan være pga. referanser eller pointers 
		for (Particle p : m_swarm)
		{
			p.calculateMakespan();
		}

		*/

		for (int i = 0; i < m_swarm.size(); i++)
		{
			m_swarm[i].calculateMakespan();
		}
	}

	void PSO::updatePositionsAndVelocities()
	{
		for (int i = 0; i < m_swarm.size(); i++)
		{
			m_swarm[i].updateParticle(m_localBestList[i], m_globalBest);
		}
	}

	void PSO::printAllSolutions()
	{
		for (Particle p : m_swarm) {
			p.printSolution();
		}
	}
	void PSO::printAllPositions()
	{
		for (Particle p : m_swarm) {
			p.printParticle();
		}
	}
	void PSO::printAllSolutionsMakespan()
	{
		int counter = 0;
		for (Particle p : m_swarm)
		{
			cout << "\n particle " << counter << " makespan: " << p.m_makespan << endl;
			counter++;
		}
	}

	Particle PSO::swarmOptimize()
	{
		PSOSettings::INERTIA_WEIGHT = PSOSettings::INERTIA_WEIGHT_VAL;
		Particle best;
		int c = 0;

		

		while (c < PSOSettings::NUM_ITERATIONS)
		{
			if ((c + 1) % 100 == 0 || c+1 == 1) 
			{
				cout << "Iteration: " << (c + 1) << "   Makespan: " << m_globalBest.m_makespan << endl;
				
			}
		
		


			// 1.INIT SWARM
				// DONE IN CONSTRUCTOR

			// 2.OBTAIN SCHEDULING SOLUTIONS THROUGH DECODING THE PARTICLE REPRESENTATION
			decode_representationsToSolutions();

			//printAllPositions();
			//printAllSolutionsMakespan();
			//printAllSolutions();
			//printAllSolutionsMakespan();

			// 3. FIND GLOBAL BEST AND LOCAL BEST
			determineLocalAndGlobalBest();

			// 4. UPDATE PARTICLES
			updatePositionsAndVelocities();

			c++;

		
			PSOSettings::INERTIA_WEIGHT -= PSOSettings::INERTIA_WEIGHT_DECREMENT_VALUE;
		
		}

		decode_representationsToSolutions();
		determineLocalAndGlobalBest();

		return m_globalBest;

	}


	void PSO::determineLocalAndGlobalBest()
	{
		// update localBest for each solution in swarm IF
		for (int i = 0; i < m_swarm.size(); i++)
		{
			// if this particle is better(lower makespan) than localBest 
			if (m_swarm[i].m_makespan < m_localBestList[i].m_makespan)
			{
				//make copy of this particle 
				Particle copy = m_swarm[i];
				// and set it to new localBest
				m_localBestList[i] = copy;
			}
		}

		setGlobalBest();

	}

	void PSO::setGlobalBest()
	{
		// update global best  IF
		for (int i = 0; i < m_swarm.size(); i++)
		{
			//if a particle is better than global best
			if (m_swarm[i].m_makespan < m_globalBest.m_makespan)
			{
				
				// then copy particle and
				Particle copy = m_swarm[i];
				// update global particle
				m_globalBest = copy;
			}
		}
	}

