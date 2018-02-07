#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include "swj_socket/heartrecvflag.h"
#include "swj_socket/recv_flag.h"
#include "swj_socket/statefeed.h"

#include <vector>
#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <log4cxx/logger.h>
 #include <pthread.h>

#define _in   const &   // input parameter of right value
#define _inc  const     // input parameter of right value
#define _out        &   // output parameter of left value

#define		INTERFACE_COMMAND       "/socket_input"
#define		INTERFACE_STATEFEEDBACK "/interface_statefeed"
#define         INTERFACE_JOINT_STATES  "/joint_states"
#define         SOCKET_IP_ADDR          "192.168.1.100"
#define         SOCKET_PORT_ADDR        5000

#define         LOOP_TIME               0.06

int sock;
int res;
signed int recv_flag;
int HeartbeatFlag=1;
void Thread_RunInit();
void* sub_fuc(void* arg);
std::vector<std::string> names;
std::vector<double> position;
std::vector<double> velocity;
std::string Joint_state;
int check_node;
float Pressure;
std::string mobot_mode;
std::string vehicle_mode;
//#####################################################
//###  1. define the Function ResolveJointstateString  ###
//#####################################################
void ResolveJointstateString( std::string _in input,std::vector<std::string> _out name,std::vector<double> _out position,std::vector<double> _out velocity,int _out check_node,float _out pressure,std::string _out mobot_mode,std::string _out vehicle_mode )
{
    std::vector<std::string> result;
    boost::split( result, input, boost::is_any_of(" "), boost::algorithm::token_compress_on );
    std::cout<<"size="<<result.size()<<std::endl;
    name.clear();
    position.clear();
    velocity.clear();
    name.insert(name.end(),result.begin(),result.begin()+11);
    for (size_t i = 0; i < 11; i++)
        position.push_back( atof(result[i+11].c_str()) );
    for (size_t i = 0; i < 11; i++)
        velocity.push_back( atof(result[i+22].c_str()) );
    check_node=(atoi(result[33].c_str()));
    pressure=(atoi(result[34].c_str()));
    mobot_mode=result[35].c_str();
    vehicle_mode=result[36].c_str();
}

//#####################################
//###  3. define the blend Function  ###
//#####################################
int BlendJointStates( std::vector<std::string> _in name,std::vector<double> _in position,std::vector<double> _in velocity, sensor_msgs::JointState _out output)
{
    // check the feasibility of the input vector (sensor_msgs::JointState)
    if (name.size() <= 0)
        ROS_ERROR("ERROR <BlendJointStates>: the input vector has no availuable data.");

    // fill in the output
    output.header.stamp = ros::Time::now();
    output.name = name;
    output.position = position;
    output.velocity = velocity;

    return output.name.size();
}
//#####################################
//###  3. define the socket Function  ###
//#####################################
void create_socket()
{
// create the socket description
    sock = socket(AF_INET, SOCK_STREAM, 0);
    // send request to server with specific IP and port
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  // clear the struct serv_addr
    serv_addr.sin_family = AF_INET;  // IPv4 protocal
    serv_addr.sin_addr.s_addr = inet_addr( SOCKET_IP_ADDR );  // specific IP address
    serv_addr.sin_port = htons( 5000 );  // specific port address

    recv_flag=-1;
    std::cout<<"ko"<<std::endl;
    res = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    // wait until socket has been connected
    while( res < 0 )
    {
        printf("Waiting for connecting.\n");
        ros::Duration(1).sleep();
        res = connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    }
    recv_flag=res;
    std::cout<<"ok"<<std::endl;
}

void recv_msgs()
{
	char Buffer_recv[550];
	memset(Buffer_recv,0,550);
	std::cout<<"1"<<std::endl;
        socklen_t length_recv = recv(sock, Buffer_recv, 550, 0);
	std::cout<<"2"<<std::endl;
        if( (int)length_recv < 0)
        {
            printf("recv msg error: %s(errno: %d)\n", strerror(errno), errno);
            sleep(1);
        }
        Joint_state= Buffer_recv;
        std::cout << " Receive message: " << Joint_state<< std::endl;
}


