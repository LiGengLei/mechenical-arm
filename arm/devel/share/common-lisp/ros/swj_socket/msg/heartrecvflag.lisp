; Auto-generated. Do not edit!


(cl:in-package swj_socket-msg)


;//! \htmlinclude heartrecvflag.msg.html

(cl:defclass <heartrecvflag> (roslisp-msg-protocol:ros-message)
  ((heartrecvflag
    :reader heartrecvflag
    :initarg :heartrecvflag
    :type cl:fixnum
    :initform 0)
   (recv_flag
    :reader recv_flag
    :initarg :recv_flag
    :type cl:fixnum
    :initform 0))
)

(cl:defclass heartrecvflag (<heartrecvflag>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <heartrecvflag>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'heartrecvflag)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name swj_socket-msg:<heartrecvflag> is deprecated: use swj_socket-msg:heartrecvflag instead.")))

(cl:ensure-generic-function 'heartrecvflag-val :lambda-list '(m))
(cl:defmethod heartrecvflag-val ((m <heartrecvflag>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader swj_socket-msg:heartrecvflag-val is deprecated.  Use swj_socket-msg:heartrecvflag instead.")
  (heartrecvflag m))

(cl:ensure-generic-function 'recv_flag-val :lambda-list '(m))
(cl:defmethod recv_flag-val ((m <heartrecvflag>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader swj_socket-msg:recv_flag-val is deprecated.  Use swj_socket-msg:recv_flag instead.")
  (recv_flag m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <heartrecvflag>) ostream)
  "Serializes a message object of type '<heartrecvflag>"
  (cl:let* ((signed (cl:slot-value msg 'heartrecvflag)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'recv_flag)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <heartrecvflag>) istream)
  "Deserializes a message object of type '<heartrecvflag>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'heartrecvflag) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'recv_flag) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<heartrecvflag>)))
  "Returns string type for a message object of type '<heartrecvflag>"
  "swj_socket/heartrecvflag")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'heartrecvflag)))
  "Returns string type for a message object of type 'heartrecvflag"
  "swj_socket/heartrecvflag")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<heartrecvflag>)))
  "Returns md5sum for a message object of type '<heartrecvflag>"
  "b4a4cc1afa7750f8ddbae253c9ba88fd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'heartrecvflag)))
  "Returns md5sum for a message object of type 'heartrecvflag"
  "b4a4cc1afa7750f8ddbae253c9ba88fd")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<heartrecvflag>)))
  "Returns full string definition for message of type '<heartrecvflag>"
  (cl:format cl:nil "int8 heartrecvflag~%int8 recv_flag~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'heartrecvflag)))
  "Returns full string definition for message of type 'heartrecvflag"
  (cl:format cl:nil "int8 heartrecvflag~%int8 recv_flag~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <heartrecvflag>))
  (cl:+ 0
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <heartrecvflag>))
  "Converts a ROS message object to a list"
  (cl:list 'heartrecvflag
    (cl:cons ':heartrecvflag (heartrecvflag msg))
    (cl:cons ':recv_flag (recv_flag msg))
))
