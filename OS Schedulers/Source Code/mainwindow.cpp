#include "mainwindow.h"
#include "ui_mainwindow.h"

vector<Process> all_Process; // all_Process vector
vector<GanttChartSlot> gantt_Chart; // GANNT CHART
double avgTurnAround; // Average Turn Around
double avgWaitingTime; // Average Waiting Time
bool pri_Flag = false; // FOR DYNAMIC CHOICES OF PROCESSES
int p_Count; // HAS COUNT OF ALL PROCESSES
bool quanta = false; // CHECK IF QUANTA HAS BEEN INSERTED
int quant_Time; // A GLOBAL VARIABLE CARRYING QUANTUM TIME FROM USER

QTableWidget *table; // GANTT CHART TABLE
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    TableWidgetDisplay(); // AUTOMATICALLY DISPLAYING THE TABLE


    //SETTING THE WINDOW SIZE
    this->setFixedHeight(518); // SETTING THE HEIGHT AND WIDTH OF THE TABLE
    this->setFixedWidth(800);


    //HIDING ALL REQUIRED INFO
    ui->label_4->setText(QString::fromStdString(to_string(p_Count)));
    ui->label->hide();
    ui->label_2->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->label_11->hide();
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->lineEdit_5->hide();


    //SETTING THE SECOND, THIRD, FOURTH AND FIFTH LINE EDIT TO NUMBERS ONLY
    ui->lineEdit_2->setValidator(new QIntValidator(0, 100, this));
    ui->lineEdit_3->setValidator(new QIntValidator(0, 100, this));
    ui->lineEdit_4->setValidator(new QIntValidator(0, 100, this));
    ui->lineEdit_5->setValidator(new QIntValidator(0, 100, this));
    //TAKES FROM 0 to 100
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TableWidgetDisplay()
{
    table = new QTableWidget(this);
    //table->setStyleSheet("border-radius: 20px; border-style: bold;");

    table->horizontalHeader()->hide();
    table->verticalHeader()->hide();
    table->setRowCount(2);
    table->setColumnCount(3);
    table->setFixedHeight(76);
    table->setFixedWidth(800);
    table->setRowHeight(0, 50);
    table->setRowHeight(1, 5);
    //DEFINITION FOR THE TABLE
}


//testing

