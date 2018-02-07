; Auto-generated. Do not edit!


(cl:in-package swj_socket-msg)


;//! \htmlinclude recv_flag.msg.html

(cl:defclass <recv_flag> (roslisp-msg-protocol:ros-message)
  ((recv_flag
    :reader recv_flag
    :initarg :recv_flag
    :type cl:fixnum
    :initform 0))
)

(cl:defclass recv_flag (<recv_flag>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <recv_flag>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'recv_flag)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name swj_socket-msg:<recv_flag> is deprecated: use swj_socket-msg:recv_flag instead.")))

(cl:ensure-generic-function 'recv_flag-val :lambda-list '(m))
(cl:defmethod recv_flag-val ((m <recv_flag>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader swj_socket-msg:recv_flag-val is deprecated.  Use swj_socket-msg:recv_flag instead.")
  (recv_flag m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <recv_flag>) ostream)
  "Serializes a message object of type '<recv_flag>"
  (cl:let* ((signed (cl:slot-value msg 'recv_flag)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <recv_flag>) istream)
  "Deserializes a message object of type '<recv_flag>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'recv_flag) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<recv_flag>)))
  "Returns string type for a message object of type '<recv_flag>"
  "swj_socket/recv_flag")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'recv_flag)))
  "Returns string type for a message object of type 'recv_flag"
  "swj_socket/recv_flag")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<recv_flag>)))
  "Returns md5sum for a message object of type '<recv_flag>"
  "67f5369eb92878e9ba8651b23c2c6c9b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'recv_flag)))
  "Returns md5sum for a message object of type 'recv_flag"
  "67f5369eb92878e9ba8651b23c2c6c9b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<recv_flag>)))
  "Returns full string definition for message of type '<recv_flag>"
  (cl:format cl:nil "int8 recv_flag~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'recv_flag)))
  "Returns full string definition for message of type 'recv_flag"
  (cl:format cl:nil "int8 recv_flag~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <recv_flag>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <recv_flag>))
  "Converts a ROS message object to a list"
  (cl:list 'recv_flag
    (cl:cons ':recv_flag (recv_flag msg))
))
