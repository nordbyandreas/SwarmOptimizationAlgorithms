


#include "Job.h"





Job::Job(vector<int> processing_times, vector<int> machine_order)
{
	m_processing_times = processing_times;
	m_machine_order = machine_order;
}





JobList::JobList(vector<Job> jobs)
{
	m_jobs = jobs;
}


