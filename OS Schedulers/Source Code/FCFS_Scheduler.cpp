#include "Schedulers.h"

void FCFS_Schedular(vector<Process> &a_processVec, vector<GanttChartSlot> &a_slotsVec,
		double &a_averageTurnaroundTime,double &a_averageWaitingTime)
{
		vector<bool> processCompletedVec( a_processVec.size() );
		unsigned int processCompleted        = 0;
		int currentProcessIndex              = -1;
		int currentProcessArivalTime         = INT_MAX;
		double TotalTurnaroundTime           = 0;
		double TotalWaitingTime              = 0;
		GanttChartSlot s_temp;

		while(processCompleted != a_processVec.size())
		{
			currentProcessIndex     = -1;
			currentProcessArivalTime  = INT_MAX;

			for(unsigned int i = 0; i < a_processVec.size(); i++)
			{
					if(a_processVec[i].arrivalTime < currentProcessArivalTime && !processCompletedVec[i])
					{
						currentProcessArivalTime = a_processVec[i].arrivalTime;
						currentProcessIndex      = i;
					}

			}

			if(currentProcessIndex != -1)
			{
				s_temp.ID        = a_processVec[currentProcessIndex].ID;
				if(a_slotsVec.empty())
				{
					s_temp.startTime = a_processVec[currentProcessIndex].arrivalTime;
				}
				else if (a_slotsVec[a_slotsVec.size()-1].endTime > a_processVec[currentProcessIndex].arrivalTime)
				{
					s_temp.startTime = a_slotsVec[a_slotsVec.size()-1].endTime;
				}
				else if(a_slotsVec[a_slotsVec.size()-1].endTime != a_processVec[currentProcessIndex].arrivalTime)
				{
					s_temp.startTime = a_processVec[currentProcessIndex].arrivalTime;
				}
				s_temp.endTime   = s_temp.startTime + a_processVec[currentProcessIndex].burstTime;
				a_slotsVec.push_back(s_temp);
				processCompleted++;
				processCompletedVec[currentProcessIndex] = true;
			}
		}
		for(unsigned int i = 0 ; i < a_processVec.size() ; i++)
		{
			TotalTurnaroundTime += a_slotsVec[i].endTime - a_processVec[i].arrivalTime;
			TotalWaitingTime += a_slotsVec[i].endTime - a_processVec[i].arrivalTime - a_processVec[i].burstTime;
		}

		a_averageTurnaroundTime = TotalTurnaroundTime / a_processVec.size();
		a_averageWaitingTime    = TotalWaitingTime    / a_processVec.size();
}
