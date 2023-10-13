
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
 * Actuation.cpp
*/


#include "Actuation.h"
//#include "Thouth_timers.h"

#ifdef StepperActuated

 #ifdef Diffrential_Steering
    /**/
    /* Initialize the Stepper motors Steps counters */

   long int Right_Step_Count =0;
   long int Left_Step_Count =0;

    /* Initialize the Stepper motors Required Steps to be compared with the counted steps */
   long int Right_Req_Steps =0;
   long int Left_Req_Steps =0;

   /* Initialize a Flag for each Stepper motors to give a sign for finishing tasks */
   bool Right_Stepper_taskcomplete = false;
   bool Left_Stepper_taskcomplete = false;


   /* ISR of the Stepper motors ; Toggeling step signal and counting steps */
    void RightStepperISR(){
      digitalWrite(Right_Actuator_Step, !digitalRead(Right_Actuator_Step));
      Right_Step_Count++;
      if(Right_Step_Count >= Right_Req_Steps){
        Right_Step_Count = 0 ;
        Right_Stepper_taskcomplete = true;
        // END Timer
      }

    }
    void LeftStepperISR(){
      digitalWrite(Left_Actuator_Step, !digitalRead(Left_Actuator_Step));
      Left_Step_Count++;
      if(Left_Step_Count >= Left_Req_Steps){
        Left_Step_Count = 0 ;
        Left_Stepper_taskcomplete = true;
        // END Timer
      }    

      
    }
    void SetReq_Steps(long int InputSteps , enum StepperSide Side ){

      if(Side == Right)
        Right_Req_Steps = InputSteps;
      else if(Side == Left)
        Left_Req_Steps = InputSteps;
      else if(Side == Both){
        Left_Req_Steps = InputSteps;
        Right_Req_Steps = InputSteps;
        }


    }   

   bool Get_Stepper_task_statue(enum StepperSide Side){
      if(Side == Right)
        return Right_Stepper_taskcomplete;
      else if(Side == Left)
        return Left_Stepper_taskcomplete; 
      else{

        Serial.println("Error in Coding");
        return false;
      }   

   }        


  #endif
#endif


void soso(){
Serial.println("   soso");
}

void khokho(){
Serial.println("   KhoKho");
}