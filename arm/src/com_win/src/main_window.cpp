/**
 * @file /src/main_window.cpp
 *
 * @brief Implementation for the qt gui.
 *
 * @date February 2011
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui>
#include <QMessageBox>
#include <iostream>
#include "../include/com_win/main_window.hpp"
#include <vector>
/*****************************************************************************
** Namespaces
*****************************************************************************/

std::string CommandMode;
std::string Coordinator="END_EFFECTOR";
std::string ZeroAxis;
std::string Aux_swing;
std::string Aux_Home;
int CommandEmit;
int ManualSwitch;
int Base_Speed;
std::vector<double> CtrlValues(6,0.0);
extern std::vector<double> position;
extern int check_node;
extern float Pressure;
extern std::string mobot_mode;
extern std::string vehicle_mode;
extern std::string Command_string;

namespace com_win {

using namespace Qt;

/*****************************************************************************
** Implementation [MainWindow]
*****************************************************************************/

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
	: QMainWindow(parent)
	, qnode(argc,argv)
{
      ui.setupUi(this);
      // init the start configuration
      ui.stackedWidget->setCurrentIndex(0);
      ui.Arm_Vehicle->setChecked(false);
      ui.Arm_Zero->setChecked(true);
      ui.Coordinator->setChecked(true);
      ui.HOMEASTOP->setChecked(true);
      ui.Vehicle->setChecked(true);
      ui.Manual->setChecked(true);
      connect(ui.Axis1_Zero,SIGNAL(clicked()),this,SLOT(real_time()));
      qnode.init();
      updateTimer = new QTimer(this);
      updateTimer->start(70);
      //updateTimer->setInterval(20);
      connect(updateTimer, SIGNAL(timeout()), this, SLOT(slotUpdateTimer()));
}

MainWindow::~MainWindow()
{

}

/*****************************************************************************
** Implementation [Slots]
*****************************************************************************/
/*
 * These triggers whenever the button is clicked, regardless of whether it
 * is already checked or not.
 */
void MainWindow::on_Arm_Vehicle_clicked()
{
    ui.stackedWidget->setCurrentIndex(0);
    ui.Arm_Vehicle->setChecked(false);
    ui.Arm_Zero->setChecked(true);
    ui.Coordinator->setChecked(true);
    ui.HOMEASTOP->setChecked(true);
    ui.Vehicle->setChecked(true);
    ui.Manual->setChecked(true);

    CommandMode = "OTHERS";
    ManualSwitch = 0;
    ui.Arm_Joint->setChecked(false);
    ui.Arm_Cartesian->setChecked(false);
    ui.Gripper->setChecked(false);
    std::cout << "Switch to Page 1." << std::endl;

    ui.Arm_Zero->setIcon(QIcon("/home/biao/swj_ws/src/com_win/images/icon1.jpg"));
    ui.Coordinator->setIcon(QIcon("/home/biao/swj_ws/src/com_win/images/icon2.jpg"));
    ui.Vehicle->setIcon(QIcon("/home/biao/swj_ws/src/com_win/images/icon3.png"));

    QProcess *proc = new QProcess();
    //QStringList arguments;
    //arguments<< "cd" << " " << "~";
    //QString program = "./joystick";
    //QString command;
    //command = "cd ~";

    //proc->start("./joystick"/*,arguments*/);
    proc->start("./pubvel");
    //proc->start("gnome-terminal bash");
    //proc->execute(command);
    //proc->execute("rosrun turtlesim turtlesim_node");
}

void MainWindow::on_Arm_Zero_clicked()
{
    ui.stackedWidget->setCurrentIndex(1);
    ui.Arm_Vehicle->setChecked(true);
    ui.Arm_Zero->setChecked(false);
    ui.Coordinator->setChecked(true);
    ui.HOMEASTOP->setChecked(true);
    ui.Vehicle->setChecked(true);
    ui.Manual->setChecked(true);
    CommandMode = "ZERO";
    ManualSwitch = 0;
    std::cout << "Switch to Page 2." << std::endl;
}

void MainWindow::on_Coordinator_clicked()
{
    ui.stackedWidget->setCurrentIndex(2);
    ui.Arm_Vehicle->setChecked(true);
    ui.Arm_Zero->setChecked(true);
    ui.Coordinator->setChecked(false);
    ui.HOMEASTOP->setChecked(true);
    ui.Vehicle->setChecked(true);
    ui.Manual->setChecked(true);
    CommandMode = "OTHERS";
    ManualSwitch = 0;
    std::cout << "Switch to Page 3." << std::endl;
}

void MainWindow::on_HOMEASTOP_clicked()
{
    ui.stackedWidget->setCurrentIndex(3);
    ui.Arm_Vehicle->setChecked(true);
    ui.Arm_Zero->setChecked(true);
    ui.Coordinator->setChecked(true);
    ui.HOMEASTOP->setChecked(false);
    ui.Vehicle->setChecked(true);
    ui.Manual->setChecked(true);
    CommandMode = "OTHERS";
    ManualSwitch = 0;
    ui.HOME_3->setChecked(false);
    ui.HOMESTOP_3->setChecked(false);
    std::cout << "Switch to Page 4." << std::endl;
}

void MainWindow::on_Vehicle_clicked()
{
    ui.stackedWidget->setCurrentIndex(4);
    ui.Arm_Vehicle->setChecked(true);
    ui.Arm_Zero->setChecked(true);
    ui.Coordinator->setChecked(true);
    ui.HOMEASTOP->setChecked(true);
    ui.Vehicle->setChecked(false);
    ui.Manual->setChecked(true);

    CommandMode = "OTHERS";
    ManualSwitch = 0;
    ui.Vehicle_Swing->setChecked(false);
    ui.Vehicle_Base->setChecked(false);
    ui.MOVE->setChecked(false);
    ui.FAST->setChecked(false);
    ui.MIDDLE->setChecked(false);
    ui.SLOW->setChecked(false);
    std::cout << "Switch to Page 5." << std::endl;
}

void MainWindow::on_Manual_clicked()
{
    ui.stackedWidget->setCurrentIndex(5);
    ui.Arm_Vehicle->setChecked(true);
    ui.Arm_Zero->setChecked(true);
    ui.Coordinator->setChecked(true);
    ui.Vehicle->setChecked(true);
    ui.Manual->setChecked(false);

    CommandMode = "OTHERS";
    ManualSwitch = 1;
    ui.Arm_Stop_Manual->setChecked(false);
    ui.Arm_Move_Manual->setChecked(false);
    ui.Vehicle_Base_Manual->setChecked(false);
    ui.Vehicle_Swing_Manual->setChecked(false);
    ui.Arm_Cspace_Manual->setChecked(false);
    ui.Arm_Wspace_Manual->setChecked(false);
    ui.Arm_Gripper_Manual->setChecked(false);
    std::cout << "Switch to Page 6." << std::endl;
}


/****************************
** Check and Update States **
*****************************/
void MainWindow::on_GetADValue_clicked()
{
    //adcard_collect();
}


void MainWindow::on_Serv_Connect_clicked()
{
   /* bool isRunning = server_thread->isRunning();
    while(!isRunning)
    {
        std::cout<<"[Connect Fail] Retry after 0.5 seconds."<<std::endl;
        //PRThread->threadStart();
        server_thread->mServerFlag = true;
        server_thread->start();
        QThread::msleep(500);
        isRunning = server_thread->isRunning();
    }*/
}

void MainWindow::on_Serv_Disconnect_clicked()
{

    /*server_thread->mServerFlag = false;
    //PRThread->threadQuit();
    server_thread->quit();
    std::cout<<"Quit the thread."<<std::endl;*/
}

void MainWindow::on_CheckStatus_clicked()
{
    /*bool isRunning = server_thread->isRunning();
    if (isRunning)
        std::cout<<"[Check Result] The thread is running."<<std::endl;
    else
        std::cout<<"[Check Result] The thread has been finished."<<std::endl;*/
}

/*
void MainWindow::on_UpdateState_clicked()
{
    countTEST += 1.0;
    ui.Mode_State->setText( CommandMode.c_str() );
    ui.Coord_State->setText( Coordinator.c_str() );
    ui.Value1_State->setText(QString::number(countTEST, 10, 2));
    ui.Value2_State->setText(QString::number(countTEST, 10, 2));
    ui.Value3_State->setText(QString::number(countTEST, 10, 2));
    ui.Value4_State->setText(QString::number(countTEST, 10, 2));
    ui.Value5_State->setText(QString::number(countTEST, 10, 2));
    ui.Value6_State->setText(QString::number(countTEST, 10, 2));
    ui.Value7_State->setText(QString::number(countTEST, 10, 2));
}
*/
void MainWindow::on_UpdateState_clicked()
{

}

void MainWindow::on_No_Limit_clicked()
{
  bool selected = ui.No_Limit->isChecked();
  if (selected)
  {
      CommandMode = "NO_LIMIT";
      CommandEmit = 1;
      ui.No_Limit->setChecked(true);
      // clear states of other buttons
  }
  else
  {
      CommandMode = "OTHERS";
      CommandEmit = 0;
      ui.No_Limit->setChecked(false);
  }
}

//add
void MainWindow::real_time()
{

}

void MainWindow::slotUpdateTimer()
{
    ui.Mobot_Mode_State->setText( mobot_mode.c_str() );
    ui.Vehicle_Mode_State->setText( vehicle_mode.c_str() );
    ui.check_node_State->setText( QString::number(check_node) );
    ui.pressure_State->setText( QString::number(Pressure, 10, 4));
    ui.Command_State->setText( Command_string.c_str() );
    ui.Value1_State_2->setText(QString::number(position[0], 10, 4));
    ui.Value2_State->setText(QString::number(position[1], 10, 4));
    ui.Value3_State->setText(QString::number(position[2], 10, 4));
    ui.Value4_State->setText(QString::number(position[3], 10, 4));
    ui.Value5_State->setText(QString::number(position[4], 10, 4));
    ui.Value6_State->setText(QString::number(position[5], 10, 4));
    ui.Value7_State->setText(QString::number(position[6], 10, 4));
    ui.Value8_State->setText(QString::number(position[7], 10, 4));
    ui.Value9_State->setText(QString::number(position[8], 10, 4));
    ui.Value10_State->setText(QString::number(position[9], 10, 4));
    ui.Value11_State->setText(QString::number(position[10], 10, 4));
    ui.Value12_State->setText(QString::number(position[11], 10, 4));
    update();
}

/*******************************************************
** The Command States in Page 1 - Manipulator Control **
********************************************************/
void MainWindow::on_Arm_Stop_pressed()
{
    CommandMode = "STOP";
    CommandEmit = 1;
    ui.Arm_Stop->setChecked(true);
    // clear states of other buttons
    ui.Arm_Joint->setChecked(false);
    ui.Arm_Cartesian->setChecked(false);
    ui.Gripper->setChecked(false);
}

void MainWindow::on_Arm_Stop_released()
{
    CommandMode = "OTHERS";
    CommandEmit = 0;
    ui.Arm_Stop->setChecked(false);
}

void MainWindow::on_Arm_Move_pressed()
{
    CommandMode = "MOVE";
    CommandEmit = 1;
    ui.Arm_Move->setChecked(true);
    // clear states of other buttons
    ui.Arm_Joint->setChecked(false);
    ui.Arm_Cartesian->setChecked(false);
    ui.Gripper->setChecked(false);
}

void MainWindow::on_Arm_Move_released()
{
    CommandMode = "OTHERS";
    CommandEmit = 0;
    ui.Arm_Move->setChecked(false);
}

void MainWindow::on_Arm_Joint_clicked()
{
    bool selected = ui.Arm_Joint->isChecked();
    //std::cout<<"[ARMJ State] "<<(int)selected<<std::endl;
    if (selected)
    {
        CommandMode = "ARMJ";
        ui.Arm_Joint->setChecked(true);
        // clear states of other buttons
        ui.Arm_Cartesian->setChecked(false);
        ui.Gripper->setChecked(false);
    }
    else
    {
        CommandMode = "OTHERS";
        ui.Arm_Joint->setChecked(false);
    }
}

void MainWindow::on_Arm_Cartesian_clicked()
{
    bool selected = ui.Arm_Cartesian->isChecked();
    //std::cout<<"[ARMC State] "<<(int)selected<<std::endl;
    if (selected)
    {
        CommandMode = "ARMC";
        ui.Arm_Cartesian->setChecked(true);
        // clear states of other buttons
        ui.Arm_Joint->setChecked(false);
        ui.Gripper->setChecked(false);
    }
    else
    {
        CommandMode = "OTHERS";
        ui.Arm_Cartesian->setChecked(false);
    }
}

void MainWindow::on_Gripper_clicked()
{
    bool selected = ui.Gripper->isChecked();
    std::cout<<"[Gripper State] "<<(int)selected<<std::endl;
    if (selected)
    {
        CommandMode = "GRIP";
        ui.Gripper->setChecked(true);
        // clear states of other buttons
        ui.Arm_Joint->setChecked(false);
        ui.Arm_Cartesian->setChecked(false);
    }
    else
    {
        CommandMode = "OTHERS";
        ui.Gripper->setChecked(false);
    }
}

void MainWindow::on_Gripper_Open_pressed()
{
    if (CommandMode == "GRIP")
    {
        CommandEmit = 1;
        CtrlValues[0] = 1.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Gripper_Open->setChecked(true);
    }
}

void MainWindow::on_Gripper_Open_released()
{
    if (CommandMode == "GRIP")
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Gripper_Open->setChecked(false);
    }
}

