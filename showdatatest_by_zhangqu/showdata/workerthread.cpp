#include "workerthread.h"
#include <iostream>
#define pi 3.1415926
using namespace std ;

WorkerThread::WorkerThread(QObject *parent) :
    QThread(parent)
{
}

 extern double tem1;
 extern double tem2;
 extern double tem3;
 extern double tem4;
 extern double tem5;
 extern double tem6;
 extern double tem7;
 extern double tem8;
 extern double tem9;
 extern double tem10;
 extern double tem11;
 extern double tem12;

void WorkerThread::run()
{
    struct HandMsg handmsg;
    int fd;
    int i;
    HandMsg* buff=NULL;
    buff=(HandMsg*)malloc(BUFF_SIZE);
    if((fd=open_port(fd,1))<0)
    {
      perror("open_port error");
     // return -1;
    }
    if((i=set_opt(fd,115200,8,'N',1))<0)
    {
      perror("set_opt error");
     // return -1;
    }
  //  printf("fd=%d\n",fd);
    while(1)
    {
        read(fd,buff,sizeof(handmsg));
        for(int j=0;j<6;j++)
        {
           handmsg.six_angle[j]=(*buff).six_angle[j];
        }
        for(int j=0;j<3;j++)
        {
           handmsg.eulerian_angle[j]=(*buff).eulerian_angle[j];
        }
        for(int j=0;j<3;j++)
        {
           handmsg.pose[j]=(*buff).pose[j];
        }


        cout<<handmsg.six_angle[0]<<" "<<handmsg.six_angle[1]<<" "<<handmsg.six_angle[2]<<" "<<handmsg.six_angle[3]<<" "<<handmsg.six_angle[4]<<" "<<handmsg.six_angle[5]<<endl;
        cout<<handmsg.eulerian_angle[0]<<" "<<handmsg.eulerian_angle[1]<<" "<<handmsg.eulerian_angle[2]<<endl;
        cout<<handmsg.pose[0]<<" "<<handmsg.pose[1]<<" "<<handmsg.pose[2]<<endl;

      //tem1=handmsg.six_angle[0];tem2=handmsg.six_angle[1];tem3=handmsg.six_angle[2];tem4=handmsg.six_angle[3];tem5=handmsg.six_angle[4];tem6=handmsg.six_angle[5];
        tem1=handmsg.six_angle[0]*180/pi;tem2=handmsg.six_angle[1]*180/pi;tem3=handmsg.six_angle[2]*180/pi;tem4=handmsg.six_angle[3]*180/pi;tem5=handmsg.six_angle[4]*180/pi;tem6=handmsg.six_angle[5]*180/pi;
        tem7=handmsg.eulerian_angle[0];tem8=handmsg.eulerian_angle[1];tem9=handmsg.eulerian_angle[2];
        tem10=handmsg.pose[0];tem11=handmsg.pose[1];tem12=handmsg.pose[2];
        /*read(fd,buff,sizeof(count));
        count.a=(*buff).a;
        count.g=(*buff).g;
        strcpy(count.t, (*buff).t);

        cout<<count.a<<endl;
        cout<<count.g<<endl;
        cout<<count.t<<endl;

        tem1=count.a;
        tem2=count.g;
        tem3=count.t;*/

        sleep(0.01);

    }
    close(fd);
}
