#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "midGoalScoring.hpp"

void scoreMidGoal(){
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127); 
    pros::delay(130);
    frontIntake.move(100);
    middleRollers.move(50);
    const int totalSteps = 250;   // 2.5 seconds
    const int stepDelay = 10;     // ms

    for (int i = 0; i <= totalSteps; i++) {
        double t = (double)i / totalSteps;  

        double speed = 24 - 6*t + 16*t*(1 - t);

        scoringRoller.move(-(int)speed);
        pros::delay(stepDelay);
    }
}


    /*
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127); 
    pros::delay(100);
    scoringRoller.move(-80);
    frontIntake.move(127);
    middleRollers.move(127);
    */

    /*
    pros::delay(150);
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(150);
    frontIntake.move(100);
    middleRollers.move(45);
    scoringRoller.move(-40);
    */
