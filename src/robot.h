#ifndef __MY_ROBOT_H_
#define __MY_ROBOT_H_

#include <pthread.h>

void* driveFunc(void* arg);
void* inputFunc(void* arg);
void* cockingFunc(void* arg);

class Xanthos : public IterativeRobot
{
public:
    Xanthos() {};
    ~Xanthos();

    void RobotInit();
    void TeleopInit();
    void DisabledInit();

    // unused functions
    void TestInit() {}
    void DisabledPeriodic() {}
    void AutonomousPeriodic() {}
    void AutonomousInit() {}
    void TeleopPeriodic() {}
    void TestPeriodic() {}
};

#endif