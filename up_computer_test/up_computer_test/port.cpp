#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#define BUFF_SIZE 1024

struct HandMsg
{
    double six_angle[6];//输出主手六个关节角度值
    double eulerian_angle[3];//主手末端相对于基坐标系的姿态
    double pose[3];//主手末端相对于基坐标系的位置
};

int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
  struct termios newtio,oldtio;
  if ( tcgetattr( fd,&oldtio) != 0) {
    perror("SetupSerial 1");
    return -1;
  }
  bzero( &newtio, sizeof( newtio ) );
  newtio.c_cflag |= CLOCAL | CREAD;//用于本地连接和接收使能
  //设置数据位，需使用掩码配置
  newtio.c_cflag &= ~CSIZE;
  switch( nBits )
  {
  case 7:
    newtio.c_cflag |= CS7;
    break;
  case 8:
    newtio.c_cflag |= CS8;
    break;
  }
//奇偶校验设置
  switch( nEvent )
  {
  case 'O'://设置奇校验
    newtio.c_cflag |= PARENB;
    newtio.c_cflag |= PARODD;
    newtio.c_iflag |= (INPCK | ISTRIP);
    break;
  case 'E'://设置偶校验
    newtio.c_iflag |= (INPCK | ISTRIP);
    newtio.c_cflag |= PARENB;
    newtio.c_cflag &= ~PARODD;
    break;
  case 'N'://无校验
    newtio.c_cflag &= ~PARENB;
    break;
  }
//波特率设置
switch( nSpeed )
  {
  case 2400:
    cfsetispeed(&newtio, B2400);
    cfsetospeed(&newtio, B2400);
    break;
  case 4800:
    cfsetispeed(&newtio, B4800);
    cfsetospeed(&newtio, B4800);
    break;
  case 9600:
    cfsetispeed(&newtio, B9600);
    cfsetospeed(&newtio, B9600);
    break;
  case 115200:
    cfsetispeed(&newtio, B115200);
    cfsetospeed(&newtio, B115200);
    break;
  default:
    cfsetispeed(&newtio, B9600);
    cfsetospeed(&newtio, B9600);
    break;
  }
  //停止位设置
  if( nStop == 1 )
    newtio.c_cflag &= ~CSTOPB;
  else if ( nStop == 2 )
    newtio.c_cflag |= CSTOPB;
   // 设置最少字符和等待时间
  newtio.c_cc[VTIME] = 0;
  newtio.c_cc[VMIN] = 0;
  //tcflush函数刷清输入（出）缓存
  tcflush(fd,TCIFLUSH);//TCIFLUSH表示“刷新收到的数据”，抛弃那些已收到但还未读的数据
  //tcsetattr函数用于激活配置
  if((tcsetattr(fd,TCSANOW,&newtio))!=0)
  {
    perror("com set error");
    return -1;
  }
  printf("set done!\n");
  return 0;
}

int open_port(int fd,int comport)
{
  //char *dev[]={"/dev/ttyS0","/dev/ttyS1","/dev/ttyS2"};
 // long vdisable;
  if (comport==1)
  {
    fd = open( "/dev/ttyUSB0", O_RDWR|O_NOCTTY|O_NDELAY);
    if (-1 == fd)
    {
      perror("Can't Open Serial Port");
      return(-1);
    }
    else
      printf("open ttyUSB0 .....\n");
  }
  else if(comport==2)
  {
    fd = open( "/dev/ttyUSB1", O_RDWR|O_NOCTTY|O_NDELAY);
    if (-1 == fd)
    {
      perror("Can't Open Serial Port");
      return(-1);
    }
    else
      printf("open ttyUSB1 .....\n");
  }
  else if (comport==3)
  {
    fd = open( "/dev/ttyUSB2", O_RDWR|O_NOCTTY|O_NDELAY);
    if (-1 == fd){
      perror("Can't Open Serial Port");
      return(-1);
    }
    else
      printf("open ttyUSB2 .....\n");
  }
  //fcntl函数用于恢复串口的状态为阻塞状态，用于等待串口数据的读入
  if(fcntl(fd, F_SETFL, 0)<0)
    printf("fcntl failed!\n");
  else
    printf("fcntl=%d\n",fcntl(fd, F_SETFL,0));
  if(isatty(STDIN_FILENO)==0)//进一步确认设备是否打开
    printf("standard input is not a terminal device\n");
  else
    printf("isatty success!\n");
  printf("fd-open=%d\n",fd);
  return fd;
}

int main(void)
{
  struct HandMsg handmsg;
  int fd;
  int i;
  Count* buff=NULL;
  buff=(HandMsg*)malloc(BUFF_SIZE);
  if((fd=open_port(fd,1))<0)
  {
    perror("open_port error");
    return -1;
  }
  if((i=set_opt(fd,115200,8,'N',1))<0)
  {
    perror("set_opt error");
    return -1;
  }
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

  }
  close(fd);
  return 0;
}
