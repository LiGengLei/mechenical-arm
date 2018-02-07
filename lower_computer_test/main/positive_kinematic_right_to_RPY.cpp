#include "stdio.h"
#include <iostream>
#include "math.h"
extern "C"{
#include "positive_kinematic_right_to_RPY.h"
using namespace std;
#define pi    3.1415926

void Matrix_Eulerian_Angle(double* matrix3X3,double (&eulerianAngle)[3])
{
        double T[9];
        double EulerAngle[3];
	for(int i=0;i<9;i++)
	{
	   T[i]=*(matrix3X3+i);
	}
        EulerAngle[0] = atan2(T[1], T[0]);
        EulerAngle[1] = atan2(-1 * T[2], (T[0] * cos(EulerAngle[0]) + T[1] * sin(EulerAngle[0])));
        EulerAngle[2] = atan2((T[6] * sin(EulerAngle[0]) - T[7] * cos(EulerAngle[0])), (-1 * T[3] * sin(EulerAngle[0]) + T[4] * cos(EulerAngle[0])));
        for(int i=0;i<3;i++)
        {
            eulerianAngle[i]=EulerAngle[i];
        }
}

int Master_positive_solution(double (&eulerian_angle)[3],double (&pose)[3],double* sixangle)
{ 
   double L1=0.23;
   double d3=0.069;
   double d4=0.256;
   double c1=sqrt(3);
   double six_angle[6];
   double t1,t2,t3,t4,t5,t6;
   double master[4][4];
   for(int i=0;i<6;i++)
  {
	six_angle[i]=*(sixangle+i);
  }
   t1=six_angle[0];
   t2=six_angle[1];
   t3=six_angle[2];
   t4=six_angle[3];
   t5=six_angle[4];
   t6=six_angle[5];
   if (six_angle[0]>=-pi&&six_angle[0]<=pi)
  {
     if (six_angle[1]<=pi&&six_angle[1]>=-pi)
    {
         if (six_angle[2]<=pi&&six_angle[2]>=-pi)
        {
            if (six_angle[3]>=-pi&&six_angle[3]<=pi)
            {
                if (six_angle[4]>=-pi&&six_angle[4]<=pi)
                {
                    if(six_angle[5]>=-pi&&six_angle[5]<=pi)
                    {
                        master[0][0]=sin(t6)*(cos(t4)*((c1*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))/2 + (sin(t3)*(cos(t1)*cos(t2) - sin(t1)*sin(t2)))/2) + cos(t3)*sin(t4)*(cos(t1)*cos(t2) - sin(t1)*sin(t2))) - cos(t6)*(cos(t5)*(sin(t4)*((c1*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))/2 + (sin(t3)*(cos(t1)*cos(t2) - sin(t1)*sin(t2)))/2) - cos(t3)*cos(t4)*(cos(t1)*cos(t2) - sin(t1)*sin(t2))) + sin(t5)*((cos(t1)*sin(t2))/2 + (cos(t2)*sin(t1))/2 - (c1*sin(t3)*(cos(t1)*cos(t2) - sin(t1)*sin(t2)))/2));
                        master[0][1]=cos(t6)*(cos(t4)*((c1*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))/2 + (sin(t3)*(cos(t1)*cos(t2) - sin(t1)*sin(t2)))/2) + cos(t3)*sin(t4)*(cos(t1)*cos(t2) - sin(t1)*sin(t2))) + sin(t6)*(cos(t5)*(sin(t4)*((c1*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))/2 + (sin(t3)*(cos(t1)*cos(t2) - sin(t1)*sin(t2)))/2) - cos(t3)*cos(t4)*(cos(t1)*cos(t2) - sin(t1)*sin(t2))) + sin(t5)*((cos(t1)*sin(t2))/2 + (cos(t2)*sin(t1))/2 - (c1*sin(t3)*(cos(t1)*cos(t2) - sin(t1)*sin(t2)))/2));
                        master[0][2]=sin(t5)*(sin(t4)*((c1*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))/2 + (sin(t3)*(cos(t1)*cos(t2) - sin(t1)*sin(t2)))/2) - cos(t3)*cos(t4)*(cos(t1)*cos(t2) - sin(t1)*sin(t2))) - cos(t5)*((cos(t1)*sin(t2))/2 + (cos(t2)*sin(t1))/2 - (c1*sin(t3)*(cos(t1)*cos(t2) - sin(t1)*sin(t2)))/2);
                        master[0][3]=d3*(cos(t1)*sin(t2) + cos(t2)*sin(t1)) + L1*cos(t1) + d4*((cos(t1)*sin(t2))/2 + (cos(t2)*sin(t1))/2 - (c1*sin(t3)*(cos(t1)*cos(t2) - sin(t1)*sin(t2)))/2);
                        master[1][0]=cos(t6)*(cos(t5)*(sin(t4)*((c1*(cos(t1)*cos(t2) - sin(t1)*sin(t2)))/2 - (sin(t3)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))/2) + cos(t3)*cos(t4)*(cos(t1)*sin(t2) + cos(t2)*sin(t1))) + sin(t5)*((cos(t1)*cos(t2))/2 - (sin(t1)*sin(t2))/2 + (c1*sin(t3)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))/2)) - sin(t6)*(cos(t4)*((c1*(cos(t1)*cos(t2) - sin(t1)*sin(t2)))/2 - (sin(t3)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))/2) - cos(t3)*sin(t4)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)));
                        master[1][1]=- cos(t6)*(cos(t4)*((c1*(cos(t1)*cos(t2) - sin(t1)*sin(t2)))/2 - (sin(t3)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))/2) - cos(t3)*sin(t4)*(cos(t1)*sin(t2) + cos(t2)*sin(t1))) - sin(t6)*(cos(t5)*(sin(t4)*((c1*(cos(t1)*cos(t2) - sin(t1)*sin(t2)))/2 - (sin(t3)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))/2) + cos(t3)*cos(t4)*(cos(t1)*sin(t2) + cos(t2)*sin(t1))) + sin(t5)*((cos(t1)*cos(t2))/2 - (sin(t1)*sin(t2))/2 + (c1*sin(t3)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))/2));
                        master[1][2]=cos(t5)*((cos(t1)*cos(t2))/2 - (sin(t1)*sin(t2))/2 + (c1*sin(t3)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))/2) - sin(t5)*(sin(t4)*((c1*(cos(t1)*cos(t2) - sin(t1)*sin(t2)))/2 - (sin(t3)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))/2) + cos(t3)*cos(t4)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)));
                        master[1][3]=L1*sin(t1) - d3*(cos(t1)*cos(t2) - sin(t1)*sin(t2)) - d4*((cos(t1)*cos(t2))/2 - (sin(t1)*sin(t2))/2 + (c1*sin(t3)*(cos(t1)*sin(t2) + cos(t2)*sin(t1)))/2);
                        master[2][0]=cos(t6)*(cos(t5)*((cos(t3)*sin(t4))/2 + cos(t4)*sin(t3)) - (c1*cos(t3)*sin(t5))/2) - sin(t6)*((cos(t3)*cos(t4))/2 - sin(t3)*sin(t4));
                        master[2][1]=- cos(t6)*((cos(t3)*cos(t4))/2 - sin(t3)*sin(t4)) - sin(t6)*(cos(t5)*((cos(t3)*sin(t4))/2 + cos(t4)*sin(t3)) - (c1*cos(t3)*sin(t5))/2);
                        master[2][2]=- sin(t5)*((cos(t3)*sin(t4))/2 + cos(t4)*sin(t3)) - (c1*cos(t3)*cos(t5))/2;
                        master[2][3]=(c1*d4*cos(t3))/2;
			master[3][0]=0;
			master[3][1]=0;
			master[3][2]=0;
			master[3][3]=1;
                    }
                 }
             }
         }
       }
    }
   double Matrix3X3[9],Eulerian_Angle[3];
   Matrix3X3[0] = master[0][0];
   Matrix3X3[1] = master[1][0];
   Matrix3X3[2] = master[2][0];
   Matrix3X3[3] = master[0][1];
   Matrix3X3[4] = master[1][1];
   Matrix3X3[5] = master[2][1];
   Matrix3X3[6] = master[0][2];
   Matrix3X3[7] = master[1][2];
   Matrix3X3[8] = master[2][2];
   Matrix_Eulerian_Angle(Matrix3X3,Eulerian_Angle);
   for(int i=0;i<3;i++)
   {
         eulerian_angle[i]=Eulerian_Angle[i];
   }
   pose[0]=master[0][3];
   pose[1]=master[1][3];
   pose[2]=master[2][3];
   return 0;	
}
}
