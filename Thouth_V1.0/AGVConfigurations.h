
/**
 * THOUTH Automated Guided Vehicle Firmware
 * Copyright (c) 2022 THOUTHFirmware [https://github.com/Ossairy/ThouthFirmware]
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

/**
 * AGVConfiguration.h
 *
 * Basic settings such as:
 *
 * - Type of electronics
 * - Type of Gyroscope sensor
 * - Type of Locomotion Actuation system
 * - LCD controller
 * - Extra features
 *
 * Advanced settings can be found in AGVConfiguration_adv.h
 */


#include "Arduino.h"
//#include "macros.h"
//#include "Pins.h"

 
#ifndef MOTHERBOARD
  #define MOTHERBOARD THOUTH_ESP32_30p 
#endif






//===========================================================================
//============================= Locomotion System ===========================
//===========================================================================
// @section Locomotion



/**/

#define StepperActuated   /* Uncomment If the actuation system depends on Stepper motors. */

//#define GearedDCActuated  /* Uncomment If the actuation system depends on Geared DC motors. */


#define Diffrential_Steering   /* Uncomment If the Steering system depends on Differential Steering System. */

#ifdef Diffrential_Steering

   #define SameSystem_On_Left_Right    /* Comment if the right actuator is not the same as the left actuator */
#endif

//#define Ackerman_Steering    /* Uncomment If the Steering system depends on a Steer wheel . */

#ifdef Ackerman_Steering 

   #define Servo_Steering   /* Uncomment If the Ackerman_Steering system depends on a Servo motor to rotate the  . */
   //#define Stepper_Steering     /* Uncomment If the Ackerman_Steering system depends on a Stepper motor . */   

#endif



 /* Initialize a Flag for each Stepper motors to give a sign for finishing tasks */

extern  bool Right_Stepper_taskcomplete;
extern  bool Left_Stepper_taskcomplete;

/* Define the Actuation System Reduction Ratio */

#ifdef StepperActuated
  
  /* Please choose the right stepping configuration based on your stepper driver hardware */
  #define FullStepping    /* Full Step*/
  //#define HalfStepping  /* 1/2 Step*/
  //#define MicroStepping   /* 1/16 Step*/


  //Replace with your values
  #ifdef FullStepping
    #define Motor_Steps_per_Rotation                           200     /* suitable with the 2 phase stepper with 1.8 step angle */  
  #elif defined(HalfStepping)
    #define Motor_Steps_per_Rotation                           400     /* suitable with the 2 phase stepper with 1.8 step angle */   
  #elif defined(MicroStepping)
  #define Motor_Steps_per_Rotation                             3200     /* suitable with the 2 phase stepper with 1.8 step angle */

  #endif

  #ifdef Diffrential_Steering
    //Replace with your values
    #ifdef SameSystem_On_Left_Right
    #define reduction_ratio                         9  /* Reduction Ratio of the Both Right and Left Stepper actuators */
    
    #else
    //Replace with your values
    #define Right_reduction_ratio                   1  /* Reduction Ratio of the Right Stepper actuators */
    #define Left_reduction_ratio                    1  /* Reduction Ratio of the Left Stepper actuators */ 
    
    #endif

  #endif
   

  #ifdef Ackerman_Steering

    #define reduction_ratio                          1     /* Reduction Ratio of the Main Single Stepper actuators */
  #endif

#endif


#define Wheel_Diameter                               0.127  /*Make sure that you are using the right units.*/

//#define Diameter_Defined_in_INCH 
#define Diameter_Defined_in_METER 
//#define Diameter_Defined_in_MILIMETER

#ifdef StepperActuated
  #ifdef Diffrential_Steering
     #ifdef SameSystem_On_Left_Right
       #define Actuator_Steps_Per_Rotation                  ((reduction_ratio)*(Motor_Steps_per_Rotation))
       #define Meter_Per_rotation                           ((Wheel_Diameter)*3.14)
       #define Steps_Per_Meter                              ((Actuator_Steps_Per_Rotation)/Meter_Per_rotation)
     #else
       #define Right_Actuator_Steps_Per_Rotation            ((Right_reduction_ratio)*(Motor_Steps_per_Rotation))
       #define Left_Actuator_Steps_Per_Rotation             ((Left_reduction_ratio)*(Motor_Steps_per_Rotation))
       #define Meter_Per_rotation                           ((Wheel_Diameter)*3.14)
       #define Right_Steps_Per_Meter                        ((Right_Actuator_Steps_Per_Rotation)/Meter_Per_rotation)
       #define Left_Steps_Per_Meter                         ((Left_Actuator_Steps_Per_Rotation)/Meter_Per_rotation)
      
     #endif
  #endif

#endif

#ifdef Diffrential_Steering

/* Invert any Actuator based on the hardware response */

 //#define Invert_Right_Actuator_DIR
 #define Invert_Left_Actuator_DIR

#else

  //#define Invert_Actuator_DIR

#endif


/**/
#define Vehicle_Rotation_Center_Diameter           32.5/100
#define Meter_per_full_Rotation                    Vehicle_Rotation_Center_Diameter*3.14 

#ifdef StepperActuated
  
  #define Steps_per_Rotation_Correction               (12.5/360)
       
  #ifdef Diffrential_Steering  
    #ifdef SameSystem_On_Left_Right
       #define steps_per_full_Rotation                (Meter_per_full_Rotation*Steps_Per_Meter)
    #else
        #define Right_steps_per_full_Rotation          Meter_per_full_Rotation*Right_Steps_Per_Meter
       #define Left_steps_per_full_Rotation           Meter_per_full_Rotation*Left_Steps_Per_Meter
    
    #endif
  #else
      #define steps_per_full_Rotation                (Meter_per_full_Rotation*Steps_Per_Meter*2)+Steps_per_Rotation_Correction   
  #endif

#endif

//#define Invert_Vehicle_Heading     /* Invert the vehicle heading , uncomment that macro it the vehicle is moving backward when it has to move forward.*/
//===========================================================================
//============================= GyroScope Sensor ===========================
//===========================================================================
// @GyroScope Sensor


// Select your IMU type.

#define MPU6050_6DOF 

//#define IMU_L3G4200D_9DOF


/* Define which axis of rotation your AGV rotates about */
/* Please note that the axis of rotation depends on the orientation of your IMU  */
/* Uncomment only one axis of rotation */
//#define USE_Rotation_about_X      /* Rotation about X-axis */
//#define USE_Rotation_about_Y      /* Rotation about Y-axis */
#define USE_Rotation_about_Z      /* Rotation about Z-axis */ /* Please note that the rotation about z is not filtered so you will have to deal with drift */

/*Uncomment if the holding orientation correction is reversed */
#define Invert_Orientation_Correction


//#define PID_Orientation_correction 

#ifdef  PID_Orientation_correction

 #define Orientation_correction_Kp                                  0.5
 #define Orientation_correction_Ki                                  0.1
 #define Orientation_correction_Kd                                  0.2

#endif

#define Orientation_correction_Factor                              0.5      /* comment if you are using PID control for the orientation correctionj */


