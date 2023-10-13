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
 * Thouth_timers.cpp

*/

#include "Thouth_timers.h"



#ifdef StepperActuated

/**/

/* Initialize two timers for the stepper actuation used in the diffrential steering system*/


 #ifdef Diffrential_Steering

   hw_timer_t *Right_Stepper_Timer  = NULL;
   hw_timer_t *Left_Stepper_Timer  = NULL;

   portMUX_TYPE synch1 = portMUX_INITIALIZER_UNLOCKED;
   portMUX_TYPE synch2 = portMUX_INITIALIZER_UNLOCKED;




   /* Steppers Timer ISR  */

   void IRAM_ATTR onRight_Timer(){
     portENTER_CRITICAL(&synch1);

     RightStepperISR();
     Serial.println("KhoKho");

     /*Left Stepper Exiting condition*/
     if(Right_Stepper_taskcomplete)
      timerEnd(Right_Stepper_Timer);

     portEXIT_CRITICAL(&synch1);

     }

     

   void IRAM_ATTR onLeft_Timer(){
     portENTER_CRITICAL(&synch2);

     LeftStepperISR();
     
     /*Left Stepper Exiting condition*/
      if(Left_Stepper_taskcomplete)
       timerEnd(Left_Stepper_Timer);

     portEXIT_CRITICAL(&synch2);

      }





   void settimer1(long int timeD){

     Right_Stepper_Timer = timerBegin(0, 80, true);
     timerAttachInterrupt(Right_Stepper_Timer, &onRight_Timer, true);
     timerAlarmWrite(Right_Stepper_Timer, timeD, true);
     timerAlarmEnable(Right_Stepper_Timer); //Just Enable


   }
   void settimer2(long int timeD){

 
     Left_Stepper_Timer = timerBegin(0, 80, true);
     timerAttachInterrupt(Left_Stepper_Timer, &onLeft_Timer, true);
     timerAlarmWrite(Left_Stepper_Timer, timeD, true);
     timerAlarmEnable(Left_Stepper_Timer); //Just Enable


    }
    void Stop_Stepper(enum StepperSide Side){

     if(Side == Right)
      timerEnd(Right_Stepper_Timer);
     if(Side == Left)
      timerEnd(Left_Stepper_Timer);


      }



 #endif 

#endif


