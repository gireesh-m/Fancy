#include "main.h"

//definition of a tile in encoder ticks
#define TL *846

void start(){
  liftAsync(1);
  intakeAsync(-50);
  delay(1000);
  intakeAsync(-100);
  delay(500);
  liftAsync(-1);
  intakeAsync(0);
  delay(1100);
  liftAsync(0);
}

void stack(){
  raiseRamp();
  drive(0.08 TL);
  delay(15);
  driveAsync(-0.4 TL);
  setSpeed(40);
  while(drivePos() > -0.4 TL) delay(20);
}

void unprotBlue5(){
  start();
  intakeAsync(70);
  setSpeed(60);
  driveAsync(0.8 TL);
  setSpeed(60);
  while(drivePos() < 0.5 TL) delay(20);
  intakeAsync(110);

  turn(5);
  driveAsync(1.1 TL);
  setSpeed(60);
  while(drivePos() < 0.9 TL) delay(20);
  delay(600);
  intakeAsync(0);

  turn(180);
  driveAsync(1.55 TL);
  setSpeed(60);
  while(drivePos() < 1.3 TL) delay(20);
  delay(50);
  drive(-0.05 TL);
  delay(50);
  stack();
}

void unprotBlue8(){
  start();
  intakeAsync(70);
  setSpeed(60);
  driveAsync(0.8 TL);
  setSpeed(60);
  while(drivePos() < 0.5 TL) delay(20);
  intakeAsync(110);

  //turn(5);
  driveAsync(1.1 TL);
  setSpeed(60);
  while(drivePos() < 0.9 TL) delay(20);
  delay(600);
  intakeAsync(0);

  drive(-0.6 TL);
  turn(-60);
  drive(-1.12 TL);
  turn(60);
  drive(-0.4 TL);
  delay(20);

  intakeAsync(110);
  driveAsync(1.3 TL);
  setSpeed(60);
  while(drivePos() < 01.1 TL) delay(20);
  delay(600);
  intakeAsync(0);

  turn(180);
  driveAsync(1.55 TL);
  setSpeed(60);
  while(drivePos() < 1.3 TL) delay(20);
  delay(50);
  drive(-0.05 TL);
  delay(50);
  stack();
}

void unprotRed(){
  start();
  intakeAsync(70);
  setSpeed(60);
  driveAsync(0.8 TL);
  setSpeed(60);
  while(drivePos() < 0.5 TL) delay(20);
  intakeAsync(110);
  turn(5);
  driveAsync(1.1 TL);
  setSpeed(60);
  while(drivePos() < 0.9 TL) delay(20);
  delay(700);
  intakeAsync(0);
  turn(-165);
  driveAsync(1.55 TL);
  setSpeed(60);
  while(drivePos() < 1.3 TL) delay(20);
  delay(50);
  drive(-0.05 TL);
  delay(50);
  stack();
}

void protBlue(){
  drive(1 TL);
  drive(-1 TL);
}

void protSideRed(){
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

void unprotSideRed(){
  start();
  drive(1.5 TL);
  delay(1000);
  turn(150);
  intakeAsync(0);
  drive(1.7 TL);
  raiseRamp();
  drive(-0.2 TL);
}

void oneCube(){
  drive(1 TL);
  delay(500);
  drive(-1 TL);
  delay(500);
  start();
  turn(-100);
}

void autonomous() {
  reset(); // reset the drive encoders

  Task drive_task(driveTask);
  Task turn_task(turnTask);
  Task intake_task(intakeTask);
  Task lift_task(liftTask);

  unprotBlue8();

  drive_task.remove();
  turn_task.remove();
  intake_task.remove();
  lift_task.remove();
}
