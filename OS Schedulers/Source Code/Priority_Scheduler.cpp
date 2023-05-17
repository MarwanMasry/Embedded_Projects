/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "Schedulers.h"

/*******************************************************************************
 *                        Public Function Definitions	                       *
 *******************************************************************************/
/*
 * Description:
 * This function takes a vector of process to be scheduled based on their priority,
 * It is non-preemptive scheduler so process can not be interrupted until it
 * terminates itself or its time is up.
 * Then return a vector containing the slots of Gantt Chart and the average turn
 * around time and the average waiting time.
 * FCFS algorithm will be executed in case of equal Priorities.
 *
 * Arguments:
 * vector<Process> &a_processVec: vector of processes to be scheduled.
 * vector<GrattChartSlot> &a_slotsVec: vector of slots of Gantt Chart.
 * double &a_averageTurnaroundTime
 * double &a_averageWaitingTime)
 */
void SCHEDULAR_nonPreemptivePriority(vector<Process> &a_processVec,
									 vector<GanttChartSlot> &a_slotsVec,
									 double &a_averageTurnaroundTime,
									 double &a_averageWaitingTime )
{
	vector<bool> processCompletedVec( a_processVec.size() );
	int currentTime                      = 0;
	unsigned int processCompleted        = 0;
	int currentProcessIndex              = -1;
	int currentProcessPriority           = INT_MAX;
	double TotalTurnaroundTime           = 0;
	double TotalWaitingTime              = 0;
	GanttChartSlot s_temp;

	/*
	 * 	This while loop is responsible for processing all the processes according
	 *  to Priority scheduling algorithm and create the vector that contain the
	 *  slots of Gantt graph and also calculate the Total round time and total
	 *  waiting time
     */
	while(processCompleted != a_processVec.size())
	{
		currentProcessIndex     = -1;
		currentProcessPriority  = INT_MAX;

		/*
		 * This loop is responsible for deciding which process will have a slot
		 * in the Gantt graph as this process has the highest priority or in
		 * case of equal priority FCFS algorithm will be taken.
		 */
		for(unsigned int i = 0; i < a_processVec.size(); i++)
		{
			/*
			 * 	If the process has arrival time less than the current and this
			 *  process havn't completed we enter the condition.
			 */
			if(a_processVec[i].arrivalTime <= currentTime && processCompletedVec[i] == 0)
			{
				/*	Select the process with highest priority */
				if(a_processVec[i].priority < currentProcessPriority)
				{
					currentProcessPriority = a_processVec[i].priority;
					currentProcessIndex    = i;
				}

				/* FCFS algorithm will be executed in case of equal Priorities. */
				if(a_processVec[i].priority == currentProcessPriority)
				{
					if(a_processVec[i].arrivalTime < a_processVec[currentProcessIndex].arrivalTime)
					{
						currentProcessPriority = a_processVec[i].priority;
						currentProcessIndex    = i;
					}
				}
			}
		}

		/*	If their is a process exists at the current time enter the condition */
		if(currentProcessIndex != -1)
		{
			/*
			 * 	We create a new slots with all needed data as ID, Start time and
			 *  end time then push it in the vector which contain all the slots
			 */
			s_temp.ID        = a_processVec[currentProcessIndex].ID;
			s_temp.startTime = currentTime;
			s_temp.endTime   = currentTime +\
							   a_processVec[currentProcessIndex].burstTime;
			a_slotsVec.push_back(s_temp);


			/* Turn around time = Process completion time - Arrival time */
			TotalTurnaroundTime += currentTime + \
							       a_processVec[currentProcessIndex].burstTime-\
								   a_processVec[currentProcessIndex].arrivalTime;

			/* Waiting time = Turn around time - Burst time */
			TotalWaitingTime    += currentTime -\
					               a_processVec[currentProcessIndex].arrivalTime;

			/*
			 * Each loop we finish a process as this is non preemptive and their
			 * is no interruption so we mark this process as completed and
			 * increment process that is completed by 1 and set the current time
			 * as the old one with addition of the burst time of current process.
			 */
			processCompletedVec[currentProcessIndex] = true;
			processCompleted++;
			currentTime += a_processVec[currentProcessIndex].burstTime;
		}
		else
		{
		/* If their is a no process exists at the current time,only increment the time */
			currentTime++;
		}
	}

	/*
	 * 	After calculating the total turn-around time and total Waiting time
	 *  we calculate their average.
	 */
	a_averageTurnaroundTime = TotalTurnaroundTime / a_processVec.size();
	a_averageWaitingTime    = TotalWaitingTime    / a_processVec.size();
}

/*
 * Description:
 * This function takes a vector of process to be scheduled based on their priority,
 * It is preemptive scheduler so process can be interrupted in between
 * Then return a vector containing the slots of Gantt Chart and the average turn
 * around time and the average waiting time.
 * FCFS algorithm will be executed in case of equal Priorities.
 *
 * Arguments:
 * vector<Process> &a_processVec: vector of processes to be scheduled.
 * vector<GrattChartSlot> &a_slotsVec: vector of slots of Gantt Chart.
 * double &a_averageTurnaroundTime
 * double &a_averageWaitingTime)
 */
