#include "ros/ros.h"
#include "com_win/command_window.h"
#include "swj_socket/heartrecvflag.h"
#include "../include/swj_socket/pmd.h"
#include "../include/swj_socket/usb-20X.h"
#include "../include/swj_socket/libusb.h"
#include "std_msgs/String.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <sys/time.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>
#include <log4cxx/logger.h>
#include <errno.h>

#define MAX_COUNT     (0xffff)
#define FALSE 0
#define TRUE 1

#define _in   const &   // input parameter of right value
#define _inc  const     // input parameter of right value
#define _out        &   // output parameter of left value
#define _ret  const     // return by value (use c++ complier optimaization)

#define		COMMAND_STRING          "/command_string"
#define         SOCKET_IP_ADDR          "192.168.1.2"
#define         SOCKET_PORT_ADDR        4000
#define         SOL_SOCKET              1
#define         SO_REUSEADDR            2
#define         LISTEN_QUEUE            20
#define         LOOP_TIME               0.020
#define         SERVER_THREAD_LOOP      15

#define     ARMJ_NUM        6
#define     ARMC_NUM        6
#define     BASE_NUM        4
#define     SWING_NUM       2
#define     GRIP_NUM        1
std::string CommandMode;
std::string Coordinator;
std::string ZeroAxis;
std::string Aux_swing;
std::string Aux_Home;
std::vector<double> CtrlValues;
int CommandEmit;
int ManualSwitch;
std::vector<double> advalues;
libusb_device_handle *udev = NULL;
uint8_t input,D0,D1,D2,D3;
float table_AIN[NCHAN_USB20X][2];

