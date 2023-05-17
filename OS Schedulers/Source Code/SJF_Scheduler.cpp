#include <iostream>
#include <algorithm>
#include <vector>
#include"std_types.h"



void sjf_print_gantt_chart(std::vector<Process> process, int N,vector<GanttChartSlot> &a_slotsVec, double &a_averageTurnaroundTime,double &a_averageWaitingTime);
void SCHEDULAR_preemptive_SJF(vector<Process> &a_processVec,vector<GanttChartSlot> &a_slotsVec,
                                  double &a_averageTurnaroundTime,double &a_averageWaitingTime);

void SCHEDULAR_nonPreemptive_SJF(vector<Process> &a_processVec,vector<GanttChartSlot> &a_slotsVec,
                                     double &a_averageTurnaroundTime,double &a_averageWaitingTime );
void set_priority(vector<Process> &a_processVec);
double totalBurstTime(const std::vector <Process> &process, int N);
std::vector <int> burst_store(vector<Process> &a_processVec,int N);
void swap(Process*xp,  Process*yp);
void sort_burst( std::vector <Process> &process, int N);
void sort_arrive( std::vector <Process> &process, int N);











void SCHEDULAR_preemptive_SJF(vector<Process> &a_processVec,vector<GanttChartSlot> &a_slotsVec,
                                  double &a_averageTurnaroundTime,double &a_averageWaitingTime)
{
        int N = a_processVec.size();
    // sorting the Process according to their arrival times
        sort_burst( a_processVec, N );
        sort_arrive( a_processVec, N );
        a_averageTurnaroundTime=0;
        a_averageWaitingTime=0;
        sjf_print_gantt_chart(a_processVec, N,a_slotsVec,a_averageTurnaroundTime, a_averageWaitingTime);
        a_averageTurnaroundTime/=N;
        a_averageWaitingTime/=N;

}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SCHEDULAR_nonPreemptive_SJF(vector<Process> &a_processVec,
                                     vector<GanttChartSlot> &a_slotsVec,
                                     double &a_averageTurnaroundTime,
                                     double &a_averageWaitingTime )
{   set_priority(a_processVec);
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void set_priority(vector<Process> &a_processVec){


for (int i=0;i<a_processVec.size();i++){


    a_processVec[i].priority=a_processVec[i].burstTime;




}

}
double totalBurstTime(const std::vector <Process> &process, int N)
{
    double sum = 0.0;

    for (int i = 0; i < N; ++i)
        sum += process[i].burstTime;

    return sum;
}
std::vector <int> burst_store(vector<Process> &a_processVec,int N)
{

    std::vector <int> burst_time(N);


    for (int i=0; i<N;i++){


        burst_time[i]=a_processVec[i]. burstTime;

        }
return burst_time;
}

void swap(Process*xp,  Process*yp)
{
    Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void sort_burst( std::vector <Process> &process, int N)
{
    int i, j;
    for (i = 0; i < N-1; i++)
    {

    // Last i elements are already in place
    for (j = 0; j < N-i-1; j++)
        if (process[j]. burstTime> process[j+1]. burstTime)
            swap(&process[j], &process[j+1]);

    }



}
void sort_arrive( std::vector <Process> &process, int N)
{
    int i, j;
    for (i = 0; i < N-1; i++)
    {

    // Last i elements are already in place
    for (j = 0; j < N-i-1; j++)
        if (process[j].arrivalTime> process[j+1].arrivalTime)
            swap(&process[j], &process[j+1]);

    }



}
void sjf_print_gantt_chart(std::vector<Process> process, int N,vector<GanttChartSlot> &a_slotsVec, double &a_averageTurnaroundTime,double &a_averageWaitingTime)
{
std::vector<int> burst_times= burst_store(process, N);
  int process_running=0;
  int stall_time=0;
  int process_runnin_before=0;
  int time_begin=process[0].arrivalTime;
  int time_end=time_begin;
  int total_burst= totalBurstTime( process , N );
  a_averageWaitingTime=0-total_burst;


  while (total_burst>0)
    {
        if( process[ process_running ]. burstTime>0)
        {
            process[ process_running ]. burstTime--;
            total_burst--;
            if(process_running!=process_runnin_before)
            {
                if (stall_time!=0)
                {
                    a_slotsVec.push_back(GanttChartSlot{process[process_runnin_before]. ID,time_begin,time_end-stall_time});
                    if(process[process_runnin_before]. burstTime==0){
                        a_averageTurnaroundTime+= (time_end+time_begin-stall_time-1) -  process[process_runnin_before].arrivalTime;


                }

                }
                else
                {
                    a_slotsVec.push_back(GanttChartSlot{process[process_runnin_before]. ID,time_begin,time_end});
                    if(process[process_runnin_before]. burstTime==0){
                        a_averageTurnaroundTime+= time_end -  process[process_runnin_before].arrivalTime;

                                                           ;
                }

                }
                stall_time=0;
                time_begin=time_end;

            }

        time_end++;
        process_runnin_before=process_running;
    }

  int min=INT_MAX;
  int process_cheked=0;

  for (int i=0;i<N;i++)
  {
        if (time_end>=process[i].arrivalTime&&process[i]. burstTime>0)
        {
            process_cheked++;

            if (min>process[i]. burstTime)
            {
                min= process[i]. burstTime ;
                process_running=i;

            }

        }

  }


  if (process_cheked==0&&total_burst!=0)
  {
        time_end++;
        stall_time++;}
  }


  a_slotsVec.push_back(GanttChartSlot{process[process_runnin_before]. ID,time_begin,time_end});
  a_averageTurnaroundTime+= time_end -  process[process_runnin_before].arrivalTime;
  a_averageWaitingTime+=  a_averageTurnaroundTime;

}

