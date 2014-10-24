#ifndef __MY_ROBOT_H__
#define __MY_ROBOT_H__

#include <pthread.h>

//Hella macros

#define JOY_PORT_1          1
#define JOY_PORT_2          2
#define JOY_PORT_3          3
#define JOY_PORT_4          4

#define JOY_BTN_X           1
#define JOY_BTN_A           2
#define JOY_BTN_B           3
#define JOY_BTN_Y           4

#define JOY_BTN_LBM         5
#define JOY_BTN_RBM         6
#define JOY_BTN_LTG         7
#define JOY_BTN_RTG         8

#define JOY_SPC_BCK         9  //Back button
#define JOY_SPC_STR         10 //Start button
#define JOY_SPC_LST         11 //Push the left stick in
#define JOY_SPC_RST         12 //Push the right stick in

#define JOY_AXIS_LX         1
#define JOY_AXIS_LY         2
#define JOY_AXIS_RX         3
#define JOY_AXIS_RY         4
#define JOY_AXIS_DX         5
#define JOY_AXIS_DY         6

#define LEFT_MOTOR_PWM		1
#define RIGHT_MOTOR_PWM		2

#define FIRST_SOLENOID_BUMPER	1
#define SECOND_SOLENOID_BUMPER	4

#define GEAR_SHIFT_EXTEND	1
#define	GEAR_SHIFT_RETRACT	2
#define SHOOT_EXTEND		3
#define SHOOT_RETRACT		4
#define JAW_OPEN			5
#define JAW_CLOSE			6
#define NECK_UP				7
#define NECK_DOWN			8
#define LOCK_LOCK			1
#define LOCK_UNLOCK			2

#define COMPRESSOR_SWITCH	1
#define COMPRESSOR_RELAY	1

//End hella macros

//Globals (I really don't like having to do this)
RobotDrive      *drive;
Joystick        *joystick;
DoubleSolenoid  *gearShifter;
DoubleSolenoid  *shooter;
DoubleSolenoid	*lock;
DoubleSolenoid  *jaw;
DoubleSolenoid  *neck;
Compressor      *compressor;
DriverStationLCD*lcd;

bool             driveRun;
pthread_t        driveThread;
pthread_t		 inputThread;
pthread_t		 cockingThread;
//End globals

//Lonely prototype
//EDIT: Now has friends
void* driveFunc(void* arg);
void* inputFunc(void* arg);
void* cockingFunc(void* arg);

//Class definition
class Xanthos : public IterativeRobot
{
public:
    Xanthos();
    void TestInit();
    void DisabledPeriodic();
    void AutonomousPeriodic();
    void AutonomousInit();
    void TeleopPeriodic();
    void TestPeriodic();

    ~Xanthos();

    void RobotInit();

    void TeleopInit();

    void DisabledInit();
};

#endif
