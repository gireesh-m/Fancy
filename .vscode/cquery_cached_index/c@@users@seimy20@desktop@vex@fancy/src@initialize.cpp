#include "main.h"


int auton = 0; // keeps track of what auton is selected
bool mirror = false;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	//sd card stuff

  /*
	FILE* usd_file_read = fopen("/usd/auton.txt", "r");
  char buf[20]; // This just needs to be larger than the contents of the file
  fread(buf, 1, 20, usd_file_read); // passing 1 because a `char` is 1 byte, and 50 b/c it's the length of buf
  auton = buf[0] - '0';
  //auton = fgetc(usd_file_read);
  // Should print "Example text" to the terminal
  fclose(usd_file_read); // always close files when you're done with them

	FILE* usd_file_read_2 = fopen("/usd/mirror.txt", "r");
  char buf_2[20]; // This just needs to be larger than the contents of the file
  fread(buf_2, 1, 20, usd_file_read_2); // passing 1 because a `char` is 1 byte, and 50 b/c it's the length of buf
  mirror = buf_2[0] - '0';

  //auton = fgetc(usd_file_read);
  // Should print "Example text" to the terminal
  fclose(usd_file_read_2); // always close files when you're done with them
  */

  gui();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}
