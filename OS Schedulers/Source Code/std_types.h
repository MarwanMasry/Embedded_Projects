#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*******************************************************************************
 *                              Includes Needed                                *
 *******************************************************************************/
#include <string>

#define FCFS 0
#define P_SJF 1
#define NP_SJF 2
#define P_Pri 3
#define NP_Pri 4
#define RR 5

using namespace std;

/*******************************************************************************
 *                             Types Deceleration	                           *
 *******************************************************************************/
/*
 * Description:
 *
 * This structure is used to store all the needed input information about the
 * process where we store the Process ID/name, arrival time, Burst time and
 * Priority in case the user choose Priority Scheduler option other cases this
 * value will be redundant.
 */
typedef struct
{
    string  ID;
    int 	arrivalTime;
    int	    burstTime;
    int     priority;
}Process;

/*
 * Description:
 *
 * This structure is used for the Gantt Chart where the result of all
 * Schedulers functions return vector of this structure which represents the
 * slots of Gantt chart.
 *
 */
typedef struct
{
    string  ID;
    int     startTime;
    int     endTime;
}GanttChartSlot;


#endif
