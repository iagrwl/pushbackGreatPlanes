#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "awp.hpp"
#include "colorSort.hpp"


void solo_awp(){

    // start
    scoringGate.set_value(true);
    wingMech.set_value(true);
    scoringGate.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    chassis.setPose(16,-48,-90);

    // move forward to push alliance
    chassis.moveToPoint(13,-48,500,{.minSpeed=50});

    // move to in front of loader
    chassis.moveToPoint(38,-48,1000,{.forwards = false,.minSpeed=50,.earlyExitRange=2});
    loaderMech.set_value(true);

    // move into loader
    chassis.moveToPose(42,-80,180,1200,{.minSpeed=75},false);

    // move into goal
    chassis.moveToPoint(46.5,-22,1100,{.forwards=false},false);
    
    // score blocks
    scoringGate.set_value(false);
    pros::delay(1100);
    
    // retract loader
    loaderMech.set_value(false);

    // reset position against goal
    chassis.setPose(48,-24,180);

    // move forward 
    chassis.moveToPose(48,-37,0,600);

    // turn toward cluster
    chassis.turnToHeading(-33,400,{.maxSpeed=50});

    // close hood
    scoringGate.set_value(true);

    // move to cluster
    chassis.moveToPoint(23,-20,800);

    // turn towards second cluster
    chassis.turnToHeading(-94,400);

    // move towards second cluster
    chassis.moveToPoint(-25.5,-21,1100,{},false);
    
    // move to mid goal 
    chassis.moveToPoint(-2,-2,1200,{.forwards=false,.minSpeed=60},false);

    // extend loader - to catch blocks during clog
    loaderMech.set_value(true);
    
    // reverse to unclog for 200ms
    frontIntake.move(-100);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);

    // score into midgoal
    frontIntake.move(100);
    middleRollers.move(75);
    scoringRoller.move(-50);

    // push on mid goal
    chassis.moveToPoint(0,0,500,{.forwards=false,.maxSpeed=20},false);
    pros::delay(750);
    
    // spin irregularly to prevent blocks from sitting in mid goal
    frontIntake.move(0);
    middleRollers.move(-100);
    scoringRoller.move(-80);

    // move in front of loader
    chassis.moveToPoint(-42,-48,1600,{.minSpeed=22},false);

    // spin regularly
    scoringRoller.move(127);
    frontIntake.move(127);
    middleRollers.move(127);

    // move into loader
    chassis.moveToPose(-46,-95,180,1000,{.minSpeed=70},false);

    //wallDistance(false, true);

    // move into long goal
    chassis.moveToPoint(-48,-25,1250,{.forwards=false},false);
    chassis.moveToPoint(-48, -15, 4500, {.forwards = false, .minSpeed = 80});
    loaderMech.set_value(false);
    
    
}