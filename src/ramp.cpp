#include "main.h"

Motor rampMotor(RAMP, MOTOR_GEARSET_36, 0, MOTOR_ENCODER_DEGREES);
static int moving = 0;
static int dir = 0;

bool isUp(){
  if(rampMotor.get_position() > 580){
    return(true);
  }
  return(false);
}

bool isDown(){
  if(rampMotor.get_position() < 10){
    return(true);
  }
  return(false);
}

void raiseRamp(){
  while(!isUp()){
    ramp((rampMotor.get_position() * -29/160) + 127);
    delay(10);
  }
  ramp(0);
  moving = false;
}

void lowerRamp(){
  while(!isDown()){
    ramp(-30);
    delay(20);
  }
  ramp(0);
  moving = false;
}

void ramp(int vel){
  if (vel == 0){
    rampMotor.set_brake_mode(MOTOR_BRAKE_HOLD);
  }
  rampMotor.move(vel);
}

void rampOp(){
  static int vel;
  rampMotor.set_current_limit(2500);
  if(!rampMotor.is_over_temp()){
    if(abs(master.get_analog(ANALOG_RIGHT_Y)) > abs(master.get_analog(ANALOG_RIGHT_X))){
      ramp(master.get_analog(ANALOG_RIGHT_Y));
    }else{
      ramp(0);
    }
    if(master.get_digital(DIGITAL_UP)){
      raiseRamp();
    }
  }
}
