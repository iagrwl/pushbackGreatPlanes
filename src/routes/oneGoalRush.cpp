#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "oneGoal.hpp"

void L_1G_R() {
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
    chassis.moveToPose(-24, -24, -45, 3000, {.minSpeed = 80});
    //pros::delay(900);
    //loaderMech.set_value(true);
    
    //chassis.turnToPoint(-40, -10, 700);
    chassis.moveToPose(-48,-9, -90, 1300, {.lead = 0.55, .minSpeed = 60});
    //pros::delay(200);
    loaderMech.set_value(false);
    pros::delay(870);
    loaderMech.set_value(true);
    pros::delay(200);
    chassis.turnToHeading(-90, 700, {.minSpeed = 100});
    chassis.swingToHeading(40, lemlib::DriveSide::LEFT, 750, {.minSpeed = 50, .earlyExitRange = 30}, false);
    //chassis.moveToPoint(-48, -40, 400, {.forwards = false, .minSpeed = 127, .earlyExitRange = 12}, false);
    left_dt.move(-127);
    right_dt.move(-127);
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(100);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(1100);
    scoringGate.set_value(false);
    chassis.turnToHeading(180, 750);
    pros::delay(1300);
    wallDistance(false, true);
    //scoringGate.set_value(true);

    chassis.moveToPoint(-48, -33, 1500, {.minSpeed = 40, .earlyExitRange = 5});
    //chassis.swingToHeading(215, lemlib::DriveSide::LEFT, 750, {.minSpeed = 40});
    wingMech.set_value(false);
    chassis.moveToPose(-40, -6, 180, 2000, {.forwards = false, .lead = 0.67, .minSpeed = 110}, false);
    while(true){
        if(chassis.getPose().y < -8) {
            chassis.moveToPose(-37, -6, 180, 1000, {.forwards = false, .maxSpeed = 60});
        } else {
            left_dt.move(0);
            right_dt.move(0);
        }
    }
    


    // chassis.moveToPoint(-28, -26, 3000, {.forwards = false});
    // chassis.moveToPoint(-50, -30, 1000, {.forwards = false, .minSpeed = 90}, false);
    // right_dt.move(-127);
    // left_dt.move(0);
    // pros::delay(1000);
    // right_dt.move(0);
    // left_dt.move(0);
    
    // //chassis.moveToPoint(-48, -18, 1000, {.forwards = false, .minSpeed = 100});
    // scoringGate.set_value(false);
    // pros::delay(1300);
    // wallDistance(false, true);
    // scoringGate.set_value(true);

    // chassis.moveToPoint(-48, -50, 1500, {.minSpeed = 40, .earlyExitRange = 5});
    // //chassis.swingToHeading(215, lemlib::DriveSide::LEFT, 750, {.minSpeed = 40});
    // wingMech.set_value(false);
    // chassis.moveToPose(-58.5, -8, 180, 2000, {.forwards = false, .lead = 0.67}, false);
    // while(true){
    //     if(chassis.getPose().y < -13) {
    //         chassis.moveToPose(59, -8, 180, 1000, {.forwards = false, .maxSpeed = 60});
    //     } else {
    //         left_dt.move(0);
    //         right_dt.move(0);
    //     }
    // }
} 