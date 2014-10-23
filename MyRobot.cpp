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
    gearShifter = new DoubleSolenoid(GEAR_SHIFT_EXTEND, GEAR_SHIFT_RETRACT);
    shooter = new DoubleSolenoid(SHOOT_EXTEND, SHOOT_RETRACT);
    jaw = new DoubleSolenoid(JAW_OPEN, JAW_CLOSE);
    neck = new DoubleSolenoid(NECK_UP, NECK_DOWN);
    compressor = new Compressor(COMPRESSOR_SWITCH, COMPRESSOR_RELAY);
    lcd = DriverStationLCD::GetInstance();
    
    drive->SetSafetyEnabled(false);
    lcd->PrintfLine(DriverStationLCD::kUser_Line2, "Please dear God");
    
    pthread_create(&driveThread, NULL, driveFunc, NULL);
}

void Xanthos::TeleopInit()
{
    compressor->Start();
    driveRun = true;
}

void Xanthos::DisabledInit()
{
    compressor->Stop();
}

void* driveFunc(void* arg)
{
    while(7)
    {
        //drive with tank drive
        if(driveRun)
        {
            drive->TankDrive((joystick->GetRawAxis(JOY_AXIS_LY) / 128.f) * 100, (joystick->GetRawAxis(JOY_AXIS_RY) / 128.f) * 100);
        }

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

        //syncing crap
        Wait(0.005);
    }
}

START_ROBOT_CLASS(Xanthos);
