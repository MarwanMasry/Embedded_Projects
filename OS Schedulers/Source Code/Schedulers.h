#ifndef SCHEDULERS_H_
#define SCHEDULERS_H_

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include "std_types.h"
#include <vector>
#include <math.h>

/*******************************************************************************
 *                          Public Function Prototype	                       *
 *******************************************************************************/

/*********** Priority Scheduler Functions ***********/
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

void swap(Process*xp,  Process*yp);
void sort(vector <Process> &process);

void SCHEDULAR_nonPreemptivePriority(vector<Process> &a_processVec,
                                     vector<GanttChartSlot> &a_slotsVec,
                                     double &a_averageTurnaroundTime,
                                     double &a_averageWaitingTime);
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
                                  double &a_averageWaitingTime);

/************* FCFS Scheduler Functions *************/
void FCFS_Schedular(vector<Process> &a_processVec, vector<GanttChartSlot> &a_slotsVec,
        double &a_averageTurnaroundTime,double &a_averageWaitingTime);
/************* SJF Scheduler Functions **************/
void SCHEDULAR_preemptive_SJF(vector<Process> &a_processVec,vector<GanttChartSlot> &a_slotsVec,
                                  double &a_averageTurnaroundTime,double &a_averageWaitingTime);

void SCHEDULAR_nonPreemptive_SJF(vector<Process> &a_processVec,vector<GanttChartSlot> &a_slotsVec,
                                     double &a_averageTurnaroundTime,double &a_averageWaitingTime );
/********* Round Robin Scheduler Functions **********/

void SCHEDULAR_roundRobin(vector<Process> &a_processVec,
                                  vector<GanttChartSlot> &a_slotsVec,
                                  double &a_averageTurnaroundTime,
                                  double &a_averageWaitingTime,
                                  int quantum_time);


#endif /* SCHEDULERS_H_ */
