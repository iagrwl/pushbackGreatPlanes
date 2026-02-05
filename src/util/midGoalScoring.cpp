#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "midGoalScoring.hpp"

void scoreMidGoal(){
    frontIntake.move(127);
    middleRollers.move(80);
    scoringRoller.move(40); 
    scoringGate.set_value(false);
    pros::delay(300);
    scoringGate.set_value(true);
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127); 
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(80);
    const int totalSteps = 50;   
    const int stepDelay = 10;     

    for (int i = 0; i <= totalSteps; i++) {
        double t = (double)i / totalSteps;  

        double speed = 55 - 35 * t * t;

        scoringRoller.move(-(int)speed);
        pros::delay(stepDelay);
    }
}

/*
void scoreMidGoal(){
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127); 
    pros::delay(200);
    frontIntake.move(100);
    middleRollers.move(70);
    const int totalSteps = 20;   
    const int stepDelay = 10;     

    for (int i = 0; i <= totalSteps; i++) {
        double t = (double)i / totalSteps;  

        double speed = 55 - 30* t * t;

        scoringRoller.move(-(int)speed);
        pros::delay(stepDelay);
    }
}
*/

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
