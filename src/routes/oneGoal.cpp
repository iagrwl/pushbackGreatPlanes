#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "oneGoal.hpp"

void one_goal_left() {
    // sets position to top left of park zone facing forwards
    chassis.setPose(-6.75, -47, 0);

    scoringGate.set_value(true);
    // starts intake system
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(100);
    
    // keeps the wing down
    wingMech.set_value(true);

    // moves to 3 cluster and loader down after 600 ms
    chassis.moveToPose(-24, -24, -45, 3000, {.minSpeed = 80, .earlyExitRange = 4});
    pros::delay(500);
    loaderMech.set_value(true);

    chassis.turnToHeading(-135, 750);
    chassis.moveToPose(-46, -68, 180, 3000, {.minSpeed = 40});
    pros::delay(200);
    chassis.moveToPoint(-46, -28, 2000, {.forwards = false}, false);
    scoringGate.set_value(false);
    pros::delay(1000);
    wallDistance(false, true);
    chassis.moveToPoint(-48, -35, 1000);
    chassis.turnToHeading(-135, 750, {.minSpeed = 40, .earlyExitRange = 20});
    chassis.moveToPose(-38, -8, 180, 2000, {.forwards = false});


} 

void one_goal_right() {
    chassis.setPose(6.75, -47, 0);

    scoringGate.set_value(true);
    // starts intake system
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(100);
    
    // keeps the wing down
    wingMech.set_value(true);

    // moves to 3 cluster and loader down after 600 ms
    chassis.moveToPose(24, -24, 45, 3000, {.minSpeed = 90, .earlyExitRange = 4});
    pros::delay(500);
    loaderMech.set_value(true);

    chassis.turnToHeading(135, 750, {.minSpeed = 30, .earlyExitRange = 60});
    chassis.moveToPose(46, -72, 180, 2100, {.minSpeed = 50});
    //pros::delay(200);
    chassis.moveToPoint(45, -28, 2000, {.forwards = false});
    pros::delay(700);
    scoringGate.set_value(false);
    pros::delay(1100);
    wallDistance(false, false);
    chassis.moveToPoint(48, -50, 1500, {.minSpeed = 40, .earlyExitRange = 5});
    //chassis.swingToHeading(215, lemlib::DriveSide::LEFT, 750, {.minSpeed = 40});
    chassis.moveToPose(60, -8, 180, 2000, {.forwards = false, .lead = 0.67});
    wingMech.set_value(false);
    
}