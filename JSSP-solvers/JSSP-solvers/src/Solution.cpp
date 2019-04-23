
#include "Solution.h"



Operation::Operation(int startTime, int endTime, int jobID)
	{
		m_startTime = startTime;
		m_endTime = endTime;
		m_jobID = jobID;
	}



Machine::Machine(vector<Operation> operations)
	{
		m_operations = operations;
	}


Solution::Solution() {};

Solution::Solution(int numMachines, int numJobs)
	{
		vector<Machine> machines;
		for (int i = 0; i < numMachines; i++) machines.push_back(Machine());
		m_machines = machines;

		vector<int> lastEndTimesPerJob;
		for (int i = 0; i < numJobs; i++) lastEndTimesPerJob.push_back(0);
		m_lastEndTimesPerJob = lastEndTimesPerJob;
	}

