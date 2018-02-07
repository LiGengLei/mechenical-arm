/**
 * @file /include/com_win/main_window.hpp
 *
 * @brief Qt based gui for com_win.
 *
 * @date November 2010
 **/
#ifndef com_win_MAIN_WINDOW_H
#define com_win_MAIN_WINDOW_H

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/QMainWindow>
#include "ui_mainwindow.h"
#include "qnode.hpp"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace com_win {

/*****************************************************************************
** Interface [MainWindow]
*****************************************************************************/
/**
 * @brief Qt central, all operations relating to the view part here.
 */
class MainWindow : public QMainWindow {
Q_OBJECT

public:
	MainWindow(int argc, char** argv, QWidget *parent = 0);
	~MainWindow();

public Q_SLOTS:
	/******************************************
	** Auto-connections (connectSlotsByName())
	*******************************************/
  /*real-time display*/
      void real_time();
      void slotUpdateTimer();
  /********************
  ** The Menu Button **
  *********************/
      void on_Arm_Vehicle_clicked();
      void on_Arm_Zero_clicked();
      void on_Coordinator_clicked();
      void on_Vehicle_clicked();
      void on_Manual_clicked();
  /****************************
   ** Check and Update States **
   *****************************/
      void on_GetADValue_clicked();
      void on_Serv_Connect_clicked();
      void on_Serv_Disconnect_clicked();
      void on_CheckStatus_clicked();
      void on_UpdateState_clicked();
      void on_No_Limit_clicked();
      /*******************************************************
      ** The Command States in Page 1 - Manipulator Control **
      ********************************************************/
          void on_Arm_Stop_pressed();
          void on_Arm_Stop_released();
          void on_Arm_Move_pressed();
          void on_Arm_Move_released();
          void on_Arm_Joint_clicked();
          void on_Arm_Cartesian_clicked();
          void on_Gripper_clicked();

          void on_Gripper_Open_pressed();
          void on_Gripper_Open_released();
          void on_Gripper_Close_pressed();
          void on_Gripper_Close_released();

          void on_Axis1_F_pressed();
          void on_Axis1_F_released();
          void on_Axis1_R_pressed();
          void on_Axis1_R_released();

          void on_Axis2_F_pressed();
          void on_Axis2_F_released();
          void on_Axis2_R_pressed();
          void on_Axis2_R_released();

          void on_Axis3_F_pressed();
          void on_Axis3_F_released();
          void on_Axis3_R_pressed();
          void on_Axis3_R_released();

          void on_Axis4_F_pressed();
          void on_Axis4_F_released();
          void on_Axis4_R_pressed();
          void on_Axis4_R_released();

          void on_Axis5_F_pressed();
          void on_Axis5_F_released();
          void on_Axis5_R_pressed();
          void on_Axis5_R_released();

          void on_Axis6_F_pressed();
          void on_Axis6_F_released();
          void on_Axis6_R_pressed();
          void on_Axis6_R_released();

          void on_Axis7_F_pressed();
          void on_Axis7_F_released();
          void on_Axis7_R_pressed();
          void on_Axis7_R_released();

      /****************************************************
      ** The Command States in Page 2 - Manipulator Zero **
      *****************************************************/
          void on_Axis1_Zero_pressed();
          void on_Axis1_Zero_released();

          void on_Axis2_Zero_pressed();
          void on_Axis2_Zero_released();

          void on_Axis3_Zero_pressed();
          void on_Axis3_Zero_released();

          void on_Axis4_Zero_pressed();
          void on_Axis4_Zero_released();

          void on_Axis5_Zero_pressed();
          void on_Axis5_Zero_released();

          void on_Axis6_Zero_pressed();
          void on_Axis6_Zero_released();

          void on_Axis7_Zero_pressed();
          void on_Axis7_Zero_released();

          void on_Gripper_Zero_pressed();
          void on_Gripper_Zero_released();

          void on_AxisAll_Zero_pressed();
          void on_AxisAll_Zero_released();

