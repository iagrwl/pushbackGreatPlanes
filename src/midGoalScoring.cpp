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
    pros::delay(100);
    scoringRoller.move(-80);
    frontIntake.move(127);
    middleRollers.move(127);
}