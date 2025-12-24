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
    chassis.setPose(-16.5, -48, 0);

    // keeps the scoring bar closed
    scoringGate.set_value(true);
    // starts intake system
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(100);
    
    // keeps the wing down
    wingMech.set_value(false);

    // moves to 3 cluster and loader down after 600 ms
    chassis.moveToPose(-24, -24, -15, 3000, {.minSpeed = 40});
    pros::delay(800);
    loaderMech.set_value(true);
    
    //chassis.turnToPoint(-40, -10, 700);
    chassis.moveToPose(-45,-10, -85, 2500, {.lead = 0.3, .minSpeed = 60});
    pros::delay(200);
    loaderMech.set_value(false);
    pros::delay(700);
    loaderMech.set_value(true);
    pros::delay(200);
    chassis.moveToPoint(-36, -30, 1500, {.forwards = false, .minSpeed = 40, .earlyExitRange = 3});
    chassis.moveToPose(-50, -22, 180, 2000, {.forwards = false, .lead = 0.3, .minSpeed =60});
    chassis.swingToHeading(-180, lemlib::DriveSide::LEFT, 750, {.minSpeed = 60});
    chassis.moveToPoint(-48, -18, 1000, {.forwards = false});
    scoringGate.set_value(false);
    pros::delay(450);
    scoringGate.set_value(true);
    chassis.moveToPoint(-48, -64, 1000, {.maxSpeed = 60});
    //pros::delay(500);
    chassis.moveToPoint(-48, -58, 1000, {.forwards = false, .minSpeed = 60, .earlyExitRange = 4});
    chassis.moveToPose(-12, -8, -135, 2500, {.forwards = false, .minSpeed = 20}, false);
    frontIntake.move(0);
    middleRollers.move(100);
    scoringRoller.move(-50);
    pros::delay(1200);
    chassis.moveToPoint(-36, -30, 1500);
    chassis.turnToHeading(170, 750);
    chassis.moveToPoint(-38, -12, 1500, {.forwards = false, .maxSpeed = 60});

    // // faces to goal + loader alley
    // chassis.turnToPoint(-48, -45, 800);

    // // enters the loader using motion chain 
    // chassis.moveToPose(-47, -48, 180, 1500, {.lead = 0.3, .minSpeed = 60, .earlyExitRange = 5});
    // // moves deeper to collect
    // chassis.moveToPoint(-47, -64, 1400, {.minSpeed = 60});
    // pros::delay(150);

    // // verifies that scoring bar is closed
    // scoringGate.set_value(true);

    // // moves back into the goal waits to reach for second then proceeds
    // chassis.moveToPoint(-48, -24, 1500, {.forwards = false});
    // pros::delay(1000);

    // // sets colorsort to off
    // colorsortOn = false;

    // // open scoring bar for 1.4 seconds
    // scoringGate.set_value(false);
    // pros::delay(1400);

    // // closes scoring bar
    // scoringGate.set_value(true);

    // // shuts intake system off
    // scoringRoller.move(0);
    // middleRollers.move(0);
    // frontIntake.move(0);
    // // colorsort switched back on for remainder of match
    // colorsortOn = true;

    // // moves in front of goal
    // chassis.moveToPoint(-48, -50, 1000);

    // // wings the goal
    // chassis.moveToPose(-36, -8, 0, 2500, {.forwards = false,.lead=-0.6}, false);

    // // verifies the bot doesnt get pushed
    // while (chassis.getPose().y < -10) {
    //     chassis.moveToPose(-36.5, -8, 180, 2500, {.forwards = false,.lead=-0.6});
    // }
    // openGate = true;


} 