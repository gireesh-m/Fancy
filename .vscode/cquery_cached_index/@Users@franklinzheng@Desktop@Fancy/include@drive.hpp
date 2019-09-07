
#ifndef _DRIVE_H_
#define _DRIVE_H_

void reset();

int drivePos();

bool trackerTriggered();

void visionAlignment();

bool isDriving();

void driveTask(void* parameter);
void turnTask(void* parameter);

void driveAsync(int sp);
void turnAsync(int sp);
void drive(int sp);
void turn(int sp);

void setSpeed(int speed);
void setSlant(int s);
void setCurrent(int mA);
void setBrakeMode(int mode);
void driveOp();

#endif
