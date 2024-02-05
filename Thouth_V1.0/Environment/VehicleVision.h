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
 * VehicleVision.h
*/


#include "AGVConfigurations.h"

#include "Pins.h"

/* This module is responsible of taking an emergency signals comming out another MCU , the vision MCU sends two seperate warrning signal*/
/* and based on the locomotion statue ,the master MCU can translate the warrning signal into an emergency signal*/



/* at the very begging the vision system has to be initalized. */
void VisionInit();


/* check wether the system is safe while rotating or not. */
bool RotationCheck();

/* check wether the system is safe while translating or not. */
bool TranslationCheck();
