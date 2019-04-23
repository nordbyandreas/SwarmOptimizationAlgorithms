// JSSP-solvers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <cstdio>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <ctime>
#include <iomanip>

#include "Job.h"
#include "DataReader.h"
#include "Solution.h"
#include "Particle.h"
#include "Tools.h"
#include "PSO.h"
#include "Settings.h"
#include "BA.h"
#include "Bee.h"

using namespace std;




int main()
{

	
	
	while (true) 
	{
		DataReader datareader = DataReader();
		datareader.ReadDataFromFile();

		int num_jobs = datareader.m_numJobs;
		int num_machines = datareader.m_numMachines;
		JobList jobList = JobList(datareader.jobs);
		
		std::cout << "\n\n Particle Swarm(p) or Bee Algorithm(b) ? : " << endl;
		string inp;
		cin >> inp;

		if (inp == "b")
		{
			//BA run
			BA ba = BA();
			Bee best = ba.beeOptimize(jobList);
			std::cout << "\n\n FINAL MAKESPAN: " << best.m_makespan << "\n\n" << endl;
			datareader.saveSolution(best.m_solution, best.m_makespan);
		}
		else if (inp == "p")
		{

			// PSO RUN
			PSO pso = PSO(jobList, PSOSettings::SWARM_SIZE);
			Particle best = pso.swarmOptimize();
			//best.printSolution();
			std::cout << "\n\n FINAL MAKESPAN: " << best.m_makespan << "\n\n" << endl;
			datareader.saveSolution(best.m_solution, best.m_makespan);
		}





	}

	




	system("pause");
	getchar();
	std::cout << "Terminating";
	return 0;
}








// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