void MainWindow::on_Gripper_Close_pressed()
{
    if (CommandMode == "GRIP")
    {
        CommandEmit = 1;
        CtrlValues[0] = -1.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Gripper_Open->setChecked(true);
    }
}

void MainWindow::on_Gripper_Close_released()
{
    if (CommandMode == "GRIP")
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Gripper_Open->setChecked(false);
    }
}

void MainWindow::on_Axis1_F_pressed()
{
    if ( (CommandMode == "ARMJ")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.15;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis1_F->setChecked(true);
    }
    else if ( (CommandMode == "ARMC")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.5;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis1_F->setChecked(true);
    }
}


void MainWindow::on_Axis1_F_released()
{
    if ( (CommandMode == "ARMJ") || (CommandMode == "ARMC") )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Axis1_F->setChecked(false);
    }
}

void MainWindow::on_Axis1_R_pressed()
{
    if ( (CommandMode == "ARMJ") )
    {
        CommandEmit = 1;
        CtrlValues[0] = -0.15;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis1_R->setChecked(true);
    }
    else if ( (CommandMode == "ARMC")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = -0.5;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis1_R->setChecked(true);
    }
}

void MainWindow::on_Axis1_R_released()
{
    if ( (CommandMode == "ARMJ") || (CommandMode == "ARMC") )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Axis1_R->setChecked(false);
    }
}