void Thread_RunInit()
{
    pthread_t id;     // 创建心跳检测线程
    int ret = pthread_create(&id, NULL, sub_fuc, NULL);
    if(ret != 0)
    {
        std::cout << "Can not create sub_fuc thread.\n";
    }
}
void* sub_fuc(void* arg)
{
while(ros::ok())
{
if(recv_flag>=0)
{
ros::Duration(1).sleep();
ros::spinOnce();
}
//std::cout<<"recvflag="<<recv_flag<<std::endl;
}
}
//#####################################################
//###  4. define the callback Function ###
//#####################################################
void message_feed( const swj_socket::heartrecvflag& msg)
{
   HeartbeatFlag=msg.heartrecvflag;
   recv_flag=msg.recv_flag;
}

//#####################################
//###  5. define the Main Function  ###
//#####################################
int main ( int argc, char **argv )
{
    ros::init ( argc, argv, "socket_recv" );
    ros::AsyncSpinner spinner(1);
    spinner.start();
    log4cxx::Logger::getLogger(ROSCONSOLE_DEFAULT_NAME)->setLevel(
                ros::console::g_level_lookup[ros::console::levels::Debug]);

    ros::NodeHandle NodeHandle;
    ros::Publisher pub_joint_state = NodeHandle.advertise<sensor_msgs::JointState>( INTERFACE_JOINT_STATES, 3, true );
    ros::Publisher pub_recv_msg = NodeHandle.advertise<swj_socket::recv_flag>( INTERFACE_COMMAND, 3, true );
    ros::Publisher pub_statefeed = NodeHandle.advertise<swj_socket::statefeed>( INTERFACE_STATEFEEDBACK, 3, true );
    ros::Subscriber sub = NodeHandle.subscribe("heartbeat_recv", 3, &message_feed );
    ROS_INFO ( "initializing ROS succeed" );
    sensor_msgs::JointState output_joint_state;
    swj_socket::recv_flag output_recvflag;
    swj_socket::statefeed output_statefeed;
    // 3. start the main loop
    while( ros::ok() )
    {        
        Thread_RunInit();
        if(HeartbeatFlag==1)
	{	
	create_socket();
	}
        //sleep(1);
	while (HeartbeatFlag==1&&recv_flag>=0)
	{
	pub_recv_msg.publish( output_recvflag );
        // 3>>1. receive the message from socket
        double start = ros::Time::now().toSec();
	recv_msgs();
        // 3>>2. resolve the Jointstate string and cahnge the corresponding message
	ResolveJointstateString(Joint_state,names,position,velocity,check_node,Pressure,mobot_mode,vehicle_mode);
        // 3>>3. fill the the jointstate message
	int blend_num = BlendJointStates( names, position,velocity,output_joint_state );
	output_recvflag.recv_flag=recv_flag;
	output_statefeed.check_node=check_node;
	output_statefeed.Pressure=Pressure; 
	output_statefeed.mobot_mode=mobot_mode;
	output_statefeed.vehicle_mode=vehicle_mode;   
	pub_joint_state.publish( output_joint_state );
	pub_recv_msg.publish(output_recvflag);
	pub_statefeed.publish(output_statefeed);
	
        // 3>>4. time control
        double sleep_time = LOOP_TIME - ( ros::Time::now().toSec() - start );
        if ( sleep_time > 0 )
        {
            ros::Duration(sleep_time).sleep();
            //ROS_INFO("Cost Time: %lf ms", (LOOP_TIME - sleep_time) * 1000);
        }
        else
            ROS_WARN ( "control loop over time: %f ms", -sleep_time * 1000 );
	
	}
    //ros::Duration(1).sleep();
    std::cout<<"1"<<std::endl;
    sleep(1);
    // close the socket
    close(sock);
    }
    
    ros::waitForShutdown();
    return 0;
}


