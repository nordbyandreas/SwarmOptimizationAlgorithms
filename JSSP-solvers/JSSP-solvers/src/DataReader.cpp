

#include "Job.h"
#include "DataReader.h"

using namespace std;


void DataReader::saveSolution(Solution solution, int makespan) 
{
	//loop through solution and print one operation per Line:
	// job - machine - start - end
	ofstream myfile("../../../../src/solution.txt");
	if (myfile.is_open())
	{
		myfile << makespan << " " << Settings::NUM_JOBS << " " << Settings::NUM_MACHINES << "\n";
		for (int i = 0; i < solution.m_machines.size(); i++)
		{
			Machine machine = solution.m_machines[i];
			for (int j = 0; j < machine.m_operations.size(); j++)
			{
				Operation operation = machine.m_operations[j];
				int jobID = operation.m_jobID;
				int startTime = operation.m_startTime;
				int endTime = operation.m_endTime;
				myfile << jobID << " " << i << " " << startTime << " " << endTime << "\n";
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";
	


	
}

void DataReader::ReadDataFromFile() 
{
	cout << "Enter filename: " << endl;
	string inp;
	cin >> inp;
	cout << m_path << inp << ".txt" << endl;

	string fullPath;
	fullPath = m_path + inp + ".txt";


	ifstream infile(fullPath);

	if (!infile)
	{
		cerr << "ERROR: " << fullPath << " could not be opened . !" << endl;
		system("pause");
		getchar();
		cout << "Terminating" << endl;
	}

	bool firstLine = true;
	while (infile)
	{
		//read first line differently (meta data)
		if (firstLine)
		{
			infile >> m_numJobs >> m_numMachines;
			Settings::NUM_JOBS = m_numJobs;
			Settings::NUM_MACHINES = m_numMachines;
			firstLine = false;
			continue;
		}

		//read job specs
		string line;
		getline(infile, line);


		istringstream iss(line);
		vector<string> splitLine((istream_iterator<string>(iss)),
			istream_iterator<string>());


		vector<int> machine_order;
		vector<int> processing_times;

		//TODO: parse line into Job
		//bool used to switch between which list to add to
		bool addToMachineList = true;
		for (string c : splitLine)
		{

			stringstream ss(c);
			int number = 0;
			ss >> number;


			//add to machinelist
			if (addToMachineList)
			{
				stringstream ss(c);
				int number = 0;
				ss >> number;
				machine_order.push_back(number);
				addToMachineList = !addToMachineList;
			}

			//add to processing
			else
			{
				processing_times.push_back(number);
				addToMachineList = !addToMachineList;
			}

		}

		// ADD THE TWO LISTS TO A NEW JOB
		// ADD JOB TO A LIST OF JOBS
		if (processing_times.size() > 0 && machine_order.size() > 0)
		{
			Job job = Job(processing_times, machine_order);
			jobs.push_back(job);
		}







		
	}


	// ADD JOBLIST TO THE JOBLIST OBJECT - (CREATE)
	//JobList jobList = JobList(jobs);

	cout << "File read!  -  numjobs: " << m_numJobs << "   numMachines: " << m_numMachines << endl;

}
