
#include "Bee.h"
#include "Tools.h"

Bee::Bee() {}


Bee::Bee(JobList jobList)
{
	int operationNum = 0;

	for (Job job : jobList.m_jobs) 
	{
		for (int machine : job.m_machine_order)
		{
			// check how to initialize positions for this problem, 
			// maybe not that important?
			double position = doubleRand(2, false);
			Position positionObject = Position(operationNum, position);
			m_positions.push_back(positionObject);

		}
		operationNum++;
	}

	m_jobList = jobList;
}

vector<Position> Bee::copyPositions(vector<Position> originalPositions) 
{
	vector<Position> copiedPositions;
	for (Position pos : originalPositions)
	{
		Position newPos = Position(pos.m_operation, pos.m_position);
		copiedPositions.push_back(newPos);

	}
	return copiedPositions;
}



void Bee::calculateMakespan() 
{
	
	Solution solution = Solution(Settings::NUM_MACHINES, Settings::NUM_JOBS);

	vector<Position> sortedPositions = copyPositions(m_positions);
	sort(sortedPositions.begin(), sortedPositions.end(), comparePositionValue);

	//use this to look up which index we should check in Job in JobList
	vector<int> operationPerJobIndex;
	for (int i = 0; i < sortedPositions.size(); i++) operationPerJobIndex.push_back(0);


	// use JobList to decode order
//loop through sortedPositions and place each one in correct machine (use JobList to determine which machine)
	for (Position currentPos : sortedPositions)
	{
	
		int jobID = currentPos.m_operation;
		int opInJobIndex = operationPerJobIndex[jobID];
		operationPerJobIndex[jobID]++;

		int machineID = m_jobList.m_jobs[jobID].m_machine_order[opInJobIndex];
		int processingTime = m_jobList.m_jobs[jobID].m_processing_times[opInJobIndex];


		//determine startTime of operation 
		//       (check availableTime in machine and also check lastEndTimePerJob in Solution)
		int availableStartTimeInMachine = solution.m_machines[machineID].m_availableTime;
		int endTimeLastOperationThisJob = solution.m_lastEndTimesPerJob[jobID];
		int opStartTime = max(availableStartTimeInMachine, endTimeLastOperationThisJob);

		//determine endTime of operation (startTime + processingTime)
		int opEndTime = opStartTime + processingTime;

		// create operation(starttime, endtime, jobId)
		Operation operation = Operation(opStartTime, opEndTime, jobID);

		
		// place operation in machine
		solution.m_machines[machineID].m_operations.push_back(operation);


		// update availableTime for machine
		solution.m_machines[machineID].m_availableTime = operation.m_endTime;

		//update lastEndTimePerJob for that job in solution
		solution.m_lastEndTimesPerJob[jobID] = operation.m_endTime;



	}

	// calculate makespan for this solution (find max in solution.lastEndTimesPerJob)
	int makeSpan = 0;
	for (int lastEndTime : solution.m_lastEndTimesPerJob)
	{
		if (lastEndTime > makeSpan)
		{
			makeSpan = lastEndTime;
		}
	}

	//update m_makespan for this Particle
	m_makespan = makeSpan;

	//store solution so we can use it for drawing graph later
	m_solution = solution;


	
}