


#include "Particle.h"
#include "Tools.h"
#include "Settings.h"




Position::Position(int operation, double position)
{
	m_operation = operation;
	m_position = position;
}



bool comparePositionValue(Position p1, Position p2)
{
	return (p1.m_position < p2.m_position);
}




Particle::Particle() {}


Particle::Particle(JobList jobList)
{

		

		// use joblist to initialize a new Particle
		int operationNum = 0;
		for (Job job : jobList.m_jobs)
		{
			for (int machine : job.m_machine_order)
			{
				// create new position in range(0, 2) and add to m_position
				// 
				double position = doubleRand(2, false);
				Position positionObject = Position(operationNum, position);
				m_positions.push_back(positionObject);

				//create new velocity in range(-2, 2) and add to m_velocities
				double velocity = doubleRand(2, true);
				m_velocities.push_back(velocity);


			}
			operationNum++;
		}

		m_jobList = jobList;

}


	//COPY CONSTRUCTOR
Particle::Particle(const Particle &particle)
{
		m_jobList = particle.m_jobList;

		m_positions = particle.m_positions;

		m_velocities = particle.m_velocities;

		m_makespan = particle.m_makespan;

		m_solution = particle.m_solution;

}



vector<Position> Particle::copyPositions(vector<Position> originalPositions)
{
		vector<Position> copiedPositions;
		for (Position pos : originalPositions)
		{
			Position newPos = Position(pos.m_operation, pos.m_position);
			copiedPositions.push_back(newPos);

		}
		return copiedPositions;
}


void Particle::calculateMakespan()
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





		/*
		// PRINT SORTED PARTICLE
		cout << "\n\n" << endl;
		cout << "Printing SORTED particle::" << endl;
		cout << "operation / position" << endl;
		for (int i = 0; i < sortedPositions.size(); i++)
		{
			cout << sortedPositions[i].m_operation << " / "
				<< setprecision(2) << sortedPositions[i].m_position << "   ,   ";
		}
		*/
}



	//update positions and velocities
void Particle::updateParticle(Particle localBest, Particle globalBest)
	{
	

		//update velocities
		for (int i = 0; i < m_velocities.size(); i++)
		{
			double newVelocity = PSOSettings::INERTIA_WEIGHT * m_velocities[i] +
				PSOSettings::ACCELERATION_CONSTANT_LOCAL * doubleRand(1, false) * (localBest.m_positions[i].m_position - m_positions[i].m_position) +
				PSOSettings::ACCELERATION_CONSTANT_GLOBAL * doubleRand(1, false) * (globalBest.m_positions[i].m_position - m_positions[i].m_position);
			m_velocities[i] = newVelocity;

			//clamp velocity between 0 and 2 - IT GOT WORSE !?!?!
			if (m_velocities[i] > 2) m_velocities[i] = 2;
			if (m_velocities[i] < -2) m_velocities[i] = -2;

		}

		//update positions
		for (int i = 0; i < m_positions.size(); i++)
		{

			m_positions[i].m_position += m_velocities[i];

		}

	}






//test if solution is valid
void Particle::printSolution()
	{


		vector<vector<string>> disp;
		for (int i = 0; i < Settings::NUM_MACHINES; i++)
		{
			vector<string> m;
			for (int j = 0; j < m_makespan + 1; j++)
			{
				m.push_back("-");
			}
			disp.push_back(m);
		}

		cout << "\n";
		cout << "IN Print Solution \n";
		cout << "printing solution.machinelengths \n\n";
		cout << "Makespan: " << m_makespan << "\n\n";

		for (int i = 0; i < m_solution.m_machines.size(); i++)
		{
			cout << "Machine: " << i << " = ";
			cout << m_solution.m_machines[i].m_operations.size() << endl;
			cout << "\n";
			for (int j = 0; j < m_solution.m_machines[i].m_operations.size(); j++)
			{
				//cout << "\n";
				//cout << "Operation: " << j << endl;
				int startTime = m_solution.m_machines[i].m_operations[j].m_startTime;
				//cout << "starttime: " << startTime << endl;
				int endTime = m_solution.m_machines[i].m_operations[j].m_endTime;
				//cout << "endtime: " << endTime << endl;
				int jobId = m_solution.m_machines[i].m_operations[j].m_jobID;
				//cout << "jobID: " << jobId << endl;
				//cout << "\n";
				for (int t = startTime; t < endTime; t++)
				{
					disp[i][t] = to_string(jobId);
				}
			}
		}

		cout << "Printing Display: \n\n";
		for (int i = 0; i < disp.size(); i++)
		{
			cout << "\n";
			for (int j = 0; j < disp[i].size(); j++)
			{
				cout << disp[i][j];
			}

			cout << "\n";
		}


	}




void Particle::printParticle()
	{

		cout << "\n\n\n\n" << endl;
		cout << "Printing particle::" << endl;
		cout << "operation / position" << endl;
		for (int i = 0; i < m_positions.size(); i++)
		{
			cout << m_positions[i].m_operation << " / "
				<< setprecision(2) << m_positions[i].m_position << "   ,   ";
		}
		cout << "\n" << endl;
		cout << "velocities:  " << endl;
		for (int i = 0; i < m_positions.size(); i++)
		{
			cout << setprecision(2) << m_velocities[i] << "   |   ";
		}
		cout << "\n" << endl;
	}


