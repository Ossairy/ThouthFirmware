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
 * Thouth_timers.h

*/


#include "AGVConfigurations.h"
#include "Actuation.h"

#include "esp_err.h"
#include "esp_attr.h"
#include "soc/soc.h"
#include "soc/timer_periph.h"
#include "esp_intr_alloc.h"
#include "hal/timer_types.h"


//===========================================================================
//============================= Locomotion System ===========================
//===========================================================================



/* Initialize timer for the stepper actuation*/

#ifdef StepperActuated

/**/

/* Initialize two timers for the stepper actuation used in the diffrential steering system*/


 #ifdef Diffrential_Steering


   /* Steppers Timer ISR  */

   void IRAM_ATTR onRight_Timer();
   void IRAM_ATTR onLeft_Timer();



   void settimer1(long int timeD);
   void settimer2(long int timeD);

   /* Stop Stepper used to stop the stepper - Right or Left - at anytime at emergency times with maximum deceleration. */
   void Stop_Stepper(enum StepperSide Side);




 #endif 

#endif


