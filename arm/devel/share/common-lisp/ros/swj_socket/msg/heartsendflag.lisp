; Auto-generated. Do not edit!


(cl:in-package swj_socket-msg)


;//! \htmlinclude heartsendflag.msg.html

(cl:defclass <heartsendflag> (roslisp-msg-protocol:ros-message)
  ((heartsendflag
    :reader heartsendflag
    :initarg :heartsendflag
    :type cl:fixnum
    :initform 0))
)

(cl:defclass heartsendflag (<heartsendflag>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <heartsendflag>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'heartsendflag)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name swj_socket-msg:<heartsendflag> is deprecated: use swj_socket-msg:heartsendflag instead.")))

(cl:ensure-generic-function 'heartsendflag-val :lambda-list '(m))
(cl:defmethod heartsendflag-val ((m <heartsendflag>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader swj_socket-msg:heartsendflag-val is deprecated.  Use swj_socket-msg:heartsendflag instead.")
  (heartsendflag m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <heartsendflag>) ostream)
  "Serializes a message object of type '<heartsendflag>"
  (cl:let* ((signed (cl:slot-value msg 'heartsendflag)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <heartsendflag>) istream)
  "Deserializes a message object of type '<heartsendflag>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'heartsendflag) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<heartsendflag>)))
  "Returns string type for a message object of type '<heartsendflag>"
  "swj_socket/heartsendflag")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'heartsendflag)))
  "Returns string type for a message object of type 'heartsendflag"
  "swj_socket/heartsendflag")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<heartsendflag>)))
  "Returns md5sum for a message object of type '<heartsendflag>"
  "77c4bcaf053909a4f759348601592667")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'heartsendflag)))
  "Returns md5sum for a message object of type 'heartsendflag"
  "77c4bcaf053909a4f759348601592667")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<heartsendflag>)))
  "Returns full string definition for message of type '<heartsendflag>"
  (cl:format cl:nil "int8 heartsendflag~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'heartsendflag)))
  "Returns full string definition for message of type 'heartsendflag"
  (cl:format cl:nil "int8 heartsendflag~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <heartsendflag>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <heartsendflag>))
  "Converts a ROS message object to a list"
  (cl:list 'heartsendflag
    (cl:cons ':heartsendflag (heartsendflag msg))
))
