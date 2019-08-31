#include "main.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

 Controller master(CONTROLLER_MASTER);

using okapi::literals::operator""_in;
using okapi::literals::operator""_ft;
using okapi::literals::operator""_deg;
 auto myChassis = okapi::ChassisControllerFactory::create(
   {7, -9}, // Left motors
   {10, -8},   // Right motors
   okapi::AbstractMotor::gearset::green *(3.0/5.0), // Green gearset * extern gear ratio
   {3.25_in, 12.5_in} // 3.25 inch wheels, 12.5 inch wheelbase width
 );

// use 0.99,1.0,7.0 for turns
 auto profileController = okapi::AsyncControllerFactory::motionProfile(
   0.99,  // Maximum linear velocity of the Chassis in m/s
   2.0,  // Maximum linear acceleration of the Chassis in m/s/s
   10.0, // Maximum linear jerk of the Chassis in m/s/s/s
   myChassis // Chassis Controller
 );



void opcontrol() {
	while (true){


			if (master.get_digital(DIGITAL_X) && !competition::is_connected()){
				profileController.generatePath({okapi::Point{0_ft, 0_ft, 0_deg}, okapi::Point{3_ft, 1_ft, 0_deg}}, "A");
  			profileController.setTarget("A");
  			profileController.waitUntilSettled();

			}
			delay(10);
		}
}
