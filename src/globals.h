#ifndef __GLOBALS_H_
#define __GLOBALS_H_

extern RobotDrive      *drive;
extern Joystick        *joystick;
extern DoubleSolenoid  *gearShifter;
extern DoubleSolenoid  *shooter;
extern DoubleSolenoid  *lock;
extern DoubleSolenoid  *jaw;
extern DoubleSolenoid  *neck;
extern Compressor      *compressor;
extern DriverStationLCD*lcd;

extern bool             driveRun;
extern pthread_t        driveThread;
extern pthread_t        inputThread;
extern pthread_t        cockingThread;

#endif