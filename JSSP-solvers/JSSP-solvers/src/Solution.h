#pragma once


#include <vector>

using namespace std;

// Operation class, takes startTime, endTime, jobId
class Operation
{
public:
	int m_startTime;
	int m_endTime;
	int m_jobID;


	Operation(int startTime, int endTime, int jobID);
	
};


//Machine class, takes operations, has availableTime
class Machine
{
public:
	vector<Operation> m_operations;
	int m_availableTime = 0;

	Machine() {}
	Machine(vector<Operation> operations);
	

};



//Solution class, takes machines, has lastEndTimesPerJob
class Solution
{
public:
	vector<Machine> m_machines;
	vector<int> m_lastEndTimesPerJob;

	Solution();
	Solution(int numMachines, int numJobs);


};