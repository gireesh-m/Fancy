#include "main.h"

//definition of a tile in encoder ticks
#define TL *635

void start(){
  raiseRamp();
  outtakeAsync();
  delay(1500);
  lowerRamp();
  endtakeAsync();
  //intakeAsync();
}

void farSideBlue(){
  start();
  drive(1.1 TL);

}

void nearSideBlue(){
  start();
  drive(1.4 TL);
  delay(3000);
  turn(150);
  drive(1.6 TL);
  endtakeAsync();
  delay(50);
  raiseRamp();
  /*turn(-50);
  drive(1.6 TL);
  endtakeAsync();
  raiseRamp();
  drive(-0.1 TL);*/
}

void nearSideRed(){
  start();
  drive(0.5 TL);
  delay(1000);
  turn(-50);
  drive(-0.8 TL);
  endtakeAsync();
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
  endtakeAsync();
  drive(1.7 TL);
  raiseRamp();
  drive(-0.2 TL);
}

void autonomous() {
  reset(); // reset the drive encoders

  Task drive_task(driveTask);
  Task turn_task(turnTask);
  Task intake_task(intakeTask);
  //Task lift_task(liftTask);
  //Task ramp_task(rampTask);

  /*switch(auton){
    case 0:
      farSide();
      break;
    case 1:
      nearSide();
      break;
    case 2:
      farSide();
      break;
    case 3:
      nearSide();
      break;
    case 4:
      farSide();
      break;
    case 5:
      nearSide();
      break;
  }*/
  farSideBlue();

  drive_task.remove();
  turn_task.remove();
  intake_task.remove();
  //lift_task.remove();
  //ramp_task.remove();
}