void MainWindow::on_Axis2_F_pressed()
{
    if ( (CommandMode == "ARMJ")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.15;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis2_F->setChecked(true);
    }
    else if ( (CommandMode == "ARMC")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.5;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis2_F->setChecked(true);
    }
}

void MainWindow::on_Axis2_F_released()
{
    if ( (CommandMode == "ARMJ") || (CommandMode == "ARMC") )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Axis2_F->setChecked(false);
    }
}

void MainWindow::on_Axis2_R_pressed()
{
    if ( (CommandMode == "ARMJ")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = -0.15;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis2_R->setChecked(true);
    }
    else if ( (CommandMode == "ARMC")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = -0.5;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis2_R->setChecked(true);
    }
}

void MainWindow::on_Axis2_R_released()
{
    if ( (CommandMode == "ARMJ") || (CommandMode == "ARMC") )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Axis2_R->setChecked(false);
    }
}

void MainWindow::on_Axis3_F_pressed()
{
    if ( (CommandMode == "ARMJ") )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.15;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis3_F->setChecked(true);
    }
    else if ( (CommandMode == "ARMC")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.5;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis3_F->setChecked(true);
    }
}

void MainWindow::on_Axis3_F_released()
{
    if ( (CommandMode == "ARMJ") || (CommandMode == "ARMC") )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Axis3_F->setChecked(false);
    }
}

void MainWindow::on_Axis3_R_pressed()
{
    if ( (CommandMode == "ARMJ")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = -0.15;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis3_R->setChecked(true);
    }
    else if ( (CommandMode == "ARMC")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = -0.5;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis3_R->setChecked(true);
    }
}

void MainWindow::on_Axis3_R_released()
{
    if ( (CommandMode == "ARMJ") || (CommandMode == "ARMC") )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Axis3_R->setChecked(false);
    }
}

void MainWindow::on_Axis4_F_pressed()
{
    if ( (CommandMode == "ARMJ")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.15;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis4_F->setChecked(true);
    }
    else if ( (CommandMode == "ARMC")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.15;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis4_F->setChecked(true);
    }
}

void MainWindow::on_Axis4_F_released()
{
    if ( (CommandMode == "ARMJ") || (CommandMode == "ARMC") )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Axis4_F->setChecked(false);
    }
}

