#pragma once



#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <sstream>
#include <iterator>

#include "Job.h"
#include "Settings.h"
#include "Solution.h"

using namespace std;


class DataReader
{
public:
	string m_path = "./../../../../TestData/";
	int m_numJobs;
	int m_numMachines;
	vector<Job> jobs;

	
	void ReadDataFromFile();
	void saveSolution(Solution solution, int makespan);
};


