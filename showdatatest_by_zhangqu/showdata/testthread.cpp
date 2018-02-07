#include "testthread.h"
#include   <iostream>
using   namespace   std   ;
TestThread::TestThread(QObject *parent) :
    QThread(parent)
{
}
extern double test;
void TestThread::run()
{
    //触发信号
   // emit TestSignal(123);
    while(1)
        {
        test ++;
      //  connect(sender, SIGNAL(send(i)), this, SLOT(showme(QString)));
    cout<<"test:"<<test<<endl;
    sleep(1);
    }
}