void MainWindow::on_Axis4_R_pressed()
{
    if ( (CommandMode == "ARMJ")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = -0.15;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis4_R->setChecked(true);
    }
   else if ( (CommandMode == "ARMC")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = -0.15;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis4_R->setChecked(true);
    }
}

void MainWindow::on_Axis4_R_released()
{
    if ( (CommandMode == "ARMJ") || (CommandMode == "ARMC") )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Axis4_R->setChecked(false);
    }
}

void MainWindow::on_Axis5_F_pressed()
{
    if ( (CommandMode == "ARMJ") )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.15;
        CtrlValues[5] = 0.0;
        ui.Axis5_F->setChecked(true);
    }
   else if ( (CommandMode == "ARMC")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.15;
        CtrlValues[5] = 0.0;
        ui.Axis5_F->setChecked(true);
    }
}

void MainWindow::on_Axis5_F_released()
{
    if ( (CommandMode == "ARMJ") || (CommandMode == "ARMC") )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Axis5_F->setChecked(false);
    }
}

void MainWindow::on_Axis5_R_pressed()
{
    if ( (CommandMode == "ARMJ")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = -0.15;
        CtrlValues[5] = 0.0;
        ui.Axis5_R->setChecked(true);
    }
   else if ( (CommandMode == "ARMC")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = -0.15;
        CtrlValues[5] = 0.0;
        ui.Axis5_R->setChecked(true);
    }
}

void MainWindow::on_Axis5_R_released()
{
    if ( (CommandMode == "ARMJ") || (CommandMode == "ARMC") )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Axis5_R->setChecked(false);
    }
}

void MainWindow::on_Axis6_F_pressed()
{
    if ( (CommandMode == "ARMJ") )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.15;
        ui.Axis6_F->setChecked(true);
    }
   else if ( (CommandMode == "ARMC")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.15;
       ui.Axis6_F->setChecked(true);
    }
}

void MainWindow::on_Axis6_F_released()
{
    if ( (CommandMode == "ARMJ") || (CommandMode == "ARMC") )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Axis6_F->setChecked(false);
    }
}

void MainWindow::on_Axis6_R_pressed()
{
    if ( (CommandMode == "ARMJ") )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = -0.15;
        ui.Axis6_R->setChecked(true);
    }
    else if ( (CommandMode == "ARMC")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = -0.15;
        ui.Axis6_R->setChecked(true);
    }
}

void MainWindow::on_Axis6_R_released()
{
    if ( (CommandMode == "ARMJ") || (CommandMode == "ARMC") )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Axis6_R->setChecked(false);
    }
}

void MainWindow::on_Axis7_F_pressed()
{
    if ( (CommandMode == "ARMJ") )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis7_F->setChecked(true);
    }
    else if ( (CommandMode == "ARMC")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis7_F->setChecked(true);
    }
}

void MainWindow::on_Axis7_F_released()
{
    if ( (CommandMode == "ARMJ") || (CommandMode == "ARMC") )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Axis7_F->setChecked(false);
    }
}

void MainWindow::on_Axis7_R_pressed()
{
    if ( (CommandMode == "ARMJ") )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis7_R->setChecked(true);
    }
    else if ( (CommandMode == "ARMC")  )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Axis7_R->setChecked(true);
    }
}

void MainWindow::on_Axis7_R_released()
{
    if ( (CommandMode == "ARMJ") || (CommandMode == "ARMC") )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Axis7_R->setChecked(false);
    }
}


/****************************************************
** The Command States in Page 2 - Manipulator Zero **
*****************************************************/
void MainWindow::on_Axis1_Zero_pressed()
{
    CommandEmit = 1;
    ZeroAxis = "AXIS1";
    ui.Axis1_Zero->setChecked(true);
}

void MainWindow::on_Axis1_Zero_released()
{
    CommandEmit = 0;
    ZeroAxis = "";
    ui.Axis1_Zero->setChecked(false);
}

void MainWindow::on_Axis2_Zero_pressed()
{
    CommandEmit = 1;
    ZeroAxis = "AXIS2";
    ui.Axis2_Zero->setChecked(true);
}

void MainWindow::on_Axis2_Zero_released()
{
    CommandEmit = 0;
    ZeroAxis = "";
    ui.Axis2_Zero->setChecked(false);
}

void MainWindow::on_Axis3_Zero_pressed()
{
    CommandEmit = 1;
    ZeroAxis = "AXIS3";
    ui.Axis3_Zero->setChecked(true);
}

void MainWindow::on_Axis3_Zero_released()
{
    CommandEmit = 0;
    ZeroAxis = "";
    ui.Axis3_Zero->setChecked(false);
}

void MainWindow::on_Axis4_Zero_pressed()
{
    CommandEmit = 1;
    ZeroAxis = "AXIS4";
    ui.Axis4_Zero->setChecked(true);
}

void MainWindow::on_Axis4_Zero_released()
{
    CommandEmit = 0;
    ZeroAxis = "";
    ui.Axis4_Zero->setChecked(false);
}

void MainWindow::on_Axis5_Zero_pressed()
{
    CommandEmit = 1;
    ZeroAxis = "AXIS5";
    ui.Axis5_Zero->setChecked(true);
}

void MainWindow::on_Axis5_Zero_released()
{
    CommandEmit = 0;
    ZeroAxis = "";
    ui.Axis5_Zero->setChecked(false);
}

void MainWindow::on_Axis6_Zero_pressed()
{
    CommandEmit = 1;
    ZeroAxis = "AXIS6";
    ui.Axis6_Zero->setChecked(true);
}

void MainWindow::on_Axis6_Zero_released()
{
    CommandEmit = 0;
    ZeroAxis = "";
    ui.Axis6_Zero->setChecked(false);
}