void SCHEDULAR_preemptivePriority(vector<Process> &a_processVec,
								  vector<GanttChartSlot> &a_slotsVec,
								  double &a_averageTurnaroundTime,
								  double &a_averageWaitingTime )
{
	vector<bool> processCompletedVec( a_processVec.size() );
	vector<int>  processRemainingBurst( a_processVec.size() );
	int currentTime                      = 0;
	unsigned int processCompleted        = 0;
	int currentProcessIndex              = -1;
	int currentProcessPriority           = INT_MAX;
	double TotalTurnaroundTime           = 0;
	double TotalWaitingTime              = 0;
	GanttChartSlot s_temp;

	/* Copy all the burst time of all processes in a new vector for needed processing */
	for(unsigned int i = 0; i < a_processVec.size(); i++)
	{
		processRemainingBurst[i] = a_processVec[i].burstTime;
	}

	/*
	 * 	This while loop is responsible for processing all the processes according
	 *  to Priority scheduling algorithm and create the vector that contain the
	 *  slots of Gantt graph and also calculate the Total round time and total
	 *  waiting time
     */

	while(processCompleted != a_processVec.size())
	{
		currentProcessIndex     = -1;
		currentProcessPriority  = INT_MAX;

		/*
		 * This loop is responsible for deciding which process will have a slot
		 * in the Gantt graph as this process has the highest priority or in
		 * case of equal priority FCFS algorithm will be taken.
		 * In this loop we check the all the process each 1 unit time slot and
		 * decide if a new process will be processed or the old one.
		 */
		for(unsigned int i = 0; i < a_processVec.size(); i++)
		{
			/*
			 * 	If the process has arrival time less than the current and this
			 *  process havn't completed we enter the condition.
			 */
			if(a_processVec[i].arrivalTime <= currentTime && processCompletedVec[i] == 0)
			{
				/*	Select the process with highest priority */
				if(a_processVec[i].priority < currentProcessPriority)
				{
					currentProcessPriority = a_processVec[i].priority;
					currentProcessIndex    = i;
				}

				/* FCFS algorithm will be executed in case of equal Priorities. */
				if(a_processVec[i].priority == currentProcessPriority)
				{
					if(a_processVec[i].arrivalTime < a_processVec[currentProcessIndex].arrivalTime)
					{
						currentProcessPriority = a_processVec[i].priority;
						currentProcessIndex    = i;
					}
				}
			}
		}

		/*	If their is a process exists at the current time enter the condition */
		if(currentProcessIndex != -1)
		{
			/*
			 * Create a new slot with the current process index ID, with start
			 * and end time equal to the current time, end time will be updated
			 * each time slot.
			 */
			s_temp.ID        = a_processVec[currentProcessIndex].ID;
			s_temp.startTime = currentTime;
			s_temp.endTime   = currentTime;

			/* Determine if we will add the created slot or not. */
			if(a_slotsVec.size() == 0)
			{
				/* If there is no slot yet in the Gantt chart add the created slot. */
				a_slotsVec.push_back(s_temp);
			}
			else
			{
				/*
				 * If there exists slots in the Gant chart the increment/update
				 * the end time of the last element in theGantt chart.
				 */
				a_slotsVec.at(a_slotsVec.size()-1).endTime++;


				/*
				 * If the ID of the current process isn't the same as the last slot
				 * in the Gantt Chart then do add a new slot with the process ID.
				 */
				if(a_processVec[currentProcessIndex].ID != a_slotsVec[a_slotsVec.size()-1].ID)
				{
					a_slotsVec.push_back(s_temp);
				}
			}

			/*
			 *  The current process burst is decremented by the unit time slot
			 *  each loop so that we can take action when the burst time ends or
			 *  to know if this process is interrupted we can know what is the
			 *  remaining burst time remaining for the interrupted process.
			 */
			processRemainingBurst[currentProcessIndex] -= 1;
			currentTime ++;


			/*
			 * If the current process has finished all its burst time we calculate
			 * the turn-around time and waiting time and accumulate them.
			 */
			if(processRemainingBurst[currentProcessIndex] == 0)
			{
				/* Turn around time = Process completion time - Arrival time */
				TotalTurnaroundTime += currentTime -\
									   a_processVec[currentProcessIndex].arrivalTime;

				/* Waiting time = Turn around time - Burst time */
				TotalWaitingTime    += currentTime -\
									   a_processVec[currentProcessIndex].burstTime-\
									   a_processVec[currentProcessIndex].arrivalTime;

				/*
				 * When a process finishes we need to mark it as complete and
				 * increment the variable that contain the number of process
				 * that is completed
				 */
				processCompletedVec[currentProcessIndex] = true;
				processCompleted++;
			}

		}
		else
		{
		/* If their is a no process exists at the current time,only increment the time */
			currentTime++;
		}
	}

	/* Increment the end time of the last element in the Gantt chart as it isn't
	 * added in the loop.
	 */
	a_slotsVec[a_slotsVec.size()-1].endTime++;

   /*
    *   After calculating the total turn-around time and total Waiting time
	*  we calculate their average.
	*/
	a_averageTurnaroundTime = TotalTurnaroundTime / a_processVec.size();
	a_averageWaitingTime    = TotalWaitingTime    / a_processVec.size();

}
