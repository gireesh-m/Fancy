#include "main.h"

//definition of a tile in encoder ticks
#define TL *846

void start(){
  liftAsync(1);
  delay(2300);
  intakeAsync(-100);
  delay(1000);
  liftAsync(-1);
  delay(1500);
  liftAsync(0);
  intakeAsync(0);
}

void farSideBlue(){
  start();
  setSpeed(60);
  driveAsync(0.8 TL);
  setSpeed(60);
  while(drivePos() < 0.7 TL) delay(20);
  intakeAsync(100);
  driveAsync(1.1 TL);
  setSpeed(60);
  while(drivePos() < 1 TL) delay(20);
  delay(200);
  intakeAsync(0);
  turn(230);
  driveAsync(1.5 TL);
  setSpeed(60);
  while(drivePos() < 1.3 TL) delay(20);
  /*intakeAsync(127);
  drive(0.5 TL);
  delay(200);
  intakeAsync(0);
  drive(-1 TL);
  turn(50);
  drive(0.5 TL);*/
  delay(100);
  raiseRamp();
  intakeAsync(-20);
  driveAsync(-0.4 TL);
  setSpeed(40);
  while(drivePos() > -0.4 TL) delay(20);
}

void nearSideBlue(){
  drive(1 TL);
  drive(-1 TL);
}

void nearSideRed(){
  start();
  drive(0.5 TL);
  delay(1000);
  turn(-50);
  drive(-0.8 TL);
  intakeAsync(0);
  turn(-50);
  drive(1 TL);
  delay(1000);
  raiseRamp();
}

void farSideRed(){
  start();
  drive(1.5 TL);
  delay(1000);
  turn(150);
  intakeAsync(0);
  drive(1.7 TL);
  raiseRamp();
  drive(-0.2 TL);
}


void firstFour(){
  start();
  intakeAsync(127);
  drive(0.79 TL);
  delay(1000);
  drive(0.23 TL);
  delay(1000);
  drive(0.23 TL);
  delay(1000);
  intakeAsync(0);
}

void travelToBot(){
  start();
  drive(-1.2 TL);
  turn(-90);
  drive(1 TL);
  turn(90);
}

void bottomFour(){
  start();
  intakeAsync(127);
  drive(0.51 TL);
  delay(1000);
  drive(0.23 TL);
  delay(1000);
  drive(0.23 TL);
  delay(1000);
  drive(0.23 TL);
  delay(1000);
  intakeAsync(0);
}

void dropOff(){
  start();
  drive(-1.25 TL);
  turn(-90);
  delay(500);
  drive(0.46 TL);
  delay(500);
  raiseRamp();
}


//This is beyond crappy
void autonomous() {
  reset(); // reset the drive encoders

  Task drive_task(driveTask);
  Task turn_task(turnTask);
  Task intake_task(intakeTask);
  Task lift_task(liftTask);

  // switch(auton){
  //   case 0:
  //     firstFour();
  //     break;
  //   case 1:
  //     travelToBot();
  //     break;
  //   case 2:
  //     bottomFour();
  //     break;
  //   case 3:
  //     dropOff();
  //     break;
  // }
  nearSideBlue();

  drive_task.remove();
  turn_task.remove();
  intake_task.remove();
  lift_task.remove();
}
