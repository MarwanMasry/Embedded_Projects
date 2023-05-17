/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "Schedulers.h"

/*******************************************************************************
 *                        Public Function Definitions	                       *
 *******************************************************************************/










void SCHEDULAR_roundRobin(vector<Process> &a_processVec,
                                  vector<GanttChartSlot> &a_slotsVec,
                                  double &a_averageTurnaroundTime,
                                  double &a_averageWaitingTime,
                                  int quantum_time)
{
    int processCount = a_processVec.size();
    vector<int> processFinished(processCount);
    vector<int> processRemainingBurst(processCount);
    int currentTime                      	= 0;
    int processCompleted       			 	= 0;
    double TotalTurnaroundTime           	= 0;
    double TotalWaitingTime              	= 0;
    bool waiting                            = true;

    GanttChartSlot s_temp;

    sort(a_processVec);

    for(int i = 0; i < processCount; i++)
    {
        processRemainingBurst[i] = a_processVec[i].burstTime;
    }

    while(processCompleted != processCount)
    {
        waiting = true;
        for(int i = 0; i < processCount; i++)
        {
            if(a_processVec[i].arrivalTime <= currentTime && processFinished[i] != 1)
            {
                waiting = false;
                s_temp.ID = a_processVec[i].ID;
                s_temp.startTime = currentTime;

                if(processRemainingBurst[i] >= quantum_time)
                {
                    currentTime += quantum_time;
                    processRemainingBurst[i] -= quantum_time;
                }

                else
                {
                    currentTime += processRemainingBurst[i];
                    processRemainingBurst[i] = 0;
                }

                s_temp.endTime = currentTime;
                a_slotsVec.push_back(s_temp);

                if(processRemainingBurst[i] == 0)
                {
                    processFinished[i] = 1;
                    TotalTurnaroundTime += currentTime - a_processVec[i].arrivalTime;
                    TotalWaitingTime    += currentTime - a_processVec[i].arrivalTime - a_processVec[i].burstTime;
                    processCompleted++;
                }
            }
        }

        if(waiting)
        {
            currentTime++;
        }

    }

    a_averageTurnaroundTime = TotalTurnaroundTime / processCount;
    a_averageWaitingTime    = TotalWaitingTime    / processCount;

}


void sort(vector <Process> &process)
{

    int i, j, N = process.size();
    for (i = 0; i < N-1; i++)
    {

    // Last i elements are already in place
    for (j = 0; j < N-i-1; j++)
        if (process[j].arrivalTime > process[j+1].arrivalTime)
            swap(&process[j], &process[j+1]);

    }
}

