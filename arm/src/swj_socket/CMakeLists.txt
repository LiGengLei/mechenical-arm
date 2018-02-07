cmake_minimum_required(VERSION 2.8.3)
project(swj_socket)

find_package(catkin REQUIRED roscpp rospy moveit_core moveit_ros_planning moveit_ros_planning_interface pluginlib cmake_modules std_msgs geometry_msgs sensor_msgs trajectory_msgs control_msgs message_generation tf)
find_package(Boost REQUIRED system filesystem date_time thread)
find_package(Eigen REQUIRED)


################################################
## Declare ROS messages, services and actions ##
################################################
add_message_files(FILES  heartsendflag.msg heartrecvflag.msg recv_flag.msg statefeed.msg)
generate_messages(DEPENDENCIES std_msgs)


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
LINK_DIRECTORIES(/usr/lib/x86_64-linux-gnu/)
LINK_DIRECTORIES(/usr/local/lib)

###########
## Build ##
###########


add_executable(heartbeat_send src/heartbeat_send.cpp)
add_dependencies(heartbeat_send swj_socket_generate_messages_cpp)
target_link_libraries(heartbeat_send ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_executable(heartbeat_recv src/heartbeat_recv.cpp)
add_dependencies(heartbeat_recv swj_socket_generate_messages_cpp)
target_link_libraries(heartbeat_recv ${catkin_LIBRARIES} ${Boost_LIBRARIES} pthread)

add_executable(socket_recv src/socket_recv.cpp)
add_dependencies(socket_recv swj_socket_generate_messages_cpp)
target_link_libraries(socket_recv ${catkin_LIBRARIES} ${Boost_LIBRARIES} pthread)

add_executable(socket_send src/socket_send.cpp)
add_dependencies(socket_send swj_socket_generate_messages_cpp)
target_link_libraries(socket_send ${catkin_LIBRARIES} ${Boost_LIBRARIES} /usr/lib/x86_64-linux-gnu/libusb-1.0.so /usr/local/lib/libhidapi-libusb.so)
#############
## Install ##
#############
#catkin_install_python(PROGRAMS scripts/mobot_keyboard.py DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(DIRECTORY launch DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
install(DIRECTORY config DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
