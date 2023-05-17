#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "std_types.h"
#include "Schedulers.h"

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>

#include "std_types.h"

#define UNIT_TIME   30


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_2_clicked();

    //void on_pushButton_clicked();

    void on_comboBox_activated(int index);

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    void DisplayGranttChart(const vector<GanttChartSlot>&);
    void TableWidgetDisplay();
};
#endif // MAINWINDOW_H
