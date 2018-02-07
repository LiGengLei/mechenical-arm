; Auto-generated. Do not edit!


(cl:in-package com_win-msg)


;//! \htmlinclude command_window.msg.html

(cl:defclass <command_window> (roslisp-msg-protocol:ros-message)
  ((CommandMode
    :reader CommandMode
    :initarg :CommandMode
    :type cl:string
    :initform "")
   (Coordinator
    :reader Coordinator
    :initarg :Coordinator
    :type cl:string
    :initform "")
   (ZeroAxis
    :reader ZeroAxis
    :initarg :ZeroAxis
    :type cl:string
    :initform "")
   (Aux_swing
    :reader Aux_swing
    :initarg :Aux_swing
    :type cl:string
    :initform "")
   (Aux_Home
    :reader Aux_Home
    :initarg :Aux_Home
    :type cl:string
    :initform "")
   (CtrlValues
    :reader CtrlValues
    :initarg :CtrlValues
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0))
   (CommandEmit
    :reader CommandEmit
    :initarg :CommandEmit
    :type cl:fixnum
    :initform 0)
   (ManualSwitch
    :reader ManualSwitch
    :initarg :ManualSwitch
    :type cl:fixnum
    :initform 0))
)

(cl:defclass command_window (<command_window>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <command_window>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'command_window)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name com_win-msg:<command_window> is deprecated: use com_win-msg:command_window instead.")))

(cl:ensure-generic-function 'CommandMode-val :lambda-list '(m))
(cl:defmethod CommandMode-val ((m <command_window>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader com_win-msg:CommandMode-val is deprecated.  Use com_win-msg:CommandMode instead.")
  (CommandMode m))

(cl:ensure-generic-function 'Coordinator-val :lambda-list '(m))
(cl:defmethod Coordinator-val ((m <command_window>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader com_win-msg:Coordinator-val is deprecated.  Use com_win-msg:Coordinator instead.")
  (Coordinator m))

(cl:ensure-generic-function 'ZeroAxis-val :lambda-list '(m))
(cl:defmethod ZeroAxis-val ((m <command_window>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader com_win-msg:ZeroAxis-val is deprecated.  Use com_win-msg:ZeroAxis instead.")
  (ZeroAxis m))

(cl:ensure-generic-function 'Aux_swing-val :lambda-list '(m))
(cl:defmethod Aux_swing-val ((m <command_window>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader com_win-msg:Aux_swing-val is deprecated.  Use com_win-msg:Aux_swing instead.")
  (Aux_swing m))

(cl:ensure-generic-function 'Aux_Home-val :lambda-list '(m))
(cl:defmethod Aux_Home-val ((m <command_window>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader com_win-msg:Aux_Home-val is deprecated.  Use com_win-msg:Aux_Home instead.")
  (Aux_Home m))

(cl:ensure-generic-function 'CtrlValues-val :lambda-list '(m))
(cl:defmethod CtrlValues-val ((m <command_window>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader com_win-msg:CtrlValues-val is deprecated.  Use com_win-msg:CtrlValues instead.")
  (CtrlValues m))

(cl:ensure-generic-function 'CommandEmit-val :lambda-list '(m))
(cl:defmethod CommandEmit-val ((m <command_window>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader com_win-msg:CommandEmit-val is deprecated.  Use com_win-msg:CommandEmit instead.")
  (CommandEmit m))

(cl:ensure-generic-function 'ManualSwitch-val :lambda-list '(m))
(cl:defmethod ManualSwitch-val ((m <command_window>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader com_win-msg:ManualSwitch-val is deprecated.  Use com_win-msg:ManualSwitch instead.")
  (ManualSwitch m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <command_window>) ostream)
  "Serializes a message object of type '<command_window>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'CommandMode))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'CommandMode))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Coordinator))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Coordinator))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'ZeroAxis))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'ZeroAxis))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Aux_swing))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Aux_swing))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'Aux_Home))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'Aux_Home))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'CtrlValues))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'CtrlValues))
  (cl:let* ((signed (cl:slot-value msg 'CommandEmit)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'ManualSwitch)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <command_window>) istream)
  "Deserializes a message object of type '<command_window>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'CommandMode) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'CommandMode) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Coordinator) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Coordinator) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'ZeroAxis) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'ZeroAxis) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Aux_swing) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Aux_swing) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'Aux_Home) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'Aux_Home) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'CtrlValues) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'CtrlValues)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'CommandEmit) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'ManualSwitch) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<command_window>)))
  "Returns string type for a message object of type '<command_window>"
  "com_win/command_window")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'command_window)))
  "Returns string type for a message object of type 'command_window"
  "com_win/command_window")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<command_window>)))
  "Returns md5sum for a message object of type '<command_window>"
  "080fa35438d753e3eb4d759df3a9e3e2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'command_window)))
  "Returns md5sum for a message object of type 'command_window"
  "080fa35438d753e3eb4d759df3a9e3e2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<command_window>)))
  "Returns full string definition for message of type '<command_window>"
  (cl:format cl:nil "string     CommandMode~%string     Coordinator~%string     ZeroAxis~%string     Aux_swing~%string     Aux_Home~%float64[]  CtrlValues~%int8 CommandEmit~%int8 ManualSwitch~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'command_window)))
  "Returns full string definition for message of type 'command_window"
  (cl:format cl:nil "string     CommandMode~%string     Coordinator~%string     ZeroAxis~%string     Aux_swing~%string     Aux_Home~%float64[]  CtrlValues~%int8 CommandEmit~%int8 ManualSwitch~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <command_window>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'CommandMode))
     4 (cl:length (cl:slot-value msg 'Coordinator))
     4 (cl:length (cl:slot-value msg 'ZeroAxis))
     4 (cl:length (cl:slot-value msg 'Aux_swing))
     4 (cl:length (cl:slot-value msg 'Aux_Home))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'CtrlValues) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <command_window>))
  "Converts a ROS message object to a list"
  (cl:list 'command_window
    (cl:cons ':CommandMode (CommandMode msg))
    (cl:cons ':Coordinator (Coordinator msg))
    (cl:cons ':ZeroAxis (ZeroAxis msg))
    (cl:cons ':Aux_swing (Aux_swing msg))
    (cl:cons ':Aux_Home (Aux_Home msg))
    (cl:cons ':CtrlValues (CtrlValues msg))
    (cl:cons ':CommandEmit (CommandEmit msg))
    (cl:cons ':ManualSwitch (ManualSwitch msg))
))
