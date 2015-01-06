RobotDrive      *drive;
Joystick        *joystick;
DoubleSolenoid  *gearShifter;
DoubleSolenoid  *shooter;
DoubleSolenoid  *lock;
DoubleSolenoid  *jaw;
DoubleSolenoid  *neck;
Compressor      *compressor;
DriverStationLCD*lcd;

bool             driveRun;
pthread_t        driveThread;
pthread_t        inputThread;
pthread_t        cockingThread;