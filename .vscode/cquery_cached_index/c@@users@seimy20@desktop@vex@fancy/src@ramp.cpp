#include "main.h"

Motor rampMotor(RAMP, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
static int moving = 0;
static int dir = 0;

bool isUp(){
  if(rampMotor.get_position() <= -10){
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
    ramp(-50);
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
  if(moving){
    if(dir == -1){
      ramp(1.1*(moving * dir) - 10);
    }else{
      ramp(30);
    }
    moving--;
  }

  if(master.get_digital(DIGITAL_UP) && !moving){
    moving = 100;
    dir = -1;
    //ramp(-rampMotor.get_position() - 50);
  }else if(master.get_digital(DIGITAL_DOWN) && !moving){
    moving = 100;
    dir = 1;
    //ramp(50 + rampMotor.get_position());
  }
}