int mServerSocket;
int mClientSocket;
std::string mServerCommand;
std::string mAuxCommand;
std::string mOutputCommand;
std::vector<double> mValues;
std::vector<double> mValues_pre;
int HeartbeatFlag=1;
//#####################################################
//###  1. define the ad_init  ###
//#####################################################
int ad_init()
{
    struct tm calDate;
    udev = NULL;
    int ret = libusb_init(NULL);
    if (ret < 0)
    {
        perror("usb_device_find_USB_MCC: Failed to initialize libusb");
        //exit(1);
    }

    if ((udev = usb_device_find_USB_MCC(USB201_PID, NULL)))
    {
        printf("Success, found a USB 201!\n");
    }
    else
    {
        printf("Failure, did not find a USB 201!\n");
        return 0;
    }

    usbBuildGainTable_USB20X(udev, table_AIN);
    usbCalDate_USB20X(udev, &calDate);
    usbDTristateW_USB20X(udev,0xff);
    return 0;
}
//#####################################
//###  2. define the ad_collector Function  ###
//#####################################
int adcard_collect()
{
    advalues.clear();
    input = usbDPort_USB20X(udev);
    D0=(input)&0x1;
    D1=(input>>1)&0x1;
    D2=(input>>2)&0x1;
    D3=(input>>3)&0x1;  
    //std::cout<<"input="<<D1<<std::endl;

    for (uint8_t channel = 0; channel < 7; channel++)
    {
        uint16_t value = usbAIn_USB20X(udev, channel);
        value = rint(value*table_AIN[channel][0] + table_AIN[channel][0]);
        //std::cout << "Slope [" << table_AIN[channel][0] << "], Offset [" << table_AIN[channel][1] << "]." << std::endl;
        advalues.push_back(volts_USB20X(value));
	//double x=0;
        //advalues.push_back(2.5);
    }

    // NOTE: the following codes need to be tested and modified
    CommandEmit = true;
    //CommandEmit = false;
    if(D1==0)
    {
        CommandMode="BASE";
        for (size_t i = 0; i < 3; ++i)
        {
            /*if( advalues[i]<=1 )
            {
                advalues[i] = -9.0;
                CommandEmit = true;
            }
            else if((advalues[i]>1)&(advalues[i]<=1.3))
            {
                advalues[i] = -6.0;
                CommandEmit = true;
            }
            else if((advalues[i]>1.3)&(advalues[i]<1.6))
            {
                advalues[i] = -3.0;
            }
            else if((advalues[i]>=1.6)&(advalues[i]<=2.9))
            {
                advalues[i] = 0;
            }
            else if((advalues[i]>2.9)&(advalues[i]<=3.2))
            {
                advalues[i] = 3;
            }
            else if((advalues[i]>3.2)&(advalues[i]<3.4))
            {
                advalues[i] = 6;
            }
            else
                advalues[i] = 9;*/
	    if( (advalues[i]-2.5)>1)
		advalues[i] = 6;
	    else if( (advalues[i]-2.5) < -1 )
       	    {
                advalues[i] = -6;
            }
            else
                advalues[i]=0;
        }
        if( (advalues[3]-2.5)>1 )
        {
            advalues[3] = 1;
        }
        else if( (advalues[3]-2.5) < -1 )
        {
            advalues[3] = -1;
        }
        else
            advalues[3]=0;
        for (size_t i = 4; i < 7; ++i)
        {
            if( (advalues[i]-2.5)>1 )
            {
                advalues[i] = 2;
            }
            else if( (advalues[i]-2.5) < -1 )
            {
                advalues[i] = -2;
            }
            else
                advalues[i]=0;
        }
        if((advalues[4]!=0)||(advalues[6]!=0))
        {
            CommandMode="SWING";
            Aux_swing="MOVE";
        }
    }
    else
    {   if(D2==1)
        {
            CommandMode="ARMC";
            for (size_t i = 0; i < 6; ++i)
            {
                if( (advalues[i]-2.5) > 1 )
                {
                    if(i<3)
                        advalues[i] = 0.5;
                    else
                        advalues[i] = 0.2;
                    CommandEmit = true;
                }
                else if( (advalues[i]-2.5) < -1 )
                {
                    if(i<3)
                        advalues[i] = -0.5;
                    else
                        advalues[i] = -0.2;
                    CommandEmit = true;
                }
                else
                {
                    advalues[i] = 0.0;
                }
             }
	     advalues[6] = 0.0;
        }
        else
        {
            CommandMode="ARMJ";
            for (size_t i = 0; i < 6; ++i)
            {
                if( (advalues[i]-2.5) > 0.8 )
                {
                    advalues[i] = 0.15;
                    CommandEmit = true;
                }
                else if( (advalues[i]-2.5) < -0.8 )
                {
                    advalues[i] = -0.15;
                    CommandEmit = true;
                }
                else
                {
                    advalues[i] = 0.0;
                }
            }
            if((advalues[6]-2.5) > 1)
            {
               CommandMode="GRIP";
               advalues[6]=1;
            }
            else if((advalues[6]-2.5) < -1)
            {
               CommandMode="GRIP";
               advalues[6]=-1;
            }
	    else
		advalues[6]=0;
        }
    }
    return 0;
}

//#####################################
//###  3. define the socket Function  ###
//#####################################
int create_socket(std::string _in ServerIP,
                  int _in ServerPort,
                  int _out server_socket,
                  int _out client_socket)
{
    // create the server socket description
    std::cout<<"ddd"<<std::endl;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    std::cout<<"aaa"<<std::endl;
    while (server_socket < 0)
    {
        std::cout << "[SOCKET_ERROR] Create socket failed, exiting." <<std::endl;
        sleep(1);
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
    }

    // bind IP and Port with the server socket description
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ServerIP.c_str());// "127.0.0.1"
    server_addr.sin_port = htons(ServerPort);

    int opt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    std::cout<<"bbb"<<std::endl;
    while( bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0 )
    {
        std::cout << "[SOCKET_ERROR] Server bind failed, exiting." << std::endl;
        sleep(1);
        bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    }

    // server socket start to listen
    while( listen(server_socket, LISTEN_QUEUE) < 0 )
    {
        std::cout << "[SOCKET_ERROR] Server listen failed, exiting." << std::endl;
        sleep(1);
        listen(server_socket, LISTEN_QUEUE);
    }
    std::cout<<"ccc"<<std::endl;
    // server socket start to accept client sockets
    struct sockaddr_in client_addr;
    socklen_t client_addr_length = sizeof(client_addr);

    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_length);
    while ( client_socket < 0 )
    {
        std::cout << "[SOCKET_ERROR] create_socket: cannot connect to client socket." << std::endl;
        sleep(1);
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_length);
    }

        std::cout << "Connect to client successfully." <<std::endl;

    return 0;
}

