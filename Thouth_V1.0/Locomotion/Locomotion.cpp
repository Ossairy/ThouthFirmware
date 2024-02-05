

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
 * Locomotion.cpp
*/

#include "Locomotion.h"






   void Right_Actuator_Move_RPM(volatile float rpm,unsigned int steps,enum StepperDIR DIR){
       
       #ifdef Invert_Right_Actuator_DIR
            
          if( DIR == CW )
            
            digitalWrite(Right_Actuator_DIR,HIGH);

          else

            digitalWrite(Right_Actuator_DIR,LOW);
       #else

          if( DIR == CW )
            
            digitalWrite(Right_Actuator_DIR,LOW);

          else

            digitalWrite(Right_Actuator_DIR,HIGH);



       #endif
    
     SetReq_Steps(2*steps,Right);
     unsigned long int t = 50000/(3*rpm);
     settimer1(t);
   }
   void Left_Actuator_Move_RPM(volatile float rpm,unsigned int steps,enum StepperDIR DIR){

       #ifdef Invert_Left_Actuator_DIR
            
          if( DIR == CW )
            
            digitalWrite(Left_Actuator_DIR,HIGH);

          else

            digitalWrite(Left_Actuator_DIR,LOW);
       #else

          if( DIR == CW )
            
            digitalWrite(Left_Actuator_DIR,LOW);

          else

            digitalWrite(Left_Actuator_DIR,HIGH);



       #endif
    
     SetReq_Steps(2*steps,Left);
     unsigned long int t = 50000/(3*rpm);
     settimer2(t);

   }

void Acc_Move(double distance, double speed , enum Locomotion_statue statue , float acceleration){

      /* Resets the actuators assigned timers. */
    Reset_Stepper_task_statue(Right);
    Reset_Stepper_task_statue(Left);
    
    /* Define the refrence vehicle orientation. */

    int reference_angle = Get_AGV_Orientation() ;
    int perverror=0;
    double correction=0;

    /*Define the vehicle heading*/
    enum StepperDIR DIR;
    #ifdef Invert_Vehicle_Heading
     if (statue == Forward)
        DIR = CW;
     else if (statue == Backward)
        DIR = CCW; 

    #else
     if (statue == Forward)
        DIR = CCW;
     else if (statue == Backward)
        DIR = CW;
    #endif
    
    int initial_rpm = 3;

    int target_rpm = (speed*60)/0.36424 ;   /* Calculate the rpm needed for the needed linear velocity based on the system reduction.*/
    float rpm = initial_rpm;
    #ifdef SameSystem_On_Left_Right
      unsigned int steps = distance*Steps_Per_Meter;

      unsigned int Discrite_steps = 5;
      unsigned int temp = 0;

      unsigned int Acc_steps = steps*0.3 ;
      unsigned int Dec_steps = steps*0.95 ;

      Right_Actuator_Move_RPM(initial_rpm ,steps,DIR);
      Left_Actuator_Move_RPM(initial_rpm ,steps,DIR);
    #else
        unsigned int Right_steps = distance*Right_Steps_Per_Meter;
        unsigned int Leftsteps = distance*Left_Steps_Per_Meter;

        Right_Actuator_Move_RPM(rpm,Right_steps,DIR);
        Left_Actuator_Move_RPM(rpm,Left_steps,DIR);
    #endif

 
    while(!(Get_Stepper_task_statue(Left))  || !(Get_Stepper_task_statue(Right))){


       if(TranslationCheck()){

        Stop_Stepper(Right);
        Stop_Stepper(Left);
        while(TranslationCheck());
        delay(1000);
        Acc_Move(distance,speed,statue,acceleration);
        
       }




    THOUTH_GYRO_update();
     int error= reference_angle-Get_AGV_Orientation();
     if(error!=perverror){
      if(abs(error)>0){
       
        if(statue == Forward)
        {
        correction = Orientation_correction_Factor*error;
        }
        else if(statue == Backward) {
        correction = -Orientation_correction_Factor*error;          
        }

     /* Update the new targeted velocities to correct the vehicle orientation. */
      #ifdef Invert_Orientation_Correction
        updatetimer(Right, rpm+correction);
        updatetimer(Left, rpm-correction);         

      #else

        updatetimer(Right, rpm-correction);
        updatetimer(Left, rpm+correction);


      #endif




     }
     
     }

     perverror=error;
     //delay(5);
    


         ///////////////////////////////////////////////////////////////////

      if (Get_Step_Count(Right) < Acc_steps ){


          if(temp > Discrite_steps ){

            //Serial.print("NONO");
            rpm =  acceleration*(60/rpm) + rpm;
            Discrite_steps=temp+5;

                  #ifdef Invert_Orientation_Correction
                       updatetimer(Right, rpm+correction);
                       updatetimer(Left, rpm-correction);         

                        #else

                        updatetimer(Right, rpm-correction);
                        updatetimer(Left, rpm+correction);


                       #endif
            if(rpm > target_rpm){

              rpm = target_rpm;
            }

            }
         





      }else if(Get_Step_Count(Right) > Acc_steps && Get_Step_Count(Right) < Dec_steps ){

        rpm = target_rpm;
        Discrite_steps = 0;

       // Serial.print("SOSO");
      }
      else {

       

        if(temp > Discrite_steps ){

          // Serial.print("KHOKHO");

            rpm =  rpm - (0.01*(60/rpm));

            if (Discrite_steps == 0){
              Discrite_steps = Get_Step_Count(Right) +5;
            }else{
            Discrite_steps=temp+15;
            }

                  #ifdef Invert_Orientation_Correction
                       updatetimer(Right, rpm+correction);
                       updatetimer(Left, rpm-correction);         

                        #else

                        updatetimer(Right, rpm-correction);
                        updatetimer(Left, rpm+correction);


                       #endif
            if(rpm < initial_rpm){

              rpm = initial_rpm;
            }
            

            }


      }

      
    temp = Get_Step_Count(Right);

    //  Serial.print("          ");
    //  Serial.print(rpm);
    //  Serial.print("        to  ");
    //  Serial.println(Discrite_steps);


    }



}

