#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "twoGoal.hpp"

void two_goal_RIGHT(){
    //nothing here


};

void two_goal_LEFT() {
    // sets position to top left of park zone facing forwards
    chassis.setPose(-6.75, -47, 0);

    // keeps the scoring bar closed
    scoringGate.set_value(true);
    // starts intake system
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(100);
    
    // keeps the wing down
    wingMech.set_value(true);

    // moves to 3 cluster and loader down after 600 ms
    chassis.moveToPose(-24, -24, -45, 3000, {.minSpeed = 40});
    //pros::delay(900);
    //loaderMech.set_value(true);
    
    //chassis.turnToPoint(-40, -10, 700);
    chassis.moveToPose(-45,-10, -85, 2500, {.lead = 0.3, .minSpeed = 60});
    //pros::delay(200);
    loaderMech.set_value(false);
    pros::delay(750);
    loaderMech.set_value(true);
    pros::delay(200);
    chassis.moveToPoint(-35, -30, 1500, {.forwards = false, .minSpeed = 40, .earlyExitRange = 3});
    chassis.swingToHeading(150, lemlib::DriveSide::LEFT, 750);
    chassis.moveToPose(-48, -22, 180, 2000, {.forwards = false, .lead = 0.1, .minSpeed = 100});
    chassis.swingToHeading(-180, lemlib::DriveSide::LEFT, 750, {.minSpeed = 60, .earlyExitRange = 20});
    chassis.moveToPoint(-48, -18, 1000, {.forwards = false});
    scoringGate.set_value(false);
    pros::delay(500);
    scoringGate.set_value(true);
    chassis.moveToPoint(-46, -68, 1500, {.maxSpeed = 80});
    //pros::delay(500);
    //chassis.moveToPoint(-46, -54, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 4});
    chassis.moveToPose(-12, -8, -135, 2500, {.forwards = false, .minSpeed = 40}, false);
    scoreMidGoal();
    pros::delay(1000);
    chassis.moveToPoint(-34, -32, 1500, {.minSpeed = 40, .earlyExitRange = 6});
    //chassis.turnToHeading(160, 750, {.minSpeed = 20, .earlyExitRange = 40});
    chassis.moveToPose(-36, -12, 180, 30000, {.forwards = false, .lead = 0.9});
    wingMech.set_value(false);
} 