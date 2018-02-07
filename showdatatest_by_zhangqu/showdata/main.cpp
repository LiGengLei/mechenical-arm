#include "widget.h"
#include "workerthread.h"
#include <QApplication>
#include <iostream>
using namespace std;

double tem1;
double tem2;
double tem3;
double tem4;
double tem5;
double tem6;
double tem7;
double tem8;
double tem9;
double tem10;
double tem11;
double tem12;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    WorkerThread *thread;
    thread = new WorkerThread();
    thread->start();

    return a.exec();
}
