




#include "AGVConfigurations.h"
#include <Wire.h>




#ifdef MPU6050_6DOF

#include <MPU6050_light.h>

#endif






void THOUTH_GYRO_init();

void THOUTH_GYRO_update();

float Get_AGV_Orientation();