int send_message( int _in client_socket, std::string _in CommandString )
{
    char Send_Buffer[150];
    strcpy(Send_Buffer, CommandString.c_str());
    socklen_t send_length = send(client_socket, Send_Buffer, 150, 0);
    if ( (int)send_length < 0 )
    {
        std::cout << "[SOCKET_ERROR] send_message: cannot send command string." << std::endl;
        return -1;
    }
    memset(Send_Buffer,0,150);
    return 0;
}

void close_socket(int _in server_socket, int _in client_socket)
{
    close(client_socket);
    close(server_socket);
}
//#####################################################
//###  4. define the callback Function ###
//#####################################################
void message_feed_heart( const swj_socket::heartrecvflag& msg)
{
   HeartbeatFlag=msg.heartrecvflag;
}
void message_feed_command( const com_win::command_window& msg)
{
   CommandMode=msg.CommandMode;
   Coordinator=msg.Coordinator;
   ZeroAxis=msg.ZeroAxis;
   Aux_swing=msg.Aux_swing;
   Aux_Home=msg.Aux_Home;
   CtrlValues.insert(CtrlValues.begin(),msg.CtrlValues.begin(),msg.CtrlValues.end());
   CommandEmit=msg.CommandEmit;
   ManualSwitch=msg.ManualSwitch;
}

template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
}
//#####################################################
//###  5. define the commandhandller Function ###
//#####################################################
class StringCommandHandller
{
public:
    StringCommandHandller(std::string _in command_id, std::string _in frame, std::vector<double> _out values)
        : Command(command_id),
          UserFrame(frame)
    {
        joint_values.clear();
        joint_values.resize(values.size());
        for (size_t i = 0; i > values.size(); ++i)
            joint_values[i] = values[i];
    }

    StringCommandHandller()
        : Command(""),
          UserFrame("")
    {
        joint_values.clear();
    }

    ~StringCommandHandller()
    {
    }

    // 1. reset the member variables
    inline void Reset(std::string _in command, std::string _in frame, std::vector<double> _in values)
    {
        Command     = command;
        UserFrame   = frame;
        joint_values.clear();
        joint_values.resize(values.size());
        for (size_t i = 0; i < values.size(); ++i)
            joint_values[i] = values[i];
    }

    // 2. get the member variable - Command
    inline std::string _ret getCommand()
    {
        return Command;
    }

    // 3. get the member variable - UserFrame
    inline std::string _ret getUserFrame()
    {
        return UserFrame;
    }

    // 4. get the member variable - joint_values
    inline std::vector<double> _ret getJointValues()
    {
        return joint_values;
    }

    // 5. translate joint_values<double> to values_string<string>
    inline void TanslateToJointValuesString( std::vector<std::string> _out output)
    {
        output.clear();
        output.resize(joint_values.size());
        for (size_t i = 0; i < joint_values.size(); ++i)
        {
            output[i] = to_string(joint_values[i]);
            //std::cout << "output[" << i+1 << "]=" << output[i] << std::endl;
        }
    }

    // 6. translate to a line of string command
    inline void TanslateToCommandString( std::string _in command,
                                         std::string _in frame,
                                         std::vector<double> _in values,
                                         std::string _out output)
    {
        Reset(command, frame, values);
        std::vector<std::string> JointValuesString;
        TanslateToJointValuesString( JointValuesString );

        std::vector<std::string> input;
        input.clear();
        input.push_back( Command );
        input.push_back( UserFrame );
        input.insert( input.end(), JointValuesString.begin(), JointValuesString.end() );

        output = boost::algorithm::join( input, " ");
        std::cout << "output:" << output <<std::endl;
    }

    // 7. translate to a simple line of string command (only command and frame)
    inline void TanslateToSimpleCommandString( std::string _in command,
                                               std::string _in frame,
                                               std::string _out output)
    {
        std::vector<double> values;
        values.clear();
        Reset(command, frame, values);

        std::vector<std::string> input;
        input.clear();
        input.push_back( Command );
        input.push_back( UserFrame );

        output = boost::algorithm::join( input, " ");
        std::cout << "output:" << output <<std::endl;
    }

