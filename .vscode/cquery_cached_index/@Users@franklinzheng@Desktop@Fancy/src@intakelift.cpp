#include "main.h"

Motor intakelift(INTAKELIFT, MOTOR_GEARSET_36, 0, MOTOR_ENCODER_DEGREES);


bool moving = false;
int stopPosition = 0;
int dir = 0;

void lift(int vel){
  if(vel == 0){
    intakelift.move(fminf(-1 * (intakelift.get_position() - stopPosition), 127));
  }else{
    if(dir == 1 && intakelift.get_position() < 0){
      intakelift.move(vel);
    }
    else if(dir == -1 && intakelift.get_position() > -200){
      intakelift.move(vel);
    }
  }
}

void liftOp(){
  static int vel;
  // up
  if(master.get_digital(DIGITAL_L2)){
    moving = true;
    dir = 1;
    vel = 60;
  // down
  }else if(master.get_digital(DIGITAL_L1)){
    moving = true;
    dir = -1;
    vel = -100;
  }else{
    moving = false;
    vel = 0;
  }
  if(moving == true){
    stopPosition = intakelift.get_position();
  }

  lift(vel);
}