void MainWindow::on_Axis7_Zero_pressed()
{
    CommandEmit = 1;
    ZeroAxis = "AXIS7";
    ui.Axis7_Zero->setChecked(true);
}

void MainWindow::on_Axis7_Zero_released()
{
    CommandEmit = 0;
    ZeroAxis = "";
    ui.Axis7_Zero->setChecked(false);
}

void MainWindow::on_Gripper_Zero_pressed()
{
    CommandEmit = 1;
    ZeroAxis = "GRIPPER";
    ui.Gripper_Zero->setChecked(true);
}

void MainWindow::on_Gripper_Zero_released()
{
    CommandEmit = 0;
    ZeroAxis = "";
    ui.Gripper_Zero->setChecked(false);
}

void MainWindow::on_AxisAll_Zero_pressed()
{
    CommandEmit = 1;
    ZeroAxis = "AXISALL";
    ui.AxisAll_Zero->setChecked(true);
}

void MainWindow::on_AxisAll_Zero_released()
{
    CommandEmit = 0;
    ZeroAxis = "";
    ui.AxisAll_Zero->setChecked(false);
}

void MainWindow::on_Stop_Zero_pressed()
{
    CommandEmit = 1;
    ZeroAxis = "AXISSTOP";
    ui.Stop_Zero->setChecked(true);
}

void MainWindow::on_Stop_Zero_released()
{
    CommandEmit = 0;
    ZeroAxis = "";
    ui.Stop_Zero->setChecked(false);
}


/***********************************************
** The Command States in Page 3 - Coordinator **
************************************************/
void MainWindow::on_Base_Link_clicked()
{
    Coordinator = "BASE_LINK";
}

void MainWindow::on_Link_1_clicked()
{
    Coordinator = "END_EFFECTOR";
    //Coordinator = "LINK_1";
}

void MainWindow::on_Link_2_clicked()
{
    Coordinator = "END_EFFECTOR";
    //Coordinator = "LINK_2";
}

void MainWindow::on_Link_3_clicked()
{
    Coordinator = "END_EFFECTOR";
    //Coordinator = "LINK_3";
}

void MainWindow::on_Link_4_clicked()
{
    Coordinator = "END_EFFECTOR";
    //Coordinator = "LINK_4";
}

void MainWindow::on_Link_5_clicked()
{
    Coordinator = "END_EFFECTOR";
    //Coordinator = "LINK_5";
}

void MainWindow::on_Link_6_clicked()
{
    Coordinator = "END_EFFECTOR";
    //Coordinator = "LINK_6";
}

void MainWindow::on_Link_7_clicked()
{
    Coordinator = "END_EFFECTOR";
    //Coordinator = "LINK_7";
}

void MainWindow::on_End_Effector_clicked()
{
    Coordinator = "END_EFFECTOR";
}

/***************************************************
** The Command States in Page 4 - HOME Control **
****************************************************/
void MainWindow::on_HOME_3_clicked()
{
    bool selected = ui.HOME_3->isChecked();
    if(selected)
    {
    CommandMode="HOME";
    ui.HOME_3->setChecked(true);
    ui.HOMESTOP_3->setChecked(false);
    }
    else
    {
    CommandMode="OTHERS";
    ui.HOME_3->setChecked(false);
    }

}

void MainWindow::on_HOMESTOP_3_pressed()
{
    CommandMode="HOMESTOP";
    CommandEmit = 1;
    ui.HOME_3->setChecked(false);
    ui.HOMESTOP_3->setChecked(true);
}


void MainWindow::on_HOMESTOP_3_released()
{
    CommandMode="OTHERS";
    CommandEmit = 0;
    ui.HOMESTOP_3->setChecked(false);
}


void MainWindow::on_AXIS1_pressed()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXIS1";
    CommandEmit = 1;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 1.0;
    //ui.AXIS1->setChecked(true);
    }
}

void MainWindow::on_AXIS1_released()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXIS1";
    CommandEmit = 0;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 0.0;
    ui.AXIS1->setChecked(false);
    }
}

void MainWindow::on_AXIS2_pressed()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXIS2";
    CommandEmit = 1;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 2.0;
    //ui.AXIS2->setChecked(true);
    }
}

void MainWindow::on_AXIS2_released()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXIS2";
    CommandEmit = 0;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 0.0;
    ui.AXIS2->setChecked(false);
    }
}

void MainWindow::on_AXIS3_pressed()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXIS3";
    CommandEmit = 1;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 3.0;
    //ui.AXIS3->setChecked(true);
    }
}

void MainWindow::on_AXIS3_released()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXIS3";
    CommandEmit = 0;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 0.0;
    ui.AXIS3->setChecked(false);
    }
}

void MainWindow::on_AXIS4_pressed()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXIS4";
    CommandEmit = 1;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 4.0;
    //ui.AXIS4->setChecked(true);
    }
}

void MainWindow::on_AXIS4_released()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXIS4";
    CommandEmit = 0;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 0.0;
    ui.AXIS4->setChecked(false);
    }
}

void MainWindow::on_AXIS5_pressed()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXIS5";
    CommandEmit = 1;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 5.0;
    //ui.AXIS5->setChecked(true);
    }
}

void MainWindow::on_AXIS5_released()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXIS5";
    CommandEmit = 0;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 0.0;
    ui.AXIS5->setChecked(false);
    }
}

void MainWindow::on_AXIS6_pressed()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXIS6";
    CommandEmit = 1;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 6.0;
    //ui.AXIS6->setChecked(true);
    }
}

void MainWindow::on_AXIS6_released()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXIS6";
    CommandEmit = 0;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 0.0;
    ui.AXIS6->setChecked(false);
    }
}

void MainWindow::on_AXIS7_pressed()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXIS7";
    CommandEmit = 1;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 7.0;
    //ui.AXIS7->setChecked(true);
    }
}

