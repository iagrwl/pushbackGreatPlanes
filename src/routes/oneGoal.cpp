#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "oneGoal.hpp"

void one_goal_left() {
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
    chassis.moveToPose(-24, -24, -15, 3000, {.maxSpeed = 80, .minSpeed = 40});
    pros::delay(600);
    loaderMech.set_value(true);

    // faces to goal + loader alley
    chassis.turnToPoint(-48, -45, 800);

    // enters the loader using motion chain 
    chassis.moveToPose(-47, -48, 180, 1500, {.lead = 0.3, .minSpeed = 60, .earlyExitRange = 5});
    // moves deeper to collect
    chassis.moveToPoint(-47, -64, 1400, {.minSpeed = 60});
    pros::delay(150);

    // verifies that scoring bar is closed
    scoringGate.set_value(true);

    // moves back into the goal waits to reach for second then proceeds
    chassis.moveToPoint(-48, -24, 1500, {.forwards = false});
    pros::delay(1000);

    // sets colorsort to off
    colorsortOn = false;

    // open scoring bar for 1.4 seconds
    scoringGate.set_value(false);
    pros::delay(1400);

    // closes scoring bar
    scoringGate.set_value(true);

    // shuts intake system off
    scoringRoller.move(0);
    middleRollers.move(0);
    frontIntake.move(0);
    // colorsort switched back on for remainder of match
    colorsortOn = true;

    // moves in front of goal
    chassis.moveToPoint(-48, -50, 1000);

    // wings the goal
    chassis.moveToPose(-36, -8, 0, 2500, {.forwards = false,.lead=-0.6}, false);

    // verifies the bot doesnt get pushed
    while (chassis.getPose().y < -10) {
        chassis.moveToPose(-36.5, -8, 180, 2500, {.forwards = false,.lead=-0.6});
    }
    openGate = true;
} 

void one_goal_right() {
    // sets position to top right of park zone facing forwards
    chassis.setPose(16.5, -48, 0);

    // keeps the scoring bar closed
    scoringGate.set_value(true);

    // starts intake system
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(100);

    // keeps the wing down
    wingMech.set_value(false);

    // moves to 3 cluster and loader down after 800 ms
    chassis.moveToPose(24, -24, 15, 3000, {.maxSpeed = 80, .minSpeed = 40});
    pros::delay(800);
    loaderMech.set_value(true);
    
    // faces to goal + loader alley
    chassis.turnToPoint(48, -45, 800);

    // enters the loader using motion chain 
    chassis.moveToPose(47, -48, 180, 1500, {.lead=0.3,.minSpeed=60,.earlyExitRange=5});
    // moves deeper to collect
    chassis.moveToPoint(45.5, -64, 1000, {.minSpeed=55});

    //verifies that scoring bar is closed
    scoringGate.set_value(true);
    // moves back into the goal waits to reach for second then proceeds
    chassis.moveToPoint(47, -24, 1500, {.forwards = false});
    pros::delay(1000);
    
    // sets colorsort to off
    colorsortOn = false;

    // open scoring bar for 1.4 seconds
    scoringGate.set_value(false);
    pros::delay(1400);
    
    // closes scoring bar
    scoringGate.set_value(true);

    // shuts intake system off
    scoringRoller.move(0);
    middleRollers.move(0);
    frontIntake.move(0);

    // colorsort switched back on for remainder of match
    colorsortOn = true;
    
    // moves in front of goal
    chassis.moveToPoint(48, -50, 1000);
    // wings the goal
    chassis.moveToPose(57, -8, 180, 2500, {.forwards = false},false);

    // verifies the bot doesnt get pushed
    while (chassis.getPose().y < -10) {
        chassis.moveToPose(57, -8, 180, 2500, {.forwards = false});
    }
    openGate = true;
    
}