#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "awp.hpp"



void solo_awp(){
    scoringGate.set_value(true);
    wingMech.set_value(true);
    scoringGate.set_value(true);
    //turn on intake
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    //go perpendicular to loader
    chassis.moveToPoint(0,33,1400,{.maxSpeed=85});
    chassis.turnToHeading(90,800,{.maxSpeed=70});
    //drop loader mech
    loaderMech.set_value(true);
    //ram loader
    chassis.moveToPoint(18,35,1050,{.maxSpeed=100},false);

    //fix lat alignment
    chassis.turnToHeading(90,200,{.maxSpeed=80});
    //go to long goal
    chassis.moveToPoint(-20,35,1000,{.forwards=false,.minSpeed=40},false);
    //let balls score
    scoringGate.set_value(false);
    //wait for blocks to be scored
    pros::delay(1100); 
    //retract loader mech
    loaderMech.set_value(false);
    //swing w 450ms turn
    left_dt.move(127);
    right_dt.move(-127);
    pros::delay(450);
    left_dt.move(0);
    right_dt.move(0);
    //correctional swing turn
    chassis.turnToHeading(187,400);
    // chassis.moveToPoint(-7,35,1000);
    // chassis.turnToPoint(-15,5,400);
    //retract bar once swung
    scoringGate.set_value(true);
    //go to first 3 stack
    chassis.moveToPoint(-10.5,0,1200,{.maxSpeed=80});
    //go to second 3 stack
    chassis.moveToPoint(-8.5,-36,1900,{.minSpeed=35});
    scoringRoller.brake();
    colorsortOn = false;
    //turn opposite of mid goal
    chassis.turnToHeading(133,500);
    //ram mid goal
    chassis.moveToPoint(-23.8,-21.5,1000,{.forwards=false},false);
    //reverse 150ms then push forward to prevent clogging
    middleRollers.move(-127);
    scoringRoller.move(-90);
    frontIntake.move(-127);
    loaderMech.set_value(false);
    pros::delay(200);
    middleRollers.move(127);
    frontIntake.move(127);
    pros::delay(460);
    //scoring recovery
    middleRollers.move(-127);
    pros::delay(110);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(10);
    colorsortOn=true;
    //moves parallel to long goal
    chassis.moveToPoint(17,-61,1300);
    //correctional parallel with goal
    chassis.turnToHeading(90,400);
    //rams goal
    chassis.moveToPoint(-18,-64,1100,{.forwards=false,.minSpeed=40});
    //lets pid settle
    pros::delay(500);
    //lets blocks score
    scoringGate.set_value(false);
    wingMech.set_value(false);
}