void MainWindow::on_AXIS7_released()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXIS7";
    CommandEmit = 0;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 0.0;
    ui.AXIS7->setChecked(false);
    }
}

void MainWindow::on_ENDEFFECTOR_pressed()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="ENDEFFECTOR";
    CommandEmit = 1;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 8.0;
    //ui.ENDEFFECTOR->setChecked(true);
    }
}

void MainWindow::on_ENDEFFECTOR_released()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="ENDEFFECTOR";
    CommandEmit = 0;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 0.0;
    ui.ENDEFFECTOR->setChecked(false);
    }
}

void MainWindow::on_AXISALL_pressed()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXISALL";
    CommandEmit = 1;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 9.0;
    //ui.AXISALL->setChecked(true);
    }
}

void MainWindow::on_AXISALL_released()
{
    if(CommandMode=="HOME")
    {
    Aux_Home="AXISALL";
    CommandEmit = 0;
    for (int i = 0; i < 6; ++i)
        CtrlValues[i] = 0.0;
    ui.AXISALL->setChecked(false);
    }
}
/***************************************************
** The Command States in Page 5 - Vehicle Control **
****************************************************/
void MainWindow::on_Vehicle_Swing_clicked()
{
    bool selected = ui.Vehicle_Swing->isChecked();
    if (selected)
    {
        CommandMode = "SWING";
        ui.Vehicle_Swing->setChecked(true);
        // clear states of other buttons
        ui.Vehicle_Base->setChecked(false);
        ui.MOVE->setChecked(false);
        ui.HOME->setChecked(false);
        ui.HOMESTOP->setChecked(false);
        ui.RS->setChecked(false);
    }
    else
    {
        CommandMode = "OTHERS";
        ui.Vehicle_Swing->setChecked(false);
    }
}

void MainWindow::on_Vehicle_Base_clicked()
{
    bool selected = ui.Vehicle_Base->isChecked();
    if (selected)
    {
        CommandMode = "BASE";
        ui.Vehicle_Base->setChecked(true);
        // clear states of other buttons
        ui.Vehicle_Swing->setChecked(false);
        ui.FAST->setChecked(false);
        ui.MIDDLE->setChecked(false);
        ui.SLOW->setChecked(false);

    }
    else
    {
        CommandMode = "OTHERS";
        ui.Vehicle_Base->setChecked(false);
    }
}

void MainWindow::on_HOME_pressed()
{
    if(CommandMode=="SWING")
    {
    Aux_swing="HOME";
    CommandEmit = 1;
    CtrlValues[0] = 6.0;
    CtrlValues[1] = 6.0;
    CtrlValues[2] = 0.0;
    CtrlValues[3] = 0.0;
    CtrlValues[4] = 0.0;
    CtrlValues[5] = 0.0;
    ui.HOME->setChecked(true);
    ui.MOVE->setChecked(false);
    }
}

void MainWindow::on_HOME_released()
{
    if(CommandMode=="SWING")
    {
    CommandEmit = 0;
    CtrlValues[0] = 0.0;
    CtrlValues[1] = 0.0;
    CtrlValues[2] = 0.0;
    CtrlValues[3] = 0.0;
    CtrlValues[4] = 0.0;
    CtrlValues[5] = 0.0;
    ui.HOME->setChecked(false);
    }
}

void MainWindow::on_HOMESTOP_pressed()
{
    if(CommandMode=="SWING")
    {
    Aux_swing="HOMESTOP";
    CommandEmit = 1;
    CtrlValues[0] = 7.0;
    CtrlValues[1] = 7.0;
    CtrlValues[2] = 0.0;
    CtrlValues[3] = 0.0;
    CtrlValues[4] = 0.0;
    CtrlValues[5] = 0.0;
    ui.HOMESTOP->setChecked(true);
    ui.MOVE->setChecked(false);
    }
}


void MainWindow::on_HOMESTOP_released()
{
    if(CommandMode=="SWING")
    {
    CommandEmit = 0;
    CtrlValues[0] = 0.0;
    CtrlValues[1] = 0.0;
    CtrlValues[2] = 0.0;
    CtrlValues[3] = 0.0;
    CtrlValues[4] = 0.0;
    CtrlValues[5] = 0.0;
    ui.HOMESTOP->setChecked(false);
    }
}

void MainWindow::on_RS_pressed()
{
    if(CommandMode=="SWING")
    {
    Aux_swing="RESET";
    CommandEmit = 1;
    CtrlValues[0] = 8.0;
    CtrlValues[1] = 8.0;
    CtrlValues[2] = 0.0;
    CtrlValues[3] = 0.0;
    CtrlValues[4] = 0.0;
    CtrlValues[5] = 0.0;
    ui.RS->setChecked(true);
    ui.MOVE->setChecked(false);
    }
}


void MainWindow::on_RS_released()
{
    if(CommandMode=="SWING")
    {
    CommandEmit = 0;
    CtrlValues[0] = 0.0;
    CtrlValues[1] = 0.0;
    CtrlValues[2] = 0.0;
    CtrlValues[3] = 0.0;
    CtrlValues[4] = 0.0;
    CtrlValues[5] = 0.0;
    ui.RS->setChecked(false);
    }
}

void MainWindow::on_MOVE_clicked()
{
    bool selected = ui.MOVE->isChecked();
    if (selected)
    {
    if(CommandMode=="SWING")
    {
    Aux_swing="MOVE";
    ui.MOVE->setChecked(true);
    ui.HOME->setChecked(false);
    ui.HOMESTOP->setChecked(false);
    ui.RS->setChecked(false);
    }
    }
    else
    ui.MOVE->setChecked(false);
}

void MainWindow::on_Swing_BothForward_pressed()
{
    if ( Aux_swing == "MOVE" )
    {
        CommandEmit = 1;
        CtrlValues[0] = 2.0;
        CtrlValues[1] = 2.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Swing_BothForward->setChecked(true);
    }
}

