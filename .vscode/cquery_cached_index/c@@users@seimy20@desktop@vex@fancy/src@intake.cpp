#include "main.h"

static int backing = 0;
static int intaking = 0;

Motor intakeLeft(INTAKELEFT, MOTOR_GEARSET_18, 0, MOTOR_ENCODER_DEGREES);
Motor intakeRight(INTAKERIGHT, MOTOR_GEARSET_18, 1, MOTOR_ENCODER_DEGREES);

void intake(int vel){
  intakeLeft.move(vel);
  intakeRight.move(vel);
}

void intakeAsync() {
  intaking = 1;
}

void outtakeAsync() {
  intaking = -1;
}

void endtakeAsync(){
  intaking = 0;
}

void intakeTask(void* parameter){
  while(1) {
    switch(intaking){
      case -1:
        intake(-50);
        break;
      case 0:
        intake(0);
        break;
      case 1:
        intake(100);
        break;
    }
    delay(20);
  }
}

void intakeOp(){
  static int vel;
  intakeLeft.set_current_limit(2500);
  intakeRight.set_current_limit(2500);
  if (!intakeLeft.is_over_temp() && !intakeRight.is_over_temp()) {
    if(master.get_digital(DIGITAL_A) && !backing){
      backing = 100;
    }

    if(backing){
      vel = -20;
      backing--;
    }else if(master.get_digital(DIGITAL_R1)){
      vel = 127;
    }else if(master.get_digital(DIGITAL_R2)){
      vel = -50;
    }else if(master.get_digital(DIGITAL_LEFT)){
      vel = -120;
    }else{
      vel = 0;
    }
    intake(vel);
  }
}
