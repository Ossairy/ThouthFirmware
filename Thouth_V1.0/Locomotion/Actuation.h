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
 * Actuation.h
*/


#include "AGVConfigurations.h"
//#include "Thouth_timers.h"
#include "Pins.h"


#ifdef StepperActuated
 #ifdef Diffrential_Steering
    

    enum StepperSide {Right, Left , Both};

    enum StepperDIR {CW, CCW };

   /* ISR of the Stepper motors ; Toggeling step signal and counting steps */
    void LeftStepperISR();
    void RightStepperISR();

   /* Sets the Required Steps for Right ,Left or Both stepper*/
    void SetReq_Steps(long int Steps , enum StepperSide Side );

    /* Gets the task statue of each stepper */
    bool Get_Stepper_task_statue(enum StepperSide Side);
    

  #endif


#endif


void soso();
void khokho();
