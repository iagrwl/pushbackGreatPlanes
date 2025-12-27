#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "skills.hpp"

void autonSkills() {
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(30);
    chassis.setPose(0,-47,180);
    scoringGate.set_value(true);
    //turn on intake
    /*
    left_dt.move(100);
    right_dt.move(100);
    pros::delay(2000);
    left_dt.move(-127);
    right_dt.move(-127);
    pros::delay(500);
    left_dt.move(30);
    right_dt.move(30);
    pros::delay(700);
    left_dt.move(0);    
    right_dt.move(0);
    pros::delay(100);
    */
    chassis.moveToPoint(0,-28,1400,{.forwards=false});
    chassis.turnToPoint(-22,-24,500,{.earlyExitRange=5});
    chassis.moveToPose(-20,-22, -90,1500,{ .minSpeed=60, .earlyExitRange=7},false);
    wallDistance(true,false);
    chassis.turnToPoint(0,0,700,{.forwards=false});
    chassis.moveToPoint(-9,-11,3000,{.forwards = false, .maxSpeed=50},false);
    scoringRoller.move(-127);
    loaderMech.set_value(true);
    chassis.moveToPose(-46,-64,180,4000,{.lead=0.4},false);
    wallDistance(true,true);
    pros::delay(1000);
    chassis.moveToPoint(-46,-50,1000,{.forwards=false});
    wingMech.set_value(true);
    scoringRoller.move(127);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringGate.set_value(true);
    chassis.turnToPoint(-60,-26,1500,{.maxSpeed=60});
    chassis.moveToPoint(-60,-26,1500,{.minSpeed=60,.earlyExitRange=2});
    chassis.turnToHeading(0,1500);
    chassis.moveToPoint(-60,36,3000,{.minSpeed=60,.earlyExitRange=8});
    chassis.turnToPoint(-45,48,1500,{.minSpeed=60,.earlyExitRange=3});
    chassis.moveToPose(-45,48,0,2000,{.maxSpeed=60});
    chassis.turnToHeading(0,1500,{.maxSpeed=80});
    pros::delay(300);
}