void Move(double distance, double speed , enum Locomotion_statue statue){

    /* Resets the actuators assigned timers. */
    Reset_Stepper_task_statue(Right);
    Reset_Stepper_task_statue(Left);
    
    /* Define the refrence vehicle orientation. */

    int reference_angle = Get_AGV_Orientation() ;
    int perverror=0;
    double correction=0;

    /*Define the vehicle heading*/
    enum StepperDIR DIR;
    #ifdef Invert_Vehicle_Heading
     if (statue == Forward)
        DIR = CW;
     else if (statue == Backward)
        DIR = CCW; 

    #else
     if (statue == Forward)
        DIR = CCW;
     else if (statue == Backward)
        DIR = CW;
    #endif
    

    int target_rpm = (speed*60)/0.36424 ;   /* Calculate the rpm needed for the needed linear velocity based on the system reduction.*/
    int rpm = target_rpm;
    #ifdef SameSystem_On_Left_Right
      unsigned int steps = distance*Steps_Per_Meter;

      Right_Actuator_Move_RPM(rpm,steps,DIR);
      Left_Actuator_Move_RPM(rpm,steps,DIR);
    #else
        unsigned int Right_steps = distance*Right_Steps_Per_Meter;
        unsigned int Leftsteps = distance*Left_Steps_Per_Meter;

        Right_Actuator_Move_RPM(rpm,Right_steps,DIR);
        Left_Actuator_Move_RPM(rpm,Left_steps,DIR);
    #endif

 
    while(!(Get_Stepper_task_statue(Left))  || !(Get_Stepper_task_statue(Right))){

     THOUTH_GYRO_update();
     int error= reference_angle-Get_AGV_Orientation();
     if(error!=perverror){
      if(abs(error)>=1){
       
        if(statue == Forward)
        {
        correction = Orientation_correction_Factor*error;
        }
        else if(statue == Backward) {
        correction = -Orientation_correction_Factor*error;          
        }

     /* Update the new targeted velocities to correct the vehicle orientation. */
      #ifdef Invert_Orientation_Correction
        updatetimer(Right, rpm+correction);
        updatetimer(Left, rpm-correction);         

      #else

        updatetimer(Right, rpm-correction);
        updatetimer(Left, rpm+correction);


      #endif




     }
     
     }

     perverror=error;
     //delay(5);
    }
  // Stop_Stepper(Right);
   //Stop_Stepper(Left);

  }


void SmoothMove(double distance, double speed , enum Locomotion_statue statue){

if (distance >= 0.5){
   //Move(0.01,0.02,statue);
   //Move(0.02,0.04,statue);
   //Move(0.04,0.07,statue);
   //Move(0.06,0.08,statue);

   Move(distance - 0.26 ,speed ,statue);

  /// Move(0.06,0.08,statue);
   //Move(0.04,0.07,statue);
   //Move(0.02,0.04,statue);
  // Move(0.01,0.02,statue);
   }

   else {

    Move(distance ,speed ,statue);


   }


}




  void Rotate(float angle){

    /* Resets the actuators assigned timers. */
    Reset_Stepper_task_statue(Right);
    Reset_Stepper_task_statue(Left);

    /* Define the refrence vehicle orientation. */

    int reference_angle = Get_AGV_Orientation() ;
    
    int steps = (angle/360)*steps_per_full_Rotation ;

  if(angle>reference_angle){
     Right_Actuator_Move_RPM(15,steps,CCW);
     Left_Actuator_Move_RPM(15,steps,CW);
       
     
  } else if(angle<reference_angle){
     Right_Actuator_Move_RPM(15,steps,CW);
     Left_Actuator_Move_RPM(15,steps,CCW);
      
  }

    while(!(Get_Stepper_task_statue(Left))  || !(Get_Stepper_task_statue(Right))){

      delay(5);
    }

  }


void Rotate(float angle, int rpm){

    /* Resets the actuators assigned timers. */
    Reset_Stepper_task_statue(Right);
    Reset_Stepper_task_statue(Left);

    /* Define the refrence vehicle orientation. */

    int reference_angle = Get_AGV_Orientation() ;
    
    int steps = (angle/360)*steps_per_full_Rotation ;

  if(angle>reference_angle){
     Right_Actuator_Move_RPM(rpm,steps,CCW);
     Left_Actuator_Move_RPM(rpm,steps,CW);
       
     
  } else if(angle<reference_angle){
     Right_Actuator_Move_RPM(rpm,steps,CW);
     Left_Actuator_Move_RPM(rpm,steps,CCW);
      
  }

    while(!(Get_Stepper_task_statue(Left))  || !(Get_Stepper_task_statue(Right))){

      delay(5);
    }

  }

  void SmoothRotate( float angle , int rpm ){

   

    Rotate(1.5 , 3);
    Rotate(3.5 , 5);
    Rotate(5 , 10);

    Rotate(angle-20 , rpm);

    Rotate(5 , 10);
    Rotate(3.5 , 5);
    Rotate(1.5 , 3);
  }

  void SmoothRotate( float angle , int rpm ,enum StepperDIR DIR  ){


    

    float correction = Steps_per_Rotation_Correction*angle;

    angle = angle + correction;
    
    //Serial.println(correction);

    Rotate(1.5 , DIR ,3);
    Rotate(3.5 , DIR ,5);
    Rotate(5 , DIR ,10);

    Rotate(angle-20 , DIR ,rpm);

    Rotate(5 , DIR ,10);
    Rotate(3.5 , DIR ,5);
    Rotate(1.5 , DIR ,3);



  }





  void Rotate(float angle , enum StepperDIR DIR ){


    /* Resets the actuators assigned timers. */
    Reset_Stepper_task_statue(Right);
    Reset_Stepper_task_statue(Left);

    /* Define the refrence vehicle orientation. */

    int reference_angle = Get_AGV_Orientation() ;
    
    int steps = (angle/344)*steps_per_full_Rotation ;

  if(DIR == CCW){
     Right_Actuator_Move_RPM(15,steps,CCW);
     Left_Actuator_Move_RPM(15,steps,CW);
       
     
  } else if(DIR == CW){
     Right_Actuator_Move_RPM(15,steps,CW);
     Left_Actuator_Move_RPM(15,steps,CCW);
      
  }

    while(!(Get_Stepper_task_statue(Left))  || !(Get_Stepper_task_statue(Right))){
       //Serial.println(steps_per_full_Rotation);
      //delay(5);
    }


  }

  void Rotate(float angle , enum StepperDIR DIR ,int rpm){


    /* Resets the actuators assigned timers. */
    Reset_Stepper_task_statue(Right);
    Reset_Stepper_task_statue(Left);
    
    
    /* Define the refrence vehicle orientation. */

    int reference_angle = Get_AGV_Orientation() ;
    
    int steps = (angle/360)*(steps_per_full_Rotation) ;

  if(DIR == CCW){
     Right_Actuator_Move_RPM(rpm,steps,CCW);
     Left_Actuator_Move_RPM(rpm,steps,CW);
       
     
  } else if(DIR == CW){
     Right_Actuator_Move_RPM(rpm,steps,CW);
     Left_Actuator_Move_RPM(rpm,steps,CCW);
      
  }

    while(!(Get_Stepper_task_statue(Left))  || !(Get_Stepper_task_statue(Right))){
      
       if(RotationCheck() || TranslationCheck() ){

        Stop_Stepper(Right);
        Stop_Stepper(Left);
        while(RotationCheck() || TranslationCheck() );
        delay(1000);
        Rotate(angle,DIR,rpm);
        
       }

    }


  }