

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
 * Locomotion.h
*/





#include "AGVConfigurations.h"
#include "Thouth_timers.h"
#include "Pins.h"


#include "THOUTH_GYRO.h"
#include "VehicleVision.h"



 enum Locomotion_statue {Forward, Backward , Rotating , Holding };

#ifdef StepperActuated

 #ifdef Diffrential_Steering

   void Right_Actuator_Move_RPM(volatile float rpm,unsigned int steps,enum StepperDIR DIR);
   void Left_Actuator_Move_RPM(volatile float rpm,unsigned int steps,enum StepperDIR DIR);

   void Move(double distance, double speed , enum Locomotion_statue statue);

  void Acc_Move(double distance, double speed , enum Locomotion_statue statue , float acceleration);

   void SmoothMove(double distance, double speed , enum Locomotion_statue statue);

   void Rotate(float angle); /* takes angles from -ve to +ve*/
   void Rotate(float angle , enum StepperDIR DIR );   /* takes angles +ve only */
   void Rotate(float angle, int rpm);
  void Rotate(float angle , enum StepperDIR DIR , int rpm );

   void SmoothRotate( float angle , int rpm );
   void SmoothRotate( float angle , int rpm ,enum StepperDIR DIR  );

 #endif
#endif