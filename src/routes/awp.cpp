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
    loaderMech.set_value(true);
    
    chassis.setPose(16,-48,90);
    chassis.moveToPoint(40,-48,800,{.minSpeed=50,.earlyExitRange=2});
    chassis.moveToPose(45.5,-80,180,1450,{.minSpeed=75},false);

    chassis.moveToPoint(45.5,-22,1200,{.forwards=false},false);
    scoringGate.set_value(false);
    pros::delay(1300);
    loaderMech.set_value(false);
    chassis.setPose(48,-24,180);
    chassis.moveToPoint(48,-37,900);
    
    
    chassis.turnToHeading(333,600);
    scoringGate.set_value(true);
    chassis.moveToPoint(23,-20,800);
    chassis.turnToHeading(-94,400);
    chassis.moveToPoint(-25.5,-22.5,1100,{.minSpeed=45});
    colorsortOn=false;
    chassis.moveToPose(-2,-2,225,1200,{.forwards=false,.minSpeed=60},false);

    frontIntake.move(-100);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);
    frontIntake.move(100);
    middleRollers.move(127);
    scoringRoller.move(-100);
    pros::delay(750);
    frontIntake.move(0);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    loaderMech.set_value(true);
    
    chassis.moveToPoint(-42,-48,1600,{.minSpeed=20},false);
    scoringRoller.move(127);
    frontIntake.move(127);
    middleRollers.move(127);
    chassis.moveToPose(-45,-90,180,1000,{.minSpeed=70},false);

    chassis.moveToPoint(-46,-25,1100,{.forwards=false},false);
    scoringGate.set_value(false);
    colorsortOn=true;



   
}