void MainWindow::on_Swing_BothForward_released()
{
    if ( Aux_swing == "MOVE" )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Swing_BothForward->setChecked(false);
    }
}

void MainWindow::on_Swing_BothBackward_pressed()
{
    if ( Aux_swing == "MOVE" )
    {
        CommandEmit = 1;
        CtrlValues[0] = -2.0;
        CtrlValues[1] = -2.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Swing_BothBackward->setChecked(true);
    }
}

void MainWindow::on_Swing_BothBackward_released()
{
    if ( Aux_swing == "MOVE" )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Swing_BothBackward->setChecked(false);
    }
}

void MainWindow::on_Swing_LeftForward_pressed()
{
    if ( Aux_swing == "MOVE" )
    {
        CommandEmit = 1;
        CtrlValues[0] = 2.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Swing_LeftForward->setChecked(true);
    }
}

void MainWindow::on_Swing_LeftForward_released()
{
    if ( Aux_swing == "MOVE" )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Swing_LeftForward->setChecked(false);
    }
}

void MainWindow::on_Swing_LeftBackward_pressed()
{
    if ( Aux_swing == "MOVE" )
    {
        CommandEmit = 1;
        CtrlValues[0] = -2.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Swing_LeftBackward->setChecked(true);
    }
}

void MainWindow::on_Swing_LeftBackward_released()
{
    if ( Aux_swing == "MOVE" )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Swing_LeftBackward->setChecked(false);
    }
}

void MainWindow::on_Swing_RightForward_pressed()
{
    if ( Aux_swing == "MOVE" )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 2.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Swing_RightForward->setChecked(true);
    }
}

void MainWindow::on_Swing_RightForward_released()
{
    if ( Aux_swing == "MOVE" )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Swing_RightForward->setChecked(false);
    }
}

void MainWindow::on_Swing_RightBackward_pressed()
{
    if ( Aux_swing == "MOVE" )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = -2.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Swing_RightBackward->setChecked(true);
    }
}

void MainWindow::on_Swing_RightBackward_released()
{
    if ( Aux_swing == "MOVE" )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Swing_RightBackward->setChecked(false);
    }
}

void MainWindow::on_FAST_clicked()
{
    bool selected = ui.FAST->isChecked();
    if (selected)
    {
        Base_Speed =3;
        ui.FAST->setChecked(true);
        // clear states of other buttons
        ui.MIDDLE->setChecked(false);
        ui.SLOW->setChecked(false);
    }
    else
    {
        CommandMode = "OTHERS";
        ui.FAST->setChecked(false);
        Base_Speed =0;
    }
}

void MainWindow::on_MIDDLE_clicked()
{
    bool selected = ui.MIDDLE->isChecked();
    if (selected)
    {
        Base_Speed =2;
        ui.MIDDLE->setChecked(true);
        // clear states of other buttons
        ui.FAST->setChecked(false);
        ui.SLOW->setChecked(false);
    }
    else
    {
        CommandMode = "OTHERS";
        ui.MIDDLE->setChecked(false);
        Base_Speed =0;
    }
}

void MainWindow::on_SLOW_clicked()
{
    bool selected = ui.SLOW->isChecked();
    if (selected)
    {
        Base_Speed =1;
        ui.SLOW->setChecked(true);
        // clear states of other buttons
        ui.FAST->setChecked(false);
        ui.MIDDLE->setChecked(false);
    }
    else
    {
        CommandMode = "OTHERS";
        ui.SLOW->setChecked(false);
        Base_Speed =0;
    }
}

void MainWindow::on_Base_Forward_pressed()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 1;
        CtrlValues[0] = 3.0*Base_Speed;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Base_Forward->setChecked(true);
    }
}

void MainWindow::on_Base_Forward_released()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Base_Forward->setChecked(false);
    }
}

void MainWindow::on_Base_Backward_pressed()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 1;
        CtrlValues[0] = -3.0*Base_Speed;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 0.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Base_Backward->setChecked(true);
    }
}

void MainWindow::on_Base_Backward_released()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Base_Backward->setChecked(false);
    }
}

void MainWindow::on_Base_Left_pressed()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 1.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Base_Left->setChecked(true);
    }
}

void MainWindow::on_Base_Left_released()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Base_Left->setChecked(false);
    }
}

void MainWindow::on_Base_Right_pressed()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 1;
        CtrlValues[0] = 0.0;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = -1.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Base_Right->setChecked(true);
    }
}

void MainWindow::on_Base_Right_released()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Base_Right->setChecked(false);
    }
}

void MainWindow::on_Base_LeftForward_pressed()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 1;
        CtrlValues[0] = 3.0*Base_Speed;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 1.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Base_LeftForward->setChecked(true);
    }
}

void MainWindow::on_Base_LeftForward_released()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Base_LeftForward->setChecked(false);
    }
}

void MainWindow::on_Base_RightForward_pressed()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 1;
        CtrlValues[0] = 3.0*Base_Speed;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = -1.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Base_RightForward->setChecked(true);
    }
}

void MainWindow::on_Base_RightForward_released()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Base_RightForward->setChecked(false);
    }
}

void MainWindow::on_Base_LeftBackward_pressed()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 1;
        CtrlValues[0] = -3.0*Base_Speed;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = -1.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Base_LeftBackward->setChecked(true);
    }
}

void MainWindow::on_Base_LeftBackward_released()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Base_LeftBackward->setChecked(false);
    }
}

void MainWindow::on_Base_RightBackward_pressed()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 1;
        CtrlValues[0] = -3.0*Base_Speed;
        CtrlValues[1] = 0.0;
        CtrlValues[2] = 0.0;
        CtrlValues[3] = 1.0;
        CtrlValues[4] = 0.0;
        CtrlValues[5] = 0.0;
        ui.Base_RightBackward->setChecked(true);
    }
}

