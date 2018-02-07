#include "ros/ros.h"
#include "swj_socket/heartrecvflag.h"
#include "swj_socket/heartsendflag.h"
#include "swj_socket/recv_flag.h"

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

#define		INTERFACE_COMMAND       "/heartbeat_recv"
#define         SOCKET_IP_ADDR          "192.168.1.2"
#define         SOCKET_PORT_ADDR        8000
#define         SOL_SOCKET              1
#define         SO_REUSEADDR            2
#define         LISTEN_QUEUE            20

int HeartbeatFlag=1;
int recv_flag=1;
//#####################################################
//###  1. define the class HeartbeatRecvSocket  ###
//#####################################################
void* heart_handler(void* arg);

class HeartbeatRecvSocket
{
private:
    struct sockaddr_in server_addr;
    socklen_t server_addr_len;
    int listen_fd;    // 监听的fd
    int max_fd;       // 最大的fd
    int new_fd;       //连接的fd
    fd_set master_set;   // 所有fd集合，包括监听fd和客户端fd
    fd_set working_set;  // 工作集合

    struct timeval timeout;
    map<int, pair<string, int> > mmap;   // 记录连接的客户端fd--><ip, count>
public:
    HeartbeatRecvSocket(int port);
    ~HeartbeatRecvSocket();
    void Bind();
    void Listen(int queue_len = 20);
    void Accept();
    void Run();
    void Recv();
    void RunInit();
    friend void* heart_handler(void* arg);
};

enum Type_Recv {HEART, OTHER};

struct PACKET_HEAD_RECV
{
    Type_Recv type_recv;
    int length_recv;
};

//#####################################
//###  2. define the callback Function  ###
//#####################################
void message_feed1( const swj_socket::heartsendflag& msg)
{
   HeartbeatFlag=msg.heartsendflag;
}
void message_feed2( const swj_socket::recv_flag& msg)
{
   recv_flag=msg.recv_flag;
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
HeartbeatRecvSocket::HeartbeatRecvSocket(int port)
{
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY);//inet_addr(ip.c_str());
    server_addr.sin_port = htons(port);
    // create socket to listen
    listen_fd = socket(PF_INET, SOCK_STREAM, 0);
    while(listen_fd < 0)
    {
        std::cout << "Create Socket Failed!";
        sleep(1);
        listen_fd = socket(PF_INET, SOCK_STREAM, 0);
    }
    int opt = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
}

HeartbeatRecvSocket::~HeartbeatRecvSocket()
{
    for(int fd=0; fd<=max_fd; ++fd)
    {
        if(FD_ISSET(fd, &master_set))
        {
            close(fd);
        }
    }
}

void HeartbeatRecvSocket::Bind()
{
    while(-1 == (bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr))))
    {
        std::cout << "Server Bind Failed!";
        sleep(1);
        bind(listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    }
    std::cout << "Bind Successfully.\n";
}

void HeartbeatRecvSocket::Listen(int queue_len)
{
    while(-1 == listen(listen_fd, queue_len))
    {
        std::cout << "Server Listen Failed!";
        sleep(1);
        listen(listen_fd, queue_len);
    }
    std::cout << "Listen Successfully.\n";
}

void HeartbeatRecvSocket::Accept()
{
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    new_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_addr_len);
    while(new_fd < 0)
    {
        std::cout << "Server Accept Failed!";
        sleep(1);
        new_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_addr_len);
    }

    string ip(inet_ntoa(client_addr.sin_addr));    // 获取客户端IP

    std::cout << ip << " new connection was accepted.\n";

    mmap.insert(make_pair(new_fd, make_pair(ip, 0)));
    std::cout<<"new_fd"<<new_fd<<std::endl;
    // 将新建立的连接的fd加入master_set
    FD_SET(new_fd, &master_set);
    if(new_fd > max_fd)
    {
        max_fd = new_fd;
    }
}

void HeartbeatRecvSocket::RunInit()
{
    pthread_t id;     // 创建心跳检测线程
    int ret = pthread_create(&id, NULL, heart_handler, (void*)this);
    if(ret != 0)
    {
        std::cout << "Can not create heart-beat checking thread.\n";
    }

    max_fd = listen_fd;   // 初始化max_fd
    FD_ZERO(&master_set);
    FD_SET(listen_fd, &master_set);  // 添加监听fd
}



