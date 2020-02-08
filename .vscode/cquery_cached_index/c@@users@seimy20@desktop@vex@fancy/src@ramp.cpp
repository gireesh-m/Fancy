#include "main.h"

Motor rampMotor(RAMP, MOTOR_GEARSET_36, 0, MOTOR_ENCODER_DEGREES);
static int moving = 0;
static int dir = 0;
bool tank_drive = false;
bool pressed = false;

bool isUp(){
  if(rampMotor.get_position() <= -450){
    return(true);
  }
  return(false);
}

bool isDown(){
  if(rampMotor.get_position() >= 0){
    return(true);
  }
  return(false);
}

void raiseRamp(){
  while(!isUp()){
    ramp((rampMotor.get_position() - 450) * (7/45));
    delay(10);
  }
  moving = false;
}

void lowerRamp(){
  while(!isDown()){
    ramp(30);
    delay(20);
  }
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
  if (!rampMotor.is_over_temp()) {
    if(master.get_digital(DIGITAL_RIGHT) && !pressed){
      tank_drive = !tank_drive;
      pressed = true;
    }
    if(!master.get_digital(DIGITAL_RIGHT) && pressed){
      pressed = false;
    }
    if(tank_drive){
      if(master.get_digital(DIGITAL_UP)){
        ramp(-100);
      }else if(master.get_digital(DIGITAL_DOWN)){
        ramp(50);
      }else{
        ramp(0);
      }
    }else{
      ramp(-master.get_analog(ANALOG_LEFT_Y));
    }
  }
}
