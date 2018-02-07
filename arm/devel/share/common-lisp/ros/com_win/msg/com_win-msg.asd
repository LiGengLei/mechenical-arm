
(cl:in-package :asdf)

(defsystem "com_win-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "command_window" :depends-on ("_package_command_window"))
    (:file "_package_command_window" :depends-on ("_package"))
  ))