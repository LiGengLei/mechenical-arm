/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include "com_win/command_window.h"
#include <sstream>
#include "../include/com_win/qnode.hpp"


/*****************************************************************************
** Namespaces
*****************************************************************************/
extern std::string CommandMode;
extern std::string Coordinator;
extern std::string ZeroAxis;
extern std::string Aux_swing;
extern std::string Aux_Home;
extern std::vector<double> CtrlValues;
extern int CommandEmit;
extern int ManualSwitch;
std::vector<double> position(12, 0.0);
int check_node;
float Pressure;
std::string mobot_mode;
std::string vehicle_mode;
std::string Command_string;
namespace com_win {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
	init_argc(argc),
	init_argv(argv)
	{}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}

bool QNode::init() {
	ros::init(init_argc,init_argv,"com_win");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
        chatter_publisher = n.advertise<com_win::command_window>("Command_window", 1000);
	sub1 = n.subscribe("interface_statefeed", 3, &QNode::interface_state_Received, this );
	sub2 = n.subscribe("joint_states", 3, &QNode::joint_states_Received, this);
	sub3 = n.subscribe("command_string", 3, &QNode::Command_stringSend,this );
	start();
	return true;
}

void QNode::joint_states_Received(const sensor_msgs::JointState& msg)
{
	position.clear();	
	position = msg.position;
        std::cout<<"size"<<position.size()<<std::endl;
}
void QNode::interface_state_Received(const swj_socket::statefeed& msg)
{
	check_node = msg.check_node;
	Pressure   = msg.Pressure;
	mobot_mode = msg.mobot_mode;
	vehicle_mode = msg.vehicle_mode;
}
void QNode::Command_stringSend(const std_msgs::String& msg)
{
	Command_string = msg.data;
}
bool QNode::init(const std::string &master_url, const std::string &host_url) {
	std::map<std::string,std::string> remappings;
	remappings["__master"] = master_url;
	remappings["__hostname"] = host_url;
	ros::init(remappings,"com_win");
	if ( ! ros::master::check() ) {
		return false;
	}
	ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
        chatter_publisher = n.advertise<com_win::command_window>("Command_window", 1000);
	start();
	return true;
}

void QNode::run() 
{
    ros::Rate loop_rate(50);
    while ( ros::ok() ) 
    {
    com_win::command_window msg;
    msg.CommandMode=CommandMode;
    msg.Coordinator=Coordinator;
    msg.ZeroAxis=ZeroAxis;
    msg.Aux_swing=Aux_swing;
    msg.Aux_Home=Aux_Home;
    msg.ManualSwitch=ManualSwitch;
    msg.CtrlValues.insert(msg.CtrlValues.begin(),CtrlValues.begin(),CtrlValues.end());
    msg.CommandEmit=CommandEmit;
    chatter_publisher.publish(msg);
    //log(Info,std::string("I sent: ")+msg.data);
    ros::spinOnce();
    loop_rate.sleep();
    }
    std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
    Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::log( const LogLevel &level, const std::string &msg) {
	logging_model.insertRows(logging_model.rowCount(),1);
	std::stringstream logging_model_msg;
	switch ( level ) {
		case(Debug) : {
				ROS_DEBUG_STREAM(msg);
				logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Info) : {
				ROS_INFO_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Warn) : {
				ROS_WARN_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Error) : {
				ROS_ERROR_STREAM(msg);
				logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Fatal) : {
				ROS_FATAL_STREAM(msg);
				logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
				break;
		}
	}
	QVariant new_row(QString(logging_model_msg.str().c_str()));
	logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
	Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}

}  // namespace com_win
