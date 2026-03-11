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
    
  
    chassis.setPose(16,-48,-90);
    chassis.moveToPoint(5,-48,500,{.minSpeed=50});
    chassis.moveToPoint(40,-48,1200,{.forwards = false,.minSpeed=50});
    loaderMech.set_value(true);
    chassis.moveToPose(43.5,-80,180,1200,{.minSpeed=75},false);

    chassis.moveToPose(45,-20,180,1100,{.forwards=false,.minSpeed=55},false);
    scoringGate.set_value(false);
    left_dt.move(-30);
    right_dt.move(-30);
    pros::delay(1100);
    loaderMech.set_value(false);
    left_dt.move(0);
    right_dt.move(0);
    //chassis.setPose(48,-24,180);
    wallDistance(false,false);
    left_dt.move(127);
    right_dt.move(-127);
    pros::delay(450);
    left_dt.move(0);
    right_dt.move(0);
    //correctional swing turn
    chassis.turnToHeading(-77,400);
    scoringGate.set_value(true);
    //41.8 -30.19 -77
   // 26.95 -27.80 
    chassis.moveToPoint(26.95, -27.80,400,{.maxSpeed=75});

    chassis.turnToHeading(-90,400);
    chassis.moveToPose(-21,-27,-90,1500);
    
    //mid goal movement
    chassis.moveToPose(-6,-14.5,-130,1200,{.forwards=false,.minSpeed=60},false);
    loaderMech.set_value(true);
    //mid goal scoring 
    
    //reverse to unclog for 200ms
    frontIntake.move(-100);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);

    //direct into mid goal
    frontIntake.move(100);
    middleRollers.move(75);
    scoringRoller.move(-55);


    chassis.moveToPoint(-7,-14.5,150,{.forwards=false,.maxSpeed=20},false);
    
    pros::delay(550);

    frontIntake.move(100);
    middleRollers.move(127);
    scoringRoller.move(-80);
    pros::delay(100);
    
    frontIntake.move(0);
    middleRollers.move(127);
    scoringRoller.move(-127);
    
    
    chassis.moveToPoint(-40,-45,1600,{.minSpeed=22},false);
    scoringRoller.move(127);
    frontIntake.move(127);
    middleRollers.move(127);
    chassis.moveToPose(-40,-95,180,1350,{.minSpeed=60},false);

    wallDistance(true, true);

    
    chassis.moveToPoint(-48,-25,1250,{.forwards=false},false);
    chassis.moveToPoint(-48, -15, 4500, {.forwards = false, .minSpeed = 80});
    loaderMech.set_value(false);
    scoringGate.set_value(false);
    
}