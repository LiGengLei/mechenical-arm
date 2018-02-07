/**
 * @file /include/com_win/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef com_win_QNODE_HPP_
#define com_win_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <string>
#include <QThread>
#include <QStringListModel>
#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>
#include "swj_socket/statefeed.h"

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace com_win {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
	void run();
	void joint_states_Received(const sensor_msgs::JointState& msg);
	void interface_state_Received(const swj_socket::statefeed& msg);
	void Command_stringSend(const std_msgs::String& msg);

	/*********************
	** Logging
	**********************/
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

	QStringListModel* loggingModel() { return &logging_model; }
	void log( const LogLevel &level, const std::string &msg);

Q_SIGNALS:
	void loggingUpdated();
    void rosShutdown();

private:
	int init_argc;
	char** init_argv;
	ros::Publisher chatter_publisher;
	ros::Subscriber sub1;
	ros::Subscriber sub2;
	ros::Subscriber sub3;
    QStringListModel logging_model;
};

}  // namespace com_win

#endif /* com_win_QNODE_HPP_ */
