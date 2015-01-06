#include "WPILib.h"
#include "MyRobot.h"

Xanthos::Xanthos() {}
void Xanthos::TestInit() {}
void Xanthos::DisabledPeriodic() {}
void Xanthos::AutonomousPeriodic() {}
void Xanthos::AutonomousInit() {}
void Xanthos::TeleopPeriodic() {}
void Xanthos::TestPeriodic() {}

Xanthos::~Xanthos()
{
    delete drive;
    delete joystick;
    delete gearShifter;
    delete shooter;
    delete jaw;
    delete neck;
    delete compressor;
    delete lcd;
}

void Xanthos::RobotInit()
{
    drive = new RobotDrive(LEFT_MOTOR_PWM, RIGHT_MOTOR_PWM);
    joystick = new Joystick(JOY_PORT_1);
    gearShifter = new DoubleSolenoid(FIRST_SOLENOID_BUMPER, GEAR_SHIFT_EXTEND, GEAR_SHIFT_RETRACT);
    shooter = new DoubleSolenoid(FIRST_SOLENOID_BUMPER, SHOOT_EXTEND, SHOOT_RETRACT);
    lock = new DoubleSolenoid(FIRST_SOLENOID_BUMPER, LOCK_LOCK, LOCK_UNLOCK);
    jaw = new DoubleSolenoid(FIRST_SOLENOID_BUMPER, JAW_OPEN, JAW_CLOSE);
    neck = new DoubleSolenoid(FIRST_SOLENOID_BUMPER, NECK_UP, NECK_DOWN);
    compressor = new Compressor(COMPRESSOR_SWITCH, COMPRESSOR_RELAY);
    lcd = DriverStationLCD::GetInstance();
    
    drive->SetSafetyEnabled(false);
    
    pthread_create(&driveThread, NULL, driveFunc, NULL);
    pthread_create(&inputThread, NULL, inputFunc, NULL);
}

void Xanthos::TeleopInit()
{
    compressor->Start();
    driveRun = true;
}

void Xanthos::DisabledInit()
{
    compressor->Stop();
    driveRun = false;
}

void* driveFunc(void* arg)
{
    while(true)
    {
        //drive with tank drive
        if(driveRun)
        {
            drive->TankDrive((joystick->GetRawAxis(JOY_AXIS_LY) / 128.f) * 100, (joystick->GetRawAxis(JOY_AXIS_RY) / 128.f) * 100);
        }

        //syncing crap
        Wait(0.01);
    }
}

void* inputFunc(void* arg)
{
	while(true)
	{
		// Gear shifter input routines
		if(joystick->GetRawButton(JOY_BTN_LTG))
		{
			gearShifter->Set(DoubleSolenoid::kForward);
		}
		if(joystick->GetRawButton(JOY_BTN_RTG))
		{
			gearShifter->Set(DoubleSolenoid::kReverse);
		}

		// Shooter input routines
		if(joystick->GetRawButton(JOY_BTN_A))
		{
			shooter->Set(DoubleSolenoid::kForward);
		}
		if(joystick->GetRawButton(JOY_BTN_B))
		{
			shooter->Set(DoubleSolenoid::kReverse);
		}
		
		//Lock input routines
		if(joystick->GetRawButton(JOY_SPC_LST))
		{
			lock->Set(DoubleSolenoid::kForward);
		}
		if(joystick->GetRawButton(JOY_SPC_RST))
		{
			lock->Set(DoubleSolenoid::kReverse);
		}

		//Jaw input routines
		if(joystick->GetRawButton(JOY_BTN_X))
		{
			jaw->Set(DoubleSolenoid::kForward);
		}
		if(joystick->GetRawButton(JOY_BTN_Y))
		{
			jaw->Set(DoubleSolenoid::kReverse);
		}

		//Neck input routines
		if(joystick->GetRawButton(JOY_BTN_LBM))
		{
			neck->Set(DoubleSolenoid::kForward);
		}
		if(joystick->GetRawButton(JOY_BTN_RBM))
		{
			neck->Set(DoubleSolenoid::kReverse);
		}
		
		Wait(0.01);
	}
}

void* cockingFunc(void* arg)
{
	shooter->Set(DoubleSolenoid::kForward);
	Wait(1);
	lock->Set(DoubleSolenoid::kForward);
	Wait(1);
	shooter->Set(DoubleSolenoid::kReverse);
	pthread_exit(NULL);
}

START_ROBOT_CLASS(Xanthos);
