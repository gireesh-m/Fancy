#include "main.h"


//definition of a tile in encoder ticks
#define TL *469

void start(){
  raiseRamp();
  outtakeAsync();
  delay(1500);
  lowerRamp();
  endtakeAsync();
  intakeAsync();
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

// void autonomous() {
//   reset(); // reset the drive encoders
//
//   Task drive_task(driveTask);
//   Task turn_task(turnTask);
//   Task intake_task(intakeTask);
//   //Task lift_task(liftTask);
//   //Task ramp_task(rampTask);
//
//   switch(auton){
//     case 0:
//       farSideRed();
//       break;
//     case 1:
//       nearSideRed();
//       break;
//     case 2:
//       farSideBlue();
//       break;
//     case 3:
//       nearSideBlue();
//       break;
//     case 4:
//       farSideRed();
//       break;
//     case 5:
//       nearSideRed();
//       break;
//   }
//   farSideBlue();
//
//   drive_task.remove();
//   turn_task.remove();
//   intake_task.remove();
//   //lift_task.remove();
//   //ramp_task.remove();
// }


void firstFour(){
  start();
  intakeAsync();
  drive(0.79 TL);
  delay(1000);
  drive(0.23 TL);
  delay(1000);
  drive(0.23 TL);
  delay(1000);
  endtakeAsync();
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
  intakeAsync();
  drive(0.51 TL);
  delay(1000);
  drive(0.23 TL);
  delay(1000);
  drive(0.23 TL);
  delay(1000);
  drive(0.23 TL);
  delay(1000);
  endtakeAsync();
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

  Task driveTask(driveTask);
  Task turnTask(turnTask);
  Task intakeTask(intakeTask);

  switch(auton){
    case 0:
      firstFour();
      break;
    case 1:
      travelToBot();
      break;
    case 2:
      bottomFour();
      break;
    case 3:
      dropOff();
      break;
  }

  driveTask.remove();
  turnTask.remove();
  intakeTask.remove();
}
