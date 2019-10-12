#include "main.h"

Motor intakelift(INTAKELIFT, MOTOR_GEARSET_36, 0, MOTOR_ENCODER_DEGREES);

bool liftDown = false;
bool liftUp = false;
bool moving = false;

void lift(int vel){
  if (vel == 0){
    intakelift.move(-50 * intakelift.get_position());
  }
  intakelift.move(vel);
}

void liftOp(){
  static int vel;
  // up
  if(master.get_digital(DIGITAL_L2)){
    moving = true;
    vel = 110;
  // down
  } else if(master.get_digital(DIGITAL_R2)){
    moving = true;
    vel = -80;
  } else{
    moving = false;
    vel = 0;
  }
  if(moving == true){
    intakelift.tare_position();
  }

  lift(vel);
}
