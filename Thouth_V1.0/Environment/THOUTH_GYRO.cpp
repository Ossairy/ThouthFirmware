

#include "THOUTH_GYRO.h"

/* Initialize the IMU  */
#ifdef MPU6050_6DOF

 MPU6050 mpu(Wire);

#endif

void THOUTH_GYRO_init(){
  Wire.begin();

 #ifdef MPU6050_6DOF  
 
   byte status = mpu.begin();
   Serial.print(F("MPU6050 status: "));
   Serial.println(status);
   while(status!=0){ } // stop everything if could not connect to MPU6050
  
   Serial.println(F("Calculating offsets, do not move MPU6050"));
   delay(1000);
   // mpu.upsideDownMounting = true; // uncomment this line if the MPU6050 is mounted upside-down
   mpu.calcOffsets(); // gyro and accelero
   Serial.println("Done!\n");

 #endif

}

void THOUTH_GYRO_update(){
 
 #ifdef MPU6050_6DOF  
    mpu.update();
 #endif


}

float Get_AGV_Orientation(){

 #ifdef MPU6050_6DOF
   #ifdef USE_Rotation_about_X 
     return mpu.getAngleX();
   #elif USE_Rotation_about_Y 
     return mpu.getAngleY();   
   #elif USE_Rotation_about_Z
     return mpu.getAngleZ();    
   #endif
 #endif


}
