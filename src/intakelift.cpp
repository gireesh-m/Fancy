#include "main.h"

Motor intakelift(INTAKELIFT, MOTOR_GEARSET_36, 1, MOTOR_ENCODER_DEGREES);

bool moving = false;
int stopPosition = 0;
int dir = 0;
int lifting = 0;

void liftAsync(int dir) {
  lifting = dir;
}

void liftTask(void* parameter){
  while(1) {
    switch(lifting){
      case -1:
        lift(-60);
        break;
      case 0:
        lift(0);
        break;
      case 1:
        lift(120);
        break;
    }
    delay(20);
  }
}

double liftHeight(){
  return(intakelift.get_position());
}

void lift(int vel){
  if(vel == 0){
    intakelift.move(fminf(-1 * (intakelift.get_position() - stopPosition), 127));
  }else{
    intakelift.move(vel);
  }
}

void liftOp(){
  static int vel;
  intakelift.set_current_limit(2500);
  if (!intakelift.is_over_temp()) {
    // down
    if(master.get_digital(DIGITAL_L2)){
      moving = true;
      dir = -1;
      vel = -60;
    // up
    }else if(master.get_digital(DIGITAL_L1)){
      moving = true;
      dir = 1;
      vel = 120;
    }else{
      moving = false;
      vel = 0;
    }
    if(moving == true){
      stopPosition = intakelift.get_position();
    }

    lift(vel);
  }
}