          void on_Stop_Zero_pressed();
          void on_Stop_Zero_released();

      /***********************************************
      ** The Command States in Page 3 - Coordinator **
      ************************************************/
          void on_Base_Link_clicked();
          void on_Link_1_clicked();
          void on_Link_2_clicked();
          void on_Link_3_clicked();
          void on_Link_4_clicked();
          void on_Link_5_clicked();
          void on_Link_6_clicked();
          void on_Link_7_clicked();
          void on_End_Effector_clicked();

      /***************************************************
      ** The Command States in Page 4 - HOME Control **
      ****************************************************/
          void on_HOMEASTOP_clicked();

          void on_HOME_3_clicked();
	 
          void on_HOMESTOP_3_pressed();
          void on_HOMESTOP_3_released();

          void on_AXIS1_pressed();
          void on_AXIS1_released();

          void on_AXIS2_pressed();
          void on_AXIS2_released();

          void on_AXIS3_pressed();
          void on_AXIS3_released();

          void on_AXIS4_pressed();
          void on_AXIS4_released();

          void on_AXIS5_pressed();
          void on_AXIS5_released();

          void on_AXIS6_pressed();
          void on_AXIS6_released();

          void on_AXIS7_pressed();
          void on_AXIS7_released();

          void on_ENDEFFECTOR_pressed();
          void on_ENDEFFECTOR_released();

          void on_AXISALL_pressed();
          void on_AXISALL_released();



      /***************************************************
      ** The Command States in Page 5 - Vehicle Control **
      ****************************************************/
          void on_Vehicle_Swing_clicked();
          void on_Vehicle_Base_clicked();

          void on_HOME_pressed();

          void on_HOME_released();

          void on_HOMESTOP_pressed();

          void on_HOMESTOP_released();

          void on_RS_pressed();

          void on_RS_released();

          void on_MOVE_clicked();

          void on_Swing_BothForward_pressed();
          void on_Swing_BothForward_released();

          void on_Swing_BothBackward_pressed();
          void on_Swing_BothBackward_released();

          void on_Swing_LeftForward_pressed();
          void on_Swing_LeftForward_released();

          void on_Swing_LeftBackward_pressed();
          void on_Swing_LeftBackward_released();

          void on_Swing_RightForward_pressed();
          void on_Swing_RightForward_released();

          void on_Swing_RightBackward_pressed();
          void on_Swing_RightBackward_released();

          void on_FAST_clicked();

          void on_MIDDLE_clicked();

          void on_SLOW_clicked();
          void on_Base_Forward_pressed();
          void on_Base_Forward_released();

          void on_Base_Backward_pressed();
          void on_Base_Backward_released();

          void on_Base_Left_pressed();
          void on_Base_Left_released();

          void on_Base_Right_pressed();
          void on_Base_Right_released();

          void on_Base_LeftForward_pressed();
          void on_Base_LeftForward_released();

          void on_Base_RightForward_pressed();
          void on_Base_RightForward_released();

          void on_Base_LeftBackward_pressed();
          void on_Base_LeftBackward_released();

          void on_Base_RightBackward_pressed();
          void on_Base_RightBackward_released();

      /**************************************************
      ** The Command States in Page 6 - Manual Control **
      ***************************************************/
          void on_Arm_Stop_Manual_pressed();
          void on_Arm_Stop_Manual_released();

          void on_Arm_Move_Manual_pressed();
          void on_Arm_Move_Manual_released();

          void on_Vehicle_Base_Manual_clicked();
          void on_Vehicle_Swing_Manual_clicked();

          void on_Arm_Cspace_Manual_clicked();
          void on_Arm_Wspace_Manual_clicked();
          void on_Arm_Gripper_Manual_clicked();

private:
  Ui::MainWindow ui;
	QNode qnode;
  QTimer *updateTimer;
};

}  // namespace com_win

#endif // com_win_MAIN_WINDOW_H
