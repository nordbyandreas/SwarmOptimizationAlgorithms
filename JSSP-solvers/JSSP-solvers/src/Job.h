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

using namespace std;

class Job
{

public:
	vector<int> m_processing_times;
	vector<int> m_machine_order;

	Job(vector<int> processing_times, vector<int> machine_order);
};


class JobList
{
public:
	int m_numJObs;
	int m_numMachines;

	vector<Job> m_jobs;
	JobList() {}
	JobList(vector<Job> jobs);
	
};