void* heart_handler(void* arg)
{
    std::cout << "The heartbeat checking thread started.\n";
    HeartbeatRecvSocket* s = (HeartbeatRecvSocket*)arg;
    while(1)
    {
        map<int, pair<string, int> >::iterator it = s->mmap.begin();
        for( ; it!=s->mmap.end(); )
        {
            if(it->second.second == 5)   // 1s*5没有收到心跳包，判定客户端掉线
            {
                std::cout << "The client " << it->second.first << " has be offline.\n";

                int fd = it->first;
                close(fd);            // 关闭该连接
                FD_CLR(fd, &s->master_set);
                if(fd == s->max_fd)      // 需要更新max_fd;
                {
                    while(FD_ISSET(s->max_fd, &s->master_set) == false)
                        s->max_fd--;
                }

                HeartbeatFlag = 0;   // 断开连接不可发送消息
                recv_flag=-1;
		std::cout << "HeartbeatFlag="<<HeartbeatFlag<<std::endl;
                s->mmap.erase(it++);  // 从map中移除该记录

            }
            else if(it->second.second < 5 && it->second.second >= 0)
            {
                it->second.second += 1;
                ++it;
            }
            else
            {
                ++it;
            }
        }
        //std::cout << ServerFlag << endl;
        sleep(1);   // 定时三秒
    }
}
void HeartbeatRecvSocket::Recv()
{
	if(FD_ISSET(new_fd, &working_set))
        {
	    PACKET_HEAD_RECV head_recv;
	    head_recv.type_recv=OTHER;
            recv(new_fd, &head_recv, sizeof(head_recv), 0);   // 先接受包头
            if(head_recv.type_recv == HEART)
            {
                mmap[new_fd].second = 0;       // 每次收到心跳包，count置0
                std::cout << "Received heart-beat from client.\n";
                //sleep(0.01);
            }
            else
            {
                // 数据包，通过head.length确认数据包长度
            }
        }
}


//#####################################
//###  4. define the Main Function  ###
//#####################################
int main ( int argc, char **argv )
{
    ros::init ( argc, argv, "heartRecv" );
    ros::AsyncSpinner spinner(1);
    spinner.start();
    log4cxx::Logger::getLogger(ROSCONSOLE_DEFAULT_NAME)->setLevel(
                ros::console::g_level_lookup[ros::console::levels::Debug]);

    // 1. connect the socket with specific IP and port
    // create the socket description
    HeartbeatRecvSocket heartbeat_recv_socket(SOCKET_PORT_ADDR);
    // send request to server with specific IP and port
    heartbeat_recv_socket.Bind();
    heartbeat_recv_socket.Listen();
    
    //检测心跳，接受信息
    heartbeat_recv_socket.RunInit();
    heartbeat_recv_socket.Run();

    // 3. start the main loop
    ros::waitForShutdown();
    return 0;
}

void HeartbeatRecvSocket::Run()
{
    ros::NodeHandle NodeHandle;
    ros::Publisher pub = NodeHandle.advertise<swj_socket::heartrecvflag>( INTERFACE_COMMAND, 1, false );
    ros::Subscriber sub1 = NodeHandle.subscribe("heartbeat_send", 3, &message_feed1 );
    ros::Subscriber sub2 = NodeHandle.subscribe("socket_input", 3, &message_feed2 );
    ROS_INFO ( "initializing ROS succeed" );
    swj_socket::heartrecvflag Real_heart;
    while(ros::ok())// 
    {
        FD_ZERO(&working_set);
        memcpy(&working_set, &master_set, sizeof(master_set));

        timeout.tv_sec = 3;
        timeout.tv_usec = 0;
	Real_heart.heartrecvflag=HeartbeatFlag;
	Real_heart.recv_flag=recv_flag;
        pub.publish(Real_heart);
        std::cout<<"max_fd="<<max_fd<<std::endl;
        int nums = select(max_fd+1, &working_set, NULL, NULL, &timeout);
        if(nums < 0)
        {
            std::cout << "select() error!"<<errno<<std::endl;
	    continue;
            //exit(1);
        }
        if(nums == 0)
        {
            std::cout << "select() is timeout!"<<std::endl;
            continue;
        }
	ros::spinOnce();
        if(FD_ISSET(listen_fd, &working_set))//测试listen_fd是否可读，即是否网络上有数据
            Accept();   // 有新的客户端请求
        else
        {
            Recv(); // 接收客户端的消息
        }
    }
}


