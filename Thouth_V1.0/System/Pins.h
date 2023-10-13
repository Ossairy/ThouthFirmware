
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

//#include "Arduino.h"
#include "AGVConfigurations.h"



//===========================================================================
//============================= Locomotion System ===========================
//===========================================================================



#ifdef StepperActuated 


 #define Right_Actuator_Step                    2 //4
 #define Right_Actuator_Enable                   99
 #define Right_Actuator_DIR                      5


 #define Left_Actuator_Step                     15
 #define Left_Actuator_Enable                   99
 #define Left_Actuator_DIR                      18  


#endif