#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "midGoalScoring.hpp"

void scoreMidGoal(){
    // reverse intake but keep scoring roller at 0 so first block just drops
    frontIntake.move(-90);
    middleRollers.move(-90);
    scoringRoller.move(0);
    pros::delay(350);
    frontIntake.move(127);
    middleRollers.move(50);

    // bhargav's curve
    const int totalSteps = 50;   
    const int stepDelay = 20;     

    for (int i = 0; i <= totalSteps; i++) {
        double t = (double)i / totalSteps;  

        double speed = 70 - 35 * t * t;

        scoringRoller.move(-(int)speed);
        pros::delay(stepDelay);
    }

    /*
    frontIntake.move(127);
    middleRollers.move(80);
    scoringRoller.move(40); 
    scoringGate.set_value(false);
    pros::delay(250);
    scoringGate.set_value(true);
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127); 
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(53);
    const int totalSteps = 8;   
    const int stepDelay = 170;     

    for (int i = 0; i <= totalSteps; i++) {
        double t = (double)i / totalSteps;  

        double speed = 45 - 24 * t * t;

        scoringRoller.move(-(int)speed);
        pros::delay(stepDelay);
    }
    */
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
