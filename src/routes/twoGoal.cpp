#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "twoGoal.hpp"

void two_goal_RIGHT(){
    //nothing here
    chassis.setPose(6.75, -47, 0);

    scoringGate.set_value(true);
    // starts intake system
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    
    // keeps the wing down
    wingMech.set_value(true);

    // moves to 3 cluster and loader down after 600 ms
    chassis.moveToPoint(20, -20, 3000, {.minSpeed = 60});
    pros::delay(500);
    loaderMech.set_value(true);

    chassis.turnToHeading(150, 750, {.minSpeed = 30, .earlyExitRange = 60});
    chassis.moveToPose(46, -75, 180, 2500, {.minSpeed = 80});

    chassis.moveToPoint(47, -28, 2000, {.forwards = false});
    pros::delay(600);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    pros::delay(450);
    frontIntake.move(-20);
    middleRollers.move(-20);
    scoringRoller.move(-20);

    pros::delay(500);
    scoringGate.set_value(true);

    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);

    chassis.moveToPoint(48, -60, 1500, {}, false);

    wallDistance(false, false);

    chassis.turnToHeading(-45, 750);

    loaderMech.set_value(false);

    chassis.moveToPose(0, -15, -45, 2000, {}, false);
    
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);



}

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
    chassis.moveToPose(-24, -24, -45, 3000, {.minSpeed = 60});
    //pros::delay(900);
    //loaderMech.set_value(true);
    
    //chassis.turnToPoint(-40, -10, 700);
    chassis.moveToPose(-47,-10, -90, 1300, {.lead = 0.55, .minSpeed = 60});
    //pros::delay(200);
    pros::delay(800);
    loaderMech.set_value(true);
    pros::delay(200);
    chassis.turnToHeading(-90, 700, {.minSpeed = 100});
    chassis.moveToPoint(-24, -36, 1500, {.forwards = false, .minSpeed = 40, .earlyExitRange = 3});
    chassis.moveToPoint(-45, -48, 1500, {.minSpeed = 40, .earlyExitRange = 4});
    loaderMech.set_value(false);
    chassis.turnToHeading(180, 500, {}, false);
    wallDistance(false, true);
    chassis.moveToPoint(-46.5, -18, 1700, {.forwards = false});
    pros::delay(550);
    loaderMech.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    pros::delay(450);
    frontIntake.move(-20);
    middleRollers.move(-20);
    scoringRoller.move(-20);
    chassis.moveToPoint(-48, -45, 1650, {.minSpeed = 40, .earlyExitRange = 5}, false);
    scoringGate.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    chassis.moveToPoint(-48, -80, 1200, {.maxSpeed = 50});
    pros::delay(500);
    
    //pros::delay(500);
    chassis.moveToPoint(-48, -57, 1000, {.forwards = false, .minSpeed = 127, .earlyExitRange = 6});
    chassis.moveToPose(-10, -13, -135, 2500, {.forwards = false, .minSpeed = 40}, false);
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(0);
    pros::delay(400);

    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(-127);

    chassis.moveToPoint(0,0,1000,{.forwards=false,.maxSpeed=20});

    
    pros::delay(1400);
    middleRollers.move(127);
    scoringRoller.move(127);
    chassis.moveToPoint(-37, -37, 1500, {});
    chassis.turnToHeading(180, 750, {.minSpeed = 20, .earlyExitRange = 40}, false);

    chassis.moveToPose(-37, -10, 180, 3000, {.forwards = false, .lead = 0.3});
    wingMech.set_value(false);
}

void two_goal_RUSH() {
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
    chassis.moveToPose(-24, -24, -45, 3000, {.minSpeed = 60});
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
    pros::delay(650);
    wallDistance(false, true);
    frontIntake.move(-20);
    middleRollers.move(-20);
    scoringRoller.move(-20);
    chassis.moveToPoint(-48, -68, 1650, {.maxSpeed = 55});
    pros::delay(500);
    scoringGate.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    //pros::delay(500);
    chassis.moveToPoint(-44, -57, 1000, {.forwards = false, .minSpeed = 127, .earlyExitRange = 6});
    wallDistance(true, false);
    chassis.moveToPose(-9, -13, -135, 2500, {.forwards = false, .minSpeed = 40}, false);
    frontIntake.move(-100);
    middleRollers.move(-127);
    scoringRoller.move(0);

    pros::delay(200);

    chassis.moveToPoint(0,0,1000,{.forwards=false,.maxSpeed=20});

    //scoreMidGoal();
    // bool isOff = false;
    // for(int i = 0; i < 12; i++) {
    //     if (isOff) {
    //         frontIntake.move(0);
    //         middleRollers.move(0);
    //         scoringRoller.move(0);
    //         pros::delay(50);
    //     } else {
    //         frontIntake.move(127);
    //         middleRollers.move(80);
    //         scoringRoller.move(-70);
    //         pros::delay(150);
    //     }
    //     isOff = !isOff;

    // }
    frontIntake.move(127);
    middleRollers.move(50);
    scoringRoller.move(-50);
    pros::delay(1200);
    // middleRollers.move(127);
    // scoringRoller.move(127);
    // chassis.moveToPoint(-37, -37, 1500, {});
    // chassis.turnToHeading(180, 750, {.minSpeed = 20, .earlyExitRange = 40}, false);

    // chassis.moveToPose(-37, -10, 180, 3000, {.forwards = false, .lead = 0.3});
    // wingMech.set_value(false); 
}