void MainWindow::on_Base_RightBackward_released()
{
    if ( CommandMode == "BASE" )
    {
        CommandEmit = 0;
        for (int i = 0; i < 6; ++i)
            CtrlValues[i] = 0.0;
        ui.Base_RightBackward->setChecked(false);
    }
}


/**************************************************
** The Command States in Page 6 - Manual Control **
***************************************************/
void MainWindow::on_Arm_Stop_Manual_pressed()
{
    CommandMode = "STOP";
    CommandEmit = 1;
    ui.Arm_Stop_Manual->setChecked(true);
    // clear states of other buttons
    ui.Vehicle_Base_Manual->setChecked(false);
    ui.Vehicle_Swing_Manual->setChecked(false);
    ui.Arm_Cspace_Manual->setChecked(false);
    ui.Arm_Wspace_Manual->setChecked(false);
    ui.Arm_Gripper_Manual->setChecked(false);
}

void MainWindow::on_Arm_Stop_Manual_released()
{
    CommandMode = "OTHERS";
    CommandEmit = 0;
    ui.Arm_Stop_Manual->setChecked(false);
}

void MainWindow::on_Arm_Move_Manual_pressed()
{
    CommandMode = "MOVE";
    CommandEmit = 1;
    ui.Arm_Move_Manual->setChecked(true);
    // clear states of other buttons
    ui.Vehicle_Base_Manual->setChecked(false);
    ui.Vehicle_Swing_Manual->setChecked(false);
    ui.Arm_Cspace_Manual->setChecked(false);
    ui.Arm_Wspace_Manual->setChecked(false);
    ui.Arm_Gripper_Manual->setChecked(false);
}

void MainWindow::on_Arm_Move_Manual_released()
{
    CommandMode = "OTHERS";
    CommandEmit = 0;
    ui.Arm_Move_Manual->setChecked(false);
}

void MainWindow::on_Vehicle_Base_Manual_clicked()
{
    bool selected = ui.Vehicle_Base_Manual->isChecked();
    //std::cout<<"[Base State] "<<(int)selected<<std::endl;
    if (selected)
    {
        CommandMode = "BASE";
        ui.Vehicle_Base_Manual->setChecked(true);
        // clear states of other buttons
        ui.Vehicle_Swing_Manual->setChecked(false);
        ui.Arm_Cspace_Manual->setChecked(false);
        ui.Arm_Wspace_Manual->setChecked(false);
        ui.Arm_Gripper_Manual->setChecked(false);
    }
    else
    {
        CommandMode = "OTHERS";
        ui.Vehicle_Base_Manual->setChecked(false);
    }
}

void MainWindow::on_Vehicle_Swing_Manual_clicked()
{
    bool selected = ui.Vehicle_Swing_Manual->isChecked();
    //std::cout<<"[SWING State] "<<(int)selected<<std::endl;
    if (selected)
    {
        CommandMode = "SWING";
        ui.Vehicle_Swing_Manual->setChecked(true);
        // clear states of other buttons
        ui.Vehicle_Base_Manual->setChecked(false);
        ui.Arm_Cspace_Manual->setChecked(false);
        ui.Arm_Wspace_Manual->setChecked(false);
        ui.Arm_Gripper_Manual->setChecked(false);
    }
    else
    {
        CommandMode = "OTHERS";
        ui.Vehicle_Swing_Manual->setChecked(false);
    }
}

void MainWindow::on_Arm_Cspace_Manual_clicked()
{
    bool selected = ui.Arm_Cspace_Manual->isChecked();
    //std::cout<<"[ARMJ State] "<<(int)selected<<std::endl;
    if (selected)
    {
        CommandMode = "ARMJ";
        ui.Arm_Cspace_Manual->setChecked(true);
        // clear states of other buttons
        ui.Vehicle_Base_Manual->setChecked(false);
        ui.Vehicle_Swing_Manual->setChecked(false);
        ui.Arm_Wspace_Manual->setChecked(false);
        ui.Arm_Gripper_Manual->setChecked(false);
    }
    else
    {
        CommandMode = "OTHERS";
        ui.Arm_Cspace_Manual->setChecked(false);
    }
}

void MainWindow::on_Arm_Wspace_Manual_clicked()
{
    bool selected = ui.Arm_Wspace_Manual->isChecked();
    //std::cout<<"[ARMC State] "<<(int)selected<<std::endl;
    if (selected)
    {
        CommandMode = "ARMC";
        ui.Arm_Wspace_Manual->setChecked(true);
        // clear states of other buttons
        ui.Vehicle_Base_Manual->setChecked(false);
        ui.Vehicle_Swing_Manual->setChecked(false);
        ui.Arm_Cspace_Manual->setChecked(false);
        ui.Arm_Gripper_Manual->setChecked(false);
    }
    else
    {
        CommandMode = "OTHERS";
        ui.Arm_Wspace_Manual->setChecked(false);
    }
}

void MainWindow::on_Arm_Gripper_Manual_clicked()
{
    bool selected = ui.Arm_Gripper_Manual->isChecked();
    //std::cout<<"[GRIP State] "<<(int)selected<<std::endl;
    if (selected)
    {
        CommandMode = "GRIP";
        ui.Arm_Gripper_Manual->setChecked(true);
        // clear states of other buttons
        ui.Vehicle_Base_Manual->setChecked(false);
        ui.Vehicle_Swing_Manual->setChecked(false);
        ui.Arm_Cspace_Manual->setChecked(false);
        ui.Arm_Wspace_Manual->setChecked(false);
    }
    else
    {
        CommandMode = "OTHERS";
        ui.Arm_Gripper_Manual->setChecked(false);
    }
}



}  // namespace com_win

