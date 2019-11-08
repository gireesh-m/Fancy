#include "main.h"

static int backing = 0;

Motor intakeLeft(INTAKELEFT, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
Motor intakeRight(INTAKERIGHT, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

void intake(int vel){
  intakeLeft.move(vel);
  intakeRight.move(vel);
}

void intakeOp(){
  static int vel;
  // up
  if(master.get_digital(DIGITAL_X) && !backing){
    backing = 50;
  }

  if(backing){
    vel = -20;
    backing--;
  }else if(master.get_digital(DIGITAL_L1)){
    vel = 100;
  // down
  }else if(master.get_digital(DIGITAL_R1)){
    vel = -50;
  }else{
    vel = 0;
  }
  intake(vel);
}
