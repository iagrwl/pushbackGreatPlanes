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
    chassis.moveToPoint(13,-48,500,{.minSpeed=50});
    chassis.moveToPoint(40,-48,1000,{.forwards = false,.minSpeed=50,.earlyExitRange=2});
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
    chassis.setPose(48,-24,180);
    wallDistance(false,false);
    chassis.moveToPose(48,-37,0,600);
    chassis.turnToHeading(325,400,{.direction=AngularDirection::CW_CLOCKWISE,.maxSpeed=70});
    scoringGate.set_value(true);
    
    chassis.moveToPoint(23,-18,900,{.maxSpeed=75});
    chassis.turnToHeading(-90,700);
    


    chassis.moveToPose(-25.5,-20,-90,1500,{.minSpeed=60},false);
    scoringRoller.move(127);
    
    //mid goal movement
    chassis.moveToPose(-2,-2,225,1200,{.forwards=false,.minSpeed=60},false);
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
    scoringRoller.move(-50);


    chassis.moveToPoint(0,0,100,{.forwards=false,.maxSpeed=20},false);
    
    pros::delay(750);
    
    //spin regularly to continue
    frontIntake.move(0);
    middleRollers.move(-100);
    scoringRoller.move(-80);
    loaderMech.set_value(true);
    
    chassis.moveToPoint(-42,-48,1600,{.minSpeed=22},false);
    scoringRoller.move(127);
    frontIntake.move(127);
    middleRollers.move(127);
    chassis.moveToPose(-41.5,-95,180,1000,{.minSpeed=70},false);

    wallDistance(false, true);

    
    chassis.moveToPoint(-48,-25,1250,{.forwards=false},false);
    chassis.moveToPoint(-48, -15, 4500, {.forwards = false, .minSpeed = 80});
    loaderMech.set_value(false);
    scoringGate.set_value(false);
    
}