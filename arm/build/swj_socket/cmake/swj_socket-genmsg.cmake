# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "swj_socket: 4 messages, 0 services")

set(MSG_I_FLAGS "-Iswj_socket:/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(swj_socket_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/statefeed.msg" NAME_WE)
add_custom_target(_swj_socket_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "swj_socket" "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/statefeed.msg" ""
)

get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/recv_flag.msg" NAME_WE)
add_custom_target(_swj_socket_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "swj_socket" "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/recv_flag.msg" ""
)

get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartsendflag.msg" NAME_WE)
add_custom_target(_swj_socket_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "swj_socket" "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartsendflag.msg" ""
)

get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartrecvflag.msg" NAME_WE)
add_custom_target(_swj_socket_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "swj_socket" "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartrecvflag.msg" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(swj_socket
  "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/statefeed.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/swj_socket
)
_generate_msg_cpp(swj_socket
  "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/recv_flag.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/swj_socket
)
_generate_msg_cpp(swj_socket
  "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartsendflag.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/swj_socket
)
_generate_msg_cpp(swj_socket
  "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartrecvflag.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/swj_socket
)

### Generating Services

### Generating Module File
_generate_module_cpp(swj_socket
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/swj_socket
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(swj_socket_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(swj_socket_generate_messages swj_socket_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/statefeed.msg" NAME_WE)
add_dependencies(swj_socket_generate_messages_cpp _swj_socket_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/recv_flag.msg" NAME_WE)
add_dependencies(swj_socket_generate_messages_cpp _swj_socket_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartsendflag.msg" NAME_WE)
add_dependencies(swj_socket_generate_messages_cpp _swj_socket_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartrecvflag.msg" NAME_WE)
add_dependencies(swj_socket_generate_messages_cpp _swj_socket_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(swj_socket_gencpp)
add_dependencies(swj_socket_gencpp swj_socket_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS swj_socket_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(swj_socket
  "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/statefeed.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/swj_socket
)
_generate_msg_lisp(swj_socket
  "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/recv_flag.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/swj_socket
)
_generate_msg_lisp(swj_socket
  "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartsendflag.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/swj_socket
)
_generate_msg_lisp(swj_socket
  "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartrecvflag.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/swj_socket
)

### Generating Services

### Generating Module File
_generate_module_lisp(swj_socket
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/swj_socket
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(swj_socket_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(swj_socket_generate_messages swj_socket_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/statefeed.msg" NAME_WE)
add_dependencies(swj_socket_generate_messages_lisp _swj_socket_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/recv_flag.msg" NAME_WE)
add_dependencies(swj_socket_generate_messages_lisp _swj_socket_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartsendflag.msg" NAME_WE)
add_dependencies(swj_socket_generate_messages_lisp _swj_socket_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartrecvflag.msg" NAME_WE)
add_dependencies(swj_socket_generate_messages_lisp _swj_socket_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(swj_socket_genlisp)
add_dependencies(swj_socket_genlisp swj_socket_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS swj_socket_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(swj_socket
  "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/statefeed.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/swj_socket
)
_generate_msg_py(swj_socket
  "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/recv_flag.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/swj_socket
)
_generate_msg_py(swj_socket
  "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartsendflag.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/swj_socket
)
_generate_msg_py(swj_socket
  "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartrecvflag.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/swj_socket
)

### Generating Services

### Generating Module File
_generate_module_py(swj_socket
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/swj_socket
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(swj_socket_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(swj_socket_generate_messages swj_socket_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/statefeed.msg" NAME_WE)
add_dependencies(swj_socket_generate_messages_py _swj_socket_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/recv_flag.msg" NAME_WE)
add_dependencies(swj_socket_generate_messages_py _swj_socket_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartsendflag.msg" NAME_WE)
add_dependencies(swj_socket_generate_messages_py _swj_socket_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/lgl/master/mechanical_arm/arm/src/swj_socket/msg/heartrecvflag.msg" NAME_WE)
add_dependencies(swj_socket_generate_messages_py _swj_socket_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(swj_socket_genpy)
add_dependencies(swj_socket_genpy swj_socket_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS swj_socket_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/swj_socket)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/swj_socket
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(swj_socket_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/swj_socket)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/swj_socket
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(swj_socket_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/swj_socket)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/swj_socket\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/swj_socket
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(swj_socket_generate_messages_py std_msgs_generate_messages_py)
endif()
