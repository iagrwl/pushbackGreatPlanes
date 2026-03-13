#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "oneGoal.hpp"
#include "lemlib-tarball/api.hpp"
ASSET(one_goal_right_txt);
lemlib_tarball::Decoder decoder(one_goal_right_txt);

void one_goal_left() {
chassis.setPose(-6.75, -47, 0);

    scoringGate.set_value(true);
    // starts intake system
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(100);
    
    // keeps the wing down
    wingMech.set_value(true);

    // moves to 3 cluster and loader down after 600 ms
    chassis.moveToPose(-24, -24, -45, 3000, {.minSpeed = 90, .earlyExitRange = 4});
    pros::delay(500);
    loaderMech.set_value(true);

    chassis.turnToHeading(-135, 750, {.minSpeed = 30, .earlyExitRange = 60});
    chassis.moveToPose(-45, -75, 180, 2100, {.minSpeed = 60});
    //pros::delay(200);
    chassis.moveToPoint(-44, -28, 2000, {.forwards = false});
    pros::delay(700);
    scoringGate.set_value(false);
    pros::delay(1100);
    wallDistance(false, true);
    chassis.moveToPoint(-48, -50, 1500, {.minSpeed = 40, .earlyExitRange = 5});
    //chassis.swingToHeading(215, lemlib::DriveSide::LEFT, 750, {.minSpeed = 40});
    wingMech.set_value(false);
    chassis.moveToPose(-37, -8, 180, 2000, {.forwards = false, .lead = 0.67}, false);
    while(true){
        if(chassis.getPose().y < -13) {
            chassis.moveToPose(-37, -8, 180, 1000, {.forwards = false, .maxSpeed = 60});
        } else {
            left_dt.move(0);
            right_dt.move(0);
        }
    }
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
    chassis.moveToPoint(23, -25, 1500, {.minSpeed = 30, .earlyExitRange = 10});
    pros::delay(600);
    loaderMech.set_value(true);
    chassis.turnToHeading(135, 750, {.earlyExitRange = 10});
    chassis.moveToPoint(44, -48, 1200, {.minSpeed = 30, .earlyExitRange = 10});
    chassis.turnToHeading(180, 750, {}, false);
    wallDistance(false, false);
    chassis.moveToPoint(48, -70, 1200);
    chassis.moveToPoint(48, -20, 1500, {.forwards = false});
    pros::delay(700);
    loaderMech.set_value(false);
    scoringGate.set_value(false);
    pros::delay(1200);
    scoringGate.set_value(true);
    wingMech.set_value(false);
    chassis.moveToPoint(58, -50, 1500, {.minSpeed = 40, .earlyExitRange = 5});
    chassis.moveToPoint(56, -13, 1500, {.forwards = false, .maxSpeed = 80});
    pros::delay(400);
    wallDistance(false, false);
    chassis.turnToHeading(180, 750);
    
    while(true){
        if(chassis.getPose().y < -13) {
            chassis.moveToPose(56, -8, 180, 1000, {.forwards = false, .maxSpeed = 60});
        } else {
            left_dt.move(0);
            right_dt.move(0);
        }
    }


    // chassis.setPose(-47, -6.75, 90);
    // frontIntake.move(127);
    // middleRollers.move(127);
    // scoringRoller.move(100);
    // // scoringGate.set_value(true);

    // chassis.follow(decoder["Cluster"], 15, 4000, true,false);
    // loaderMech.set_value(true);

    // chassis.follow(decoder["Loader"], 20, 4000, true);
   
    
}
