; Auto-generated. Do not edit!


(cl:in-package swj_socket-msg)


;//! \htmlinclude statefeed.msg.html

(cl:defclass <statefeed> (roslisp-msg-protocol:ros-message)
  ((check_node
    :reader check_node
    :initarg :check_node
    :type cl:integer
    :initform 0)
   (Pressure
    :reader Pressure
    :initarg :Pressure
    :type cl:float
    :initform 0.0)
   (mobot_mode
    :reader mobot_mode
    :initarg :mobot_mode
    :type cl:string
    :initform "")
   (vehicle_mode
    :reader vehicle_mode
    :initarg :vehicle_mode
    :type cl:string
    :initform ""))
)

(cl:defclass statefeed (<statefeed>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <statefeed>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'statefeed)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name swj_socket-msg:<statefeed> is deprecated: use swj_socket-msg:statefeed instead.")))

(cl:ensure-generic-function 'check_node-val :lambda-list '(m))
(cl:defmethod check_node-val ((m <statefeed>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader swj_socket-msg:check_node-val is deprecated.  Use swj_socket-msg:check_node instead.")
  (check_node m))

(cl:ensure-generic-function 'Pressure-val :lambda-list '(m))
(cl:defmethod Pressure-val ((m <statefeed>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader swj_socket-msg:Pressure-val is deprecated.  Use swj_socket-msg:Pressure instead.")
  (Pressure m))

(cl:ensure-generic-function 'mobot_mode-val :lambda-list '(m))
(cl:defmethod mobot_mode-val ((m <statefeed>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader swj_socket-msg:mobot_mode-val is deprecated.  Use swj_socket-msg:mobot_mode instead.")
  (mobot_mode m))

(cl:ensure-generic-function 'vehicle_mode-val :lambda-list '(m))
(cl:defmethod vehicle_mode-val ((m <statefeed>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader swj_socket-msg:vehicle_mode-val is deprecated.  Use swj_socket-msg:vehicle_mode instead.")
  (vehicle_mode m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <statefeed>) ostream)
  "Serializes a message object of type '<statefeed>"
  (cl:let* ((signed (cl:slot-value msg 'check_node)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'Pressure))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'mobot_mode))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'mobot_mode))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'vehicle_mode))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'vehicle_mode))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <statefeed>) istream)
  "Deserializes a message object of type '<statefeed>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'check_node) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'Pressure) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'mobot_mode) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'mobot_mode) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'vehicle_mode) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'vehicle_mode) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<statefeed>)))
  "Returns string type for a message object of type '<statefeed>"
  "swj_socket/statefeed")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'statefeed)))
  "Returns string type for a message object of type 'statefeed"
  "swj_socket/statefeed")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<statefeed>)))
  "Returns md5sum for a message object of type '<statefeed>"
  "6e249da119c5a3c0bedbd44f53561933")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'statefeed)))
  "Returns md5sum for a message object of type 'statefeed"
  "6e249da119c5a3c0bedbd44f53561933")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<statefeed>)))
  "Returns full string definition for message of type '<statefeed>"
  (cl:format cl:nil "int32 check_node~%float32 Pressure~%string mobot_mode~%string vehicle_mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'statefeed)))
  "Returns full string definition for message of type 'statefeed"
  (cl:format cl:nil "int32 check_node~%float32 Pressure~%string mobot_mode~%string vehicle_mode~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <statefeed>))
  (cl:+ 0
     4
     4
     4 (cl:length (cl:slot-value msg 'mobot_mode))
     4 (cl:length (cl:slot-value msg 'vehicle_mode))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <statefeed>))
  "Converts a ROS message object to a list"
  (cl:list 'statefeed
    (cl:cons ':check_node (check_node msg))
    (cl:cons ':Pressure (Pressure msg))
    (cl:cons ':mobot_mode (mobot_mode msg))
    (cl:cons ':vehicle_mode (vehicle_mode msg))
))