    // 8. resolve a line of command string to real control command
    inline void ResolveCommandString( std::string _in input )
    {
        std::vector<std::string> result;
        boost::split( result, input, boost::is_any_of(" "), boost::algorithm::token_compress_on );
        std::string COMMAND = result[0];
        std::string FRAME  = "";
        std::vector<double> VALUES;
        VALUES.clear();

        if (COMMAND == "ZERO")
        {
            FRAME = result[1];
        }
        else if ((COMMAND == "BASE")||(COMMAND == "SWING")||(COMMAND == "GRIP"))
        {
            for (size_t i = 1; i < result.size(); ++i)
            {
                VALUES.push_back( atof(result[i].c_str()) );
            }
        }
        else if ((COMMAND == "ARMJ")||(COMMAND == "ARMC"))
        {
            FRAME = result[1];
            for (size_t i = 2; i < result.size(); ++i)
            {
                VALUES.push_back( atof(result[i].c_str()) );
            }
        }

        Reset( COMMAND, FRAME, VALUES );
    }

private:
    std::string Command;
    std::string UserFrame;
    std::vector<double> joint_values;
};
//#####################################################
//###  6. define the sever_init Function ###
//#####################################################    
void sever_init()
{
// 1. init the command strings and values
        CommandMode = "OTHERS";
        Coordinator = "END_EFFECTOR";
        ZeroAxis    = "";
        Aux_swing   = "HOMESTOP";
        CommandEmit = 0;
        ManualSwitch = 0;
        CtrlValues.resize(6);
        for (size_t i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        advalues.resize(7);
        for (size_t i = 0; i < 7; ++i)
            advalues[i] = 0.0;
}
//#####################################
//###  7. define the Main Function  ###
//#####################################
int main ( int argc, char **argv )
{
    ros::init ( argc, argv, "socket_send" );
    ros::AsyncSpinner spinner(1);
    spinner.start();
    log4cxx::Logger::getLogger(ROSCONSOLE_DEFAULT_NAME)->setLevel(
                ros::console::g_level_lookup[ros::console::levels::Debug]);

    ros::NodeHandle NodeHandle;
    ros::Publisher  pub_Command_string = NodeHandle.advertise<std_msgs::String>( COMMAND_STRING, 3, true );
    ros::Subscriber sub_heartbeat = NodeHandle.subscribe("heartbeat_recv", 3, &message_feed_heart );
    ros::Subscriber sub_commandwindow = NodeHandle.subscribe("Command_window", 3, &message_feed_command );
    ROS_INFO ( "initializing ROS succeed" );
    ad_init();
    sever_init();
    StringCommandHandller mStringHandller;
    std_msgs::String Command;
    // 1. start the main loop
    while( ros::ok() )
    {  
	ros::spinOnce();
	if(HeartbeatFlag==1)
        { 
		// 2. create the server socket
                int resp = create_socket(SOCKET_IP_ADDR, SOCKET_PORT_ADDR, mServerSocket, mClientSocket);
                while ( resp < 0 )
                {
                    std::cout << "Create socket failed, retry after 1 seconds." << std::endl;
                    sleep(1);
                    resp = create_socket(SOCKET_IP_ADDR, SOCKET_PORT_ADDR, mServerSocket, mClientSocket);
                }

        }
        while(1)  
	{
	if(HeartbeatFlag==1)
        {
            // 3>>1. get the start time in msecs
	    double start = ros::Time::now().toSec();
            // 3>>2. get the vector - input_values, from screen or joystick,
            // NOTE: CommandMode in joystick should be determined in adcard_collect()
            std::vector<double> input_values;
	    
            input_values.clear();
	    ros::spinOnce();
            if (!ManualSwitch) // control by the screen
            {
                for(size_t i = 0; i < 6; ++i)
                    input_values.push_back(CtrlValues[i]);
            }
            else // control by the joystick
            {
                adcard_collect();
		//ros::Duration(0.01).sleep();
                for(size_t i = 0; i < 7; ++i)
                    input_values.push_back(advalues[i]);
		
            }

            // 3>>3. get the variable - mServerCommand
            if (CommandEmit == 1)
                mServerCommand = CommandMode;
            else
                mServerCommand = "OTHERS";

            // 3>>4. get the variable - mAuxCommand
            if ((mServerCommand == "ARMJ")||(mServerCommand == "ARMC"))
            {
                mAuxCommand = Coordinator;
            }
            else if (mServerCommand == "ZERO")
            {
                mAuxCommand = ZeroAxis;
            }
            else if (mServerCommand == "SWING")
            {
                mAuxCommand = Aux_swing;
            }
            else if (mServerCommand == "HOME")
            {
                mAuxCommand = Aux_Home;
            }
            else
            {
                mAuxCommand = "";
            }

            // 3>>5. get the variable - mValues, the command explaination in joystick should be conducted
	   
	    mValues.clear();
            if(mServerCommand == "ARMJ")
            {
                for (size_t i = 0; i < ARMJ_NUM; ++i)
                    mValues.push_back(input_values[i]);
            }
            else if(mServerCommand == "ARMC")
            {
                for (size_t i = 0; i < ARMC_NUM; ++i)
                    mValues.push_back(input_values[i]);
            }
            else if(mServerCommand == "BASE")
            {
                for (size_t i = 0; i < BASE_NUM; ++i)
                    mValues.push_back(input_values[i]);
            }
            else if((mServerCommand == "SWING")&(!ManualSwitch))
            {
                for (size_t i = 0; i < SWING_NUM; ++i)
                    mValues.push_back(input_values[i]);
            }
            else if((mServerCommand == "SWING")&(ManualSwitch))
            {
		    for (size_t i = 0; i < (SWING_NUM+1); i=i+2)                  
		    mValues.push_back(input_values[i+4]);
            }
            else if((mServerCommand == "GRIP")&(!ManualSwitch))
            {
                for (size_t i = 0; i < GRIP_NUM; ++i)
                    mValues.push_back(input_values[i]);
            }
            else if((mServerCommand == "GRIP")&(ManualSwitch))
            {
                for (size_t i = 0; i < GRIP_NUM; ++i)
                    mValues.push_back(input_values[i+6]);
            }
            else if(mServerCommand == "HOME")
            {
		                
		for (size_t i = 0; i < ARMJ_NUM; ++i)
                    mValues.push_back(input_values[i]);
            }
            // 3>>6. transfer the command to a line of command string, and send the string
            if (mServerCommand != "OTHERS")
            {
               if(ManualSwitch&((advalues[0]+advalues[1]+advalues[2]+advalues[3]+advalues[4]+advalues[5]+advalues[6])==0))
	       {
               CommandEmit = 0;
	       Command.data="Null";
	       pub_Command_string.publish(Command);
	       }
               else
               {
                mStringHandller.TanslateToCommandString( mServerCommand, mAuxCommand, mValues, mOutputCommand);
                int resp = send_message( mClientSocket, mOutputCommand );
		Command.data=mOutputCommand;
	        pub_Command_string.publish(Command);
                if (resp < 0)
                {
                    std::cout << "[SOCKET_ERROR] send_message: cannot send command string." << std::endl;
                }
                }

                //msleep(200);
            }
	    else
	        Command.data="Null";
	        pub_Command_string.publish(Command);
	    
            // 4. get the end time in msecs, control the sleep time (default: 500ms)
            double sleep_time = LOOP_TIME - ( ros::Time::now().toSec() - start );
            if ( sleep_time > 0 )
            {
                ros::Duration(sleep_time).sleep();
                //ROS_INFO("Cost Time: %lf ms", (LOOP_TIME - sleep_time) * 1000);
            }
            //else
                //ROS_WARN ("control loop over time: %f ms", -sleep_time * 1000);
        }
            else
            break;
	}
        close_socket(mServerSocket, mClientSocket);
        sleep(1);
        std::cout<<"Get out of the run process loop."<<std::endl;
    }
    
    ros::waitForShutdown();
    return 0;
}