//void test_PriorityScheduling(vector<GanttChartSlot> & a_slotsVec);
void MainWindow::on_pushButton_2_clicked() // DISPLAY CHART BUTTON
{
    /* DISPLAY CHART BUTTON MAKES SURE THAT THERE ARE ENOUGH PROCESSES
     *
     * TO DISPLAY YOUR GANTT CHART
     *
     * THE GANTT CHART WAS USED USING TABLES AND MANIPULATION OF THE TABLE USING COLORS
     *
     * AND FONT
     *
     *
     */

    //CHECKING IF THERE ARE PROCESSES
    if(all_Process.size() == 0)
        return;

    //RESET THE PREVIOUS CHART
    gantt_Chart.clear();

    //GET THE CURRENT SCHEDULAR TO DRAW ACCORDING TO IT
    int currSchedular = ui->comboBox->currentIndex();

    /* EACH SCHEDULAR HAS ITS OWN FUNCTION THAT DISPLAYS
     *
     * EVERY SINGLE SCHEDULAR ACCORDING TO ITS SPECIFICATIONS
     *
     */
    switch(currSchedular){
    case FCFS:
        FCFS_Schedular(all_Process,
                       gantt_Chart,
                       avgTurnAround,
                       avgWaitingTime);
    break;
    case P_SJF:
        SCHEDULAR_preemptive_SJF(all_Process,
                                 gantt_Chart,
                                 avgTurnAround,
                                 avgWaitingTime);
    break;
    case NP_SJF:
        SCHEDULAR_nonPreemptive_SJF(all_Process,
                                    gantt_Chart,
                                    avgTurnAround,
                                    avgWaitingTime);
    break;
    case P_Pri:
        SCHEDULAR_preemptivePriority(all_Process,
                                     gantt_Chart,
                                     avgTurnAround,
                                     avgWaitingTime);
    break;
    case NP_Pri:
    SCHEDULAR_nonPreemptivePriority(all_Process,
                                    gantt_Chart,
                                    avgTurnAround,
                                    avgWaitingTime);
    break;
    case RR:
    SCHEDULAR_roundRobin(all_Process,
                         gantt_Chart,
                         avgTurnAround,
                         avgWaitingTime,
                                          quant_Time);
    break;
    }
   // MAIN FUNCTION FOR DISPLAYING
   DisplayGranttChart(gantt_Chart);
   ui->label_9->setText(QString::fromStdString(to_string(avgWaitingTime)));
   ui->label_10->setText(QString::fromStdString(to_string(avgTurnAround)));
}
int random()
{
    return (int)((float)rand()/(float)RAND_MAX * 255);
}
void MainWindow::DisplayGranttChart(const vector<GanttChartSlot> & a_slotsVec)
{
    map<string,QColor> color_map;
    //At start
    int current_time=0;
    unsigned int vec_index=0;
    unsigned int col_index=0;
    table->setColumnCount(a_slotsVec.size());
    /////////////////////////////////////////////
    while(vec_index<a_slotsVec.size())
    {
        if(a_slotsVec[vec_index].startTime==current_time)
        {
            QTableWidgetItem *item_p = new QTableWidgetItem(QString::fromStdString(a_slotsVec[vec_index].ID)); // Process name
            QTableWidgetItem *item_t = new QTableWidgetItem(QString::number(a_slotsVec[vec_index].endTime)); // Process end time
            //items alignment
            item_p->setTextAlignment(Qt::AlignCenter);
            item_t->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            //styling for process
            if(color_map.count(a_slotsVec[vec_index].ID)==0){
                color_map[a_slotsVec[vec_index].ID]=QColor(random(), random(), random(), 160);
                item_p->setBackground(QBrush(color_map.at(a_slotsVec[vec_index].ID)));
            }
            else
                item_p->setBackground(QBrush(color_map.at(a_slotsVec[vec_index].ID)));
            //setting items to table
            if(col_index >= table->columnCount())
            {
                table->setColumnCount(table->columnCount()+1);
            }
            table->setItem(0, col_index, item_p);
            table->setItem(1, col_index, item_t);

            // adjusting width to match time taken by process
            table->setColumnWidth(col_index,(a_slotsVec[vec_index].endTime-a_slotsVec[vec_index].startTime)  * UNIT_TIME);

            //updating current time to which next process (if exist) will start
            current_time=a_slotsVec[vec_index].endTime;

            /////
            vec_index++;
        }
        else
        {
            //for null process

            QTableWidgetItem *item_p = new QTableWidgetItem("");
            QTableWidgetItem *item_t = new QTableWidgetItem(QString::number(a_slotsVec[vec_index].startTime)); // NUll end time
            //items alignment
            item_t->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

            //styling for process
            item_p->setBackground(QBrush(QColor(255, 204, 204, 120)));

            //setting items to table
            if(col_index >= table->columnCount())
            {
                table->setColumnCount(table->columnCount()+1);
            }
            table->setItem(0, col_index, item_p);
            table->setItem(1, col_index, item_t);

            // adjusting width to match time taken by process
            table->setColumnWidth(col_index,(a_slotsVec[vec_index].startTime-current_time)  * UNIT_TIME);


            //updating current time to which same process will start
            current_time=a_slotsVec[vec_index].startTime;

            //don't update index
        }
        col_index++;
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    //SHOWING THE REQUIRED INFO
    /*ui->label->show();
    ui->label_2->show();
    ui->label_5->show();
    ui->label_6->show();
    ui->lineEdit->show();
    ui->lineEdit_2->show();
    ui->lineEdit_3->show();
    ui->lineEdit_4->show();*/
    switch(index){
    case FCFS:
        pri_Flag = false;
        /* RESET ALL LABELS */
        ui->label_6->hide(); // HIDING THE LABEL OF PRIORITY
        ui->lineEdit_4->hide(); // HIDING LINE OF PRIORITY
        ui->label_11->hide(); // HIDING THE LABEL OF QUANTUM TIME
        ui->lineEdit_5->hide(); // HIDING THE TEXT OF QUANTUM

        /* SHOWING THE NEEDED LABELS */
        ui->label->show();
        ui->label_2->show();
        ui->label_5->show();
        //ui->label_6->show(); LABEL OF PRIORITY
        ui->lineEdit->show();
        ui->lineEdit_2->show();
        ui->lineEdit_3->show();
        //ui->lineEdit_4->show(); LINE OF PRIORITY

        /* CODE */
        break;
    case P_SJF:
        pri_Flag = false;
        /* RESET ALL LABELS */
        ui->label_6->hide(); // HIDING THE LABEL OF PRIORITY
        ui->lineEdit_4->hide(); // HIDING LINE OF PRIORITY
        ui->label_11->hide(); // HIDING THE LABEL OF QUANTUM TIME
        ui->lineEdit_5->hide(); // HIDING THE TEXT OF QUANTUM
        /* SHOWING THE NEEDED LABELS */
        ui->label->show();
        ui->label_2->show();
        ui->label_5->show();
        //ui->label_6->show(); LABEL OF PRIORITY
        ui->lineEdit->show();
        ui->lineEdit_2->show();
        ui->lineEdit_3->show();
        //ui->lineEdit_4->show(); LINE OF PRIORITY
        break;
    case NP_SJF:
        pri_Flag = false;
        /* RESET ALL LABELS */
        ui->label_6->hide(); // HIDING THE LABEL OF PRIORITY
        ui->lineEdit_4->hide(); // HIDING LINE OF PRIORITY
        ui->label_11->hide(); // HIDING THE LABEL OF QUANTUM TIME
        ui->lineEdit_5->hide(); // HIDING THE TEXT OF QUANTUM
        /* SHOWING THE NEEDED LABELS */
        ui->label->show();
        ui->label_2->show();
        ui->label_5->show();
        //ui->label_6->show(); LABEL OF PRIORITY
        ui->lineEdit->show();
        ui->lineEdit_2->show();
        ui->lineEdit_3->show();
        //ui->lineEdit_4->show(); LINE OF PRIORITY
        break;
    case P_Pri:
        /* PROMPTING THE USER TO DELETE ALL THE PROCESSES OR NOT */
        if(pri_Flag == false){
            QMessageBox msgBox;
            msgBox.setText("All the processes that were created, if created, will be deleted.");
            msgBox.setInformativeText("Do you want to remove the processes?");
            msgBox.setStandardButtons(QMessageBox::Apply | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Apply);
            int ret = msgBox.exec();
            switch (ret) {
              case QMessageBox::Apply:
                  // Apply was clicked
                  all_Process.clear();
                  p_Count = 0;
                  ui->label_4->setText(QString::fromStdString(to_string(p_Count)));
                  pri_Flag = true;
                  break;
              case QMessageBox::Cancel:
                  // Cancel was clicked
                  QMessageBox::information(this, "Info", "All previous processes priority were set to 0");
                  pri_Flag = true;
                  break;
              default:
                  break;
            }
        }
        /* RESET ALL LABELS */
        ui->label_11->hide(); // HIDING THE LABEL OF QUANTUM TIME
        ui->lineEdit_5->hide(); // HIDING THE TEXT OF QUANTUM
        //ui->label_6->hide(); // HIDING THE LABEL OF PRIORITY
        //ui->lineEdit_4->hide(); // HIDING LINE OF PRIORITY
        /* SHOWING THE NEEDED LABELS */
        ui->label->show();
        ui->label_2->show();
        ui->label_5->show();
        ui->label_6->show();
        ui->lineEdit->show();
        ui->lineEdit_2->show();
        ui->lineEdit_3->show();
        ui->lineEdit_4->show();
        break;
    case NP_Pri:
        if(pri_Flag == false){
            QMessageBox msgBox;
            msgBox.setText("All the processes that were created, if created, will be deleted.");
            msgBox.setInformativeText("Do you want to remove the processes?");
            msgBox.setStandardButtons(QMessageBox::Apply | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Apply);
            int ret = msgBox.exec();
            switch (ret) {
              case QMessageBox::Apply:
                  // Apply was clicked
                  all_Process.clear();
                  p_Count = 0;
                  ui->label_4->setText(QString::fromStdString(to_string(p_Count)));
                  pri_Flag = true;
                  break;
              case QMessageBox::Cancel:
                  // Cancel was clicked
                  QMessageBox::information(this, "Info", "All previous processes priority were set to 0");
                  pri_Flag = true;
                  break;
              default:
                  break;
            }
        }
        /* RESET ALL LABELS */
        ui->label_11->hide(); // HIDING THE LABEL OF QUANTUM TIME
        ui->lineEdit_5->hide(); // HIDING THE TEXT OF QUANTUM
        //ui->label_6->hide(); // HIDING THE LABEL OF PRIORITY
        //ui->lineEdit_4->hide(); // HIDING LINE OF PRIORITY
        /* SHOWING THE NEEDED LABELS */
        ui->label->show();
        ui->label_2->show();
        ui->label_5->show();
        ui->label_6->show();
        ui->lineEdit->show();
        ui->lineEdit_2->show();
        ui->lineEdit_3->show();
        ui->lineEdit_4->show();
        break;
    case RR:
        if(quanta == true){
            QMessageBox msgBox;
            msgBox.setText("A quantum time was inserted before.");
            msgBox.setInformativeText("Do you want to reset the quantum time?");
            msgBox.setStandardButtons(QMessageBox::Apply | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Apply);
            int ret = msgBox.exec();
            switch (ret) {
              case QMessageBox::Apply:
                  // Apply was clicked
                  quanta = false;
                  quant_Time = 0;
                  ui->label_13->setText(QString::fromStdString(to_string(quant_Time)));
                  ui->label_11->show(); // HIDING THE LABEL OF QUANTUM TIME
                  ui->lineEdit_5->show(); // HIDING THE TEXT OF QUANTUM
                  break;
              case QMessageBox::Cancel:
                  // Cancel was clicked
                  QMessageBox::information(this, "Info", "Quantum Time wasn't changed.");
                  break;
              default:
                  break;
            }
        }
        else{
            ui->label_11->show(); // HIDING THE LABEL OF QUANTUM TIME
            ui->lineEdit_5->show(); // HIDING THE TEXT OF QUANTUM
        }
        pri_Flag = false;
        /* RESET ALL LABELS */
        ui->label_6->hide(); // HIDING THE LABEL OF PRIORITY
        ui->lineEdit_4->hide(); // HIDING LINE OF PRIORITY
        /* SHOWING THE NEEDED LABELS */
        ui->label->show();
        ui->label_2->show();
        ui->label_5->show();
        //ui->label_6->show(); LABEL OF PRIORITY
        ui->lineEdit->show();
        ui->lineEdit_2->show();
        ui->lineEdit_3->show();
        //ui->lineEdit_4->show(); LINE OF PRIORITY

        /* CODE */
        break;
    }
}


void MainWindow::on_pushButton_clicked()
{
    Process new_process;
    QString p_idname = ui->lineEdit->text();
    QString p_start = ui->lineEdit_2->text();
    QString p_burst = ui->lineEdit_3->text();
    QString pri = ui->lineEdit_4->text();
    QString quanta_T = ui->lineEdit_5->text();
    int currScheduler = ui->comboBox->currentIndex();
    if(p_idname == QString("") || p_start == QString("") || p_burst == QString("")){
        QMessageBox::information(this, "Error", "You have not inserted all of the information");
        return;
    }
    if((p_idname == QString("") || p_start == QString("") || p_burst == QString("") || pri == QString("")) && (currScheduler == P_Pri || currScheduler == NP_Pri)){
        QMessageBox::information(this, "Error", "You have not inserted all of the information");
        return;
    }
    if((p_idname == QString("") || p_start == QString("") || p_burst == QString("") || quanta_T == QString("")) && (currScheduler == RR)){
        QMessageBox::information(this, "Error", "You have not inserted all of the information");
        return;
    }
    if(currScheduler == RR){
        if(quanta == false){
            if(stoi(quanta_T.toStdString()) == 0){
                QMessageBox::information(this, "Error", "You have not inserted all of the information");
                return;
            }
            else{
                quant_Time = stoi(quanta_T.toStdString());
                quanta = true;
                ui->label_11->hide(); // HIDING THE LABEL OF QUANTUM TIME
                ui->lineEdit_5->hide(); // HIDING THE TEXT OF QUANTUM
                ui->label_13->setText(QString::fromStdString(to_string(quant_Time)));
            }
        }
    }
    new_process.ID = p_idname.toStdString();
    new_process.arrivalTime = stoi(p_start.toStdString());
    new_process.burstTime = stoi(p_burst.toStdString());
    if(pri == QString(""))
        new_process.priority = 0;
    else
        new_process.priority = stoi(pri.toStdString());
    string test;
    test.append("Added a new Process\n");
    switch(currScheduler){
        case FCFS:
        test.append("First Come First Serve\n");
        break;
        case P_SJF:
        test.append("Preemptive Shortest Job First\n");
        break;
        case NP_SJF:
        test.append("Non-Preemptive Shortest Job First\n");
        break;
        case P_Pri:
        test.append("Preemptive Priority\n");
        break;
        case NP_Pri:
        test.append("Non-Preemptive Priority\n");
        break;
        case RR:
        test.append("Round-Robin\n");
        break;
    }
    all_Process.push_back(new_process);
    test.append("Process Name: " + new_process.ID + "\n");
    test.append("Arrival Time: " + to_string(new_process.arrivalTime) + "\n");
    test.append("Burst Time: " + to_string(new_process.burstTime) + "\n");
    test.append("Priority: " + to_string(new_process.priority) + "\n");
    QMessageBox::information(this, "Info", QString::fromStdString(test));

    p_Count++;
    ui->label_4->setText(QString::fromStdString(to_string(p_Count)));
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}


void MainWindow::on_pushButton_4_clicked()
{
    QMessageBox::information(this, "Info", QString("Cleared all Processes"));
    all_Process.clear();
    p_Count = 0;
    quant_Time = 0;
    quanta = false;
    avgTurnAround = 0;
    avgWaitingTime = 0;
    pri_Flag = false;
    ui->label_9->setText(QString::fromStdString(to_string(avgWaitingTime)));
    ui->label_10->setText(QString::fromStdString(to_string(avgTurnAround)));
    ui->label_13->setText(QString::fromStdString(to_string(p_Count)));
    ui->label_4->setText(QString::fromStdString(to_string(p_Count)));
}


void MainWindow::on_pushButton_3_clicked()
{
    string text;
    for(int i = 0; i < all_Process.size(); i++){
        text.append("Process Number: " + to_string(i + 1) + "\n");
        Process currProcess = all_Process[i];
        text.append("Process Name: " + currProcess.ID + "\n");
        text.append("Arrival Time: " + to_string(currProcess.arrivalTime) + "\n");
        text.append("Burst Time: " + to_string(currProcess.burstTime) + "\n");
        text.append("Priority: " + to_string(currProcess.priority) + "\n");
        text.append("\n\n");
    }
    QMessageBox::information(this, "View", QString::fromStdString(text));
}

