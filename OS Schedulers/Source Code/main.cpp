#include "mainwindow.h"
#include"Schedulers.h"
#include"std_types.h"

#include <QApplication>

void test_PriorityScheduling(vector<GanttChartSlot> & a_slotsVec)
{
    vector<Process> a_processVec = {Process {"P1", 0, 2, 3},
                                    Process {"P2", 2, 2, 2},
                                    Process {"P3", 9, 2, 1}};

    double a_averageTurnaroundTime;
    double a_averageWaitingTime;

    SCHEDULAR_preemptivePriority(a_processVec,
                                 a_slotsVec,
                                 a_averageTurnaroundTime,
                                 a_averageWaitingTime);

//	for(unsigned int i =0; i< a_slotsVec.size(); i++)
//	{
//		cout  <<"<Slot"<<i<<">  ID:" << a_slotsVec.at(i).ID << "\t Starts:"
//			  << a_slotsVec.at(i).startTime
//		      << "\t Ends:" << a_slotsVec.at(i).endTime << endl;
//	}

//	cout << "\nAverage Turn-around Time:"<<a_averageTurnaroundTime
//		 << "\nAverage Waiting time:" << a_averageWaitingTime << "\n";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
