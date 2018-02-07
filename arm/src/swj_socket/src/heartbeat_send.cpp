#include "ros/ros.h"
#include "swj_socket/heartsendflag.h"
#include "swj_socket/heartrecvflag.h"

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <unistd.h>
#include <errno.h>
#include <log4cxx/logger.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <map>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

#define _in   const &   // input parameter of right value
#define _inc  const     // input parameter of right value
#define _out        &   // output parameter of left value

#define		INTERFACE_COMMAND       "/heartbeat_send"
#define         IP                      "192.168.1.100"
#define         SOCKET_PORT_ADDR        15000
#define         SOL_SOCKET              1
#define         SO_REUSEADDR            2
#define         LISTEN_QUEUE            20

int HeartbeatFlag=1;

//#####################################################
//###  1. define the class HeartbeatRecvSocket  ###
//#####################################################
enum Type_Send {HEART_HEART, OTHER_OTHER};

struct PACKET_HEAD_SEND
{
    Type_Send type_send;
    int length_send;
};

void* send_heart(void* arg);

class HeartbeatSendSocket
{
private:
    struct sockaddr_in server_addr;
    socklen_t server_addr_len;
    int fd;
    int count;

public:
    HeartbeatSendSocket(string ip, int port);
    ~HeartbeatSendSocket();
    void Connect();
    void Run();
    void close_fd();
    int ret_connect;
    pthread_t id;

    friend void* send_heart(void* arg);
};
//#####################################
//###  2. define the callback Function  ###
//#####################################
void message_feed( const swj_socket::heartrecvflag& msg)
{
   HeartbeatFlag=msg.heartrecvflag;
}
 template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
}

//#####################################
//###  3. define the RECV Function  ###
//#####################################
HeartbeatSendSocket::HeartbeatSendSocket(string ip, int port)
{
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    int resp = inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);
    while(resp == 0)
    {
        cout << "Server IP Address Error! retry after 1 seconds.\n";
        sleep(1);
        resp = inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);
    }
    server_addr.sin_port = htons(port);
    server_addr_len = sizeof(server_addr);
    // create socket
    fd = socket(AF_INET, SOCK_STREAM, 0);
    while(fd < 0)
    {
        cout << "Create Socket Failed! retry after 1 seconds.\n";
        sleep(1);
        fd = socket(AF_INET, SOCK_STREAM, 0);
    }
    //初始化count
    count=0;
}

HeartbeatSendSocket::~HeartbeatSendSocket()
{
    close(fd);
}

void HeartbeatSendSocket::Connect()
{
    cout << "Connecting......" << endl;

    ret_connect = connect(fd, (struct sockaddr*)&server_addr, server_addr_len);
    while( ret_connect < 0)
    {
        //cout << "Can not Connect to Server IP! retry after 1 seconds.\n";
        sleep(1);
        ret_connect = connect(fd, (struct sockaddr*)&server_addr, server_addr_len);
    }
    cout << "Connect to Server successfully." << endl;
}

void HeartbeatSendSocket::Run()
{
    //pthread_t id;     // 创建心跳发送进程
    int ret = pthread_create(&id, NULL, send_heart, (void*)this);
    while(ret != 0)
    {
        cout << "Can not create heart-beat sending thread! retry after 1 seconds.\n";
        sleep(1);
        ret = pthread_create(&id, NULL, send_heart, (void*)this);
    }
}

void HeartbeatSendSocket::close_fd()
{
    close(fd);
}

// thread function
void* send_heart(void* arg)
{
    cout << "The heartbeat sending thread started.\n";
    HeartbeatSendSocket* c = (HeartbeatSendSocket*)arg;
    //int count = 0;  // 测试
    while(1)
    {
        PACKET_HEAD_SEND head_send;
        head_send.type_send = HEART_HEART;
        head_send.length_send = 0;
        send(c->fd, &head_send, sizeof(head_send), 0);
        sleep(1);     // 定时1秒
        if(HeartbeatFlag == 0)
        {
            pthread_exit(0);
        }
    }
}


//#####################################
//###  4. define the Main Function  ###
//#####################################
int main ( int argc, char **argv )
{
    ros::init ( argc, argv, "heartSend" );
    ros::AsyncSpinner spinner(1);
    spinner.start();
    log4cxx::Logger::getLogger(ROSCONSOLE_DEFAULT_NAME)->setLevel(
                ros::console::g_level_lookup[ros::console::levels::Debug]);
    ros::NodeHandle NodeHandle;
    ROS_INFO ( "initializing ROS succeed" );

    ros::Subscriber sub = NodeHandle.subscribe("heartbeat_recv", 3, &message_feed );
    ros::Publisher pub = NodeHandle.advertise<swj_socket::heartsendflag>( INTERFACE_COMMAND, 1, false );
    // 1. connect the socket with specific IP and port
    // send request to server with specific IP and port
    HeartbeatSendSocket heartbeat_send_socket(IP, SOCKET_PORT_ADDR);
    heartbeat_send_socket.Connect();
    heartbeat_send_socket.Run();
    swj_socket::heartsendflag Real_heart;
    while(ros::ok())
        {
	    if(HeartbeatFlag == 0)
            {
                cout << "HeartbeatFlag is" << HeartbeatFlag << endl;
                pthread_join(heartbeat_send_socket.id,NULL);//退出线程,释放所占用的资源
                cout << "000" << endl;
                heartbeat_send_socket.close_fd();
		
                while(1)
                {
                    HeartbeatSendSocket heartbeat_send_socket(IP, SOCKET_PORT_ADDR);
                    heartbeat_send_socket.Connect();
                    HeartbeatFlag = 1;
		    Real_heart.heartsendflag=HeartbeatFlag;
		    pub.publish(Real_heart);
                    heartbeat_send_socket.Run();
                    while(1)
                    {
			ros::spinOnce();
                        if(HeartbeatFlag == 0)
                        {
                            break;
                        }
                    }
                    break;
                }
            }
        }
    // 3. start the main loop
    ros::waitForShutdown();
    return 0;
}



