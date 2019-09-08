#include "main.h"

Motor intakelift(INTAKELIFT, MOTOR_GEARSET_36, 0, MOTOR_ENCODER_DEGREES);

bool liftDown = false;
bool liftUp = false;

void lift(int vel){
  if (vel == 0){
    intakelift.set_brake_mode(MOTOR_BRAKE_HOLD);
  }
  intakelift.move(vel);
}

void liftOp(){
  static int vel;
  // up
  if(master.get_digital(DIGITAL_L2)){
    vel = 110;
  // down
  } else if(master.get_digital(DIGITAL_R2)){
    vel = -80;
  } else{
    vel = 0;
  }
  lift(vel);
}
