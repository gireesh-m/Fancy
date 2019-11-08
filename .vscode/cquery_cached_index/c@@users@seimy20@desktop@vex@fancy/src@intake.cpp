#include "main.h"

Motor intakeLeft(INTAKELEFT, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
Motor intakeRight(INTAKERIGHT, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

void intake(int vel){
  intakeLeft.move(vel);
  intakeRight.move(vel);
}

void intakeOp(){
  static int vel;
  // up
  if(master.get_digital(DIGITAL_L1)){ // checks that the flipper is not dangerously far down
    vel = 100;
  // down
  } else if(master.get_digital(DIGITAL_R1)){ // checks that the flipper is not dangerously far up
    vel = -30;
  } else{
    vel = 0;
  }
  intake(vel);
}
