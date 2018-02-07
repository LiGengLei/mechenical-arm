cmake_minimum_required(VERSION 2.8.3)
project(mobot_description)

find_package(catkin REQUIRED roscpp rospy moveit_core moveit_ros_planning moveit_ros_planning_interface pluginlib cmake_modules std_msgs geometry_msgs sensor_msgs trajectory_msgs control_msgs message_generation tf)
find_package(Boost REQUIRED system filesystem date_time thread)
find_package(Eigen REQUIRED)


################################################
## Declare ROS messages, services and actions ##
################################################
#add_message_files(FILES Keyboard.msg ArmControl.msg SwingControl.msg GripControl.msg InterfaceJointVel.msg command_list.msg heartsendflag.msg heartrecvflag.msg)
#generate_messages(DEPENDENCIES std_msgs)


###################################
## catkin specific configuration ##
###################################
catkin_package( CATKIN_DEPENDS moveit_core moveit_ros_planning_interface interactive_markers std_msgs geometry_msgs sensor_msgs trajectory_msgs control_msgs message_runtime tf)


#############
## includes #
#############
include_directories(SYSTEM)
include_directories(${Boost_INCLUDE_DIR})
include_directories(${EIGEN_INCLUDE_DIRS})
include_directories(${catkin_INCLUDE_DIRS})
link_directories(${catkin_LIBRARY_DIRS})
INCLUDE_DIRECTORIES(/usr/include/)
LINK_DIRECTORIES(/usr/lib/)

###########
## Build ##
###########

#############
## Install ##
#############

install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
