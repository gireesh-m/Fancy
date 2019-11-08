#include "main.h"

Motor rampMotor(RAMP, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);

void ramp(int vel){
  if (vel == 0){
    rampMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
  }
  rampMotor.move(vel);
}

void rampOp(){
  static int vel;

  if(master.get_digital(DIGITAL_UP)){
    vel = 127;
  }else if(master.get_digital(DIGITAL_DOWN)){
    vel = -50;
  }else{
    vel = 0;

  }

  ramp(vel);
}
