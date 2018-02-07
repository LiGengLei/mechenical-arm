
(cl:in-package :asdf)

(defsystem "swj_socket-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "heartrecvflag" :depends-on ("_package_heartrecvflag"))
    (:file "_package_heartrecvflag" :depends-on ("_package"))
    (:file "heartsendflag" :depends-on ("_package_heartsendflag"))
    (:file "_package_heartsendflag" :depends-on ("_package"))
    (:file "statefeed" :depends-on ("_package_statefeed"))
    (:file "_package_statefeed" :depends-on ("_package"))
    (:file "recv_flag" :depends-on ("_package_recv_flag"))
    (:file "_package_recv_flag" :depends-on ("_package"))
  ))