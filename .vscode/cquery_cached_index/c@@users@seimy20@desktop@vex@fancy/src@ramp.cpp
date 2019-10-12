#include "main.h"

Motor rampMotor(RAMP, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);

void ramp(int vel){
  rampMotor.move(vel);
}

void rampOp(){
  static int vel;

  if(master.get_digital(DIGITAL_UP)){
    vel = 30;
  }else if(master.get_digital(DIGITAL_DOWN)){
    vel = -30;
  }else{
    vel = 0;
  }

  ramp(vel);
}