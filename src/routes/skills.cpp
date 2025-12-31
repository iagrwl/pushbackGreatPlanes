#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "skills.hpp"
#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "skills.hpp"

void autonSkills() {
    scoringGate.set_value(true);
    wingMech.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    /*
    chassis.setPose(0,-47,180);
    //go in
    left_dt.move(80);
    right_dt.move(80);
    pros::delay(400);
    left_dt.move(30);
    right_dt.move(30);
    //intake first part
    pros::delay(500);
    left_dt.move(0);
    right_dt.move(0);
    pros::delay(700);
    //go in
    left_dt.move(70);
    right_dt.move(70);
    pros::delay(500);
    //intake second part
    left_dt.move(0);
    right_dt.move(0);
    pros::delay(500);
    //go out
    left_dt.move(-40);
    right_dt.move(-40);
    pros::delay(800);
    //go in
    left_dt.move(70);
    right_dt.move(70);
    pros::delay(800);
    //go out
    left_dt.move(-90);
    right_dt.move(-90);
    pros::delay(700);
    //go in 
    left_dt.move(30);
    right_dt.move(30);
    pros::delay(700);
    //stop
    left_dt.move(0);    
    right_dt.move(0);
    pros::delay(800);
    wallDistance(true,true);
    chassis.setPose(chassis.getPose().x,-47,180);

    //line up for mid goal
    chassis.moveToPoint(0,-28,1400,{.forwards=false});
    chassis.turnToPoint(-22,-24,500,{.earlyExitRange=5});
    chassis.moveToPose(-20,-22, -90,1500,{ .minSpeed=60, .earlyExitRange=7},false);
    chassis.turnToPoint(0,0,700,{.forwards=false});
    chassis.moveToPoint(-9,-11,3000,{.forwards = false, .maxSpeed=50});

    //scoring mid goal
    pros::delay(350);
    scoreMidGoal();
    loaderMech.set_value(true);
    pros::delay(500);
    scoringRoller.move(127);
    frontIntake.move(127);
    middleRollers.move(127);

    
    chassis.moveToPose(-45,-64.5,180,3000,{.lead=0.45},false);
    wallDistance(true,true);
    pros::delay(500);
    chassis.moveToPoint(-48,-53,1000,{.forwards=false});
    chassis.turnToPoint(-60,-28,1500,{.maxSpeed=60});
    chassis.moveToPoint(-60,-28,1500,{.minSpeed=60,.earlyExitRange=2});
    chassis.turnToHeading(0,1500,{},false);
    chassis.moveToPoint(-60,40,3000,{.minSpeed=60,.earlyExitRange=8});
    chassis.turnToPoint(-50,20,1500,{.forwards=false,.minSpeed=60,.earlyExitRange=3});
    chassis.moveToPose(-50,20,0,1500,{.forwards=false,.lead=0.2,.maxSpeed=60,.earlyExitRange=5});
    chassis.turnToHeading(0,700,{.minSpeed=80,.earlyExitRange=4});
    chassis.moveToPoint(-50,20,500,{.forwards=false,.minSpeed=60},false);
    scoringGate.set_value(false);
    wallDistance(true,false);
    chassis.setPose(chassis.getPose().x,28, chassis.getPose().theta);
    pros::delay(1300);  
    scoringGate.set_value(true); 
    chassis.moveToPoint(-48,70,3000,{.maxSpeed=60});
    pros::delay(1000);
    chassis.moveToPoint(-48,22,2500,{.forwards=false,.maxSpeed=80});
    pros::delay(1300);
    scoringGate.set_value(false);
    loaderMech.set_value(false);
    pros::delay(2500);
    */
    chassis.setPose(-48,28,0);
    chassis.moveToPose(-16,64,90,2500,{.minSpeed=70,.earlyExitRange=5});
    //loaderMech.set_value(true);
    chassis.turnToHeading(83,500,{.minSpeed=50,.earlyExitRange=3},false);
    right_dt.move(70);
    left_dt.move(65);
    pros::delay(650);
    right_dt.move(100);
    left_dt.move(100);
    pros::delay(1200);
    //loaderMech.set_value(false);
    left_dt.move(0);
    right_dt.move(0);
    chassis.turnToHeading(105,1500,{.earlyExitRange=5},false);
    right_dt.move(-35);
    left_dt.move(-35);
    pros::delay(1500);
    left_dt.move(0);
    right_dt.move(0);

    chassis.turnToHeading(90,1500,{},false);
    wallDistance(true,false);
    chassis.setPose(18,chassis.getPose().y, chassis.getPose().theta);
    pros::delay(200);
    chassis.moveToPose(48,48,135,1500,{.lead=-0.6,.minSpeed=70});
    chassis.turnToHeading(0,1000,{},false);
    wallDistance(true,true);
    chassis.moveToPoint(48,22,3000,{.forwards=false,.maxSpeed=60});
    pros::delay(500);
    scoringGate.set_value(false);
    loaderMech.set_value(true);
    pros::delay(1200);
    chassis.turnToHeading(0,500,{},false);
    wallDistance(true,true);
    scoringGate.set_value(false);
    chassis.moveToPoint(48,70,3000,{.maxSpeed=80});
    pros::delay(1000);
    wingMech.set_value(true);
    scoringGate.set_value(false);
    chassis.turnToPoint(57,26,1500,{.forwards=false,.maxSpeed=60});
    chassis.moveToPoint(57,26,1500,{.forwards=false,.minSpeed=60,.earlyExitRange=2});
    loaderMech.set_value(false);
    chassis.turnToHeading(0,1500);
    chassis.moveToPoint(57,-32,3000,{.forwards=false,.minSpeed=60,.earlyExitRange=8});
    chassis.turnToPoint(48,-45,1500,{.forwards=false,.minSpeed=60,.earlyExitRange=3});
    chassis.moveToPose(48,-45,45,2000,{.forwards=false,.maxSpeed=60});
    chassis.turnToHeading(180,1500,{.maxSpeed=80},false);
    pros::delay(300);
    loaderMech.set_value(true);
    pros::delay(300);
    wallDistance(true,false);
    chassis.moveToPoint(48,-22,2500,{.forwards=false,.minSpeed=80});
    pros::delay(1300);
    scoringGate.set_value(true);
    loaderMech.set_value(false);
    pros::delay(2000);
}

/*
    //SETUP
    chassis.setPose(15,-48,90);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    left_dt.set_brake_mode(pros::MotorBrake::brake);
    right_dt.set_brake_mode(pros::MotorBrake::brake);
    //Q1
    chassis.moveToPoint(48,-48,1400,{.minSpeed=60,.earlyExitRange=8});
    chassis.turnToHeading(180,2000,{.maxSpeed=50},false);
    loaderMech.set_value(true);
    pros::delay(100);
    chassis.moveToPoint(47.5,-65,2500,{.maxSpeed=60},false);
    chassis.turnToHeading(180,500,{.maxSpeed=80});
    loaderMech.set_value(false);
    chassis.moveToPoint(48,-22,2000,{.forwards=false,.minSpeed=80});
    pros::delay(900);
    scoringGate.set_value(true);
    pros::delay(800);
    frontIntake.move(0);
    middleRollers.move(0);
    scoringRoller.move(0);
    pros::delay(200);
    scoringGate.set_value(false);
    chassis.setPose(wallDistance(false,false), -30, chassis.getPose().theta);

    chassis.moveToPoint(48,-36,2000,{.maxSpeed=85});
    pros::delay(200);
    wingMech.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    chassis.turnToPoint(60,-26,1500,{.maxSpeed=60});
    chassis.moveToPoint(60,-26,1500,{.minSpeed=60,.earlyExitRange=2});
    chassis.turnToHeading(0,1500);
    chassis.moveToPoint(60,36,3000,{.minSpeed=60,.earlyExitRange=8});
    chassis.turnToPoint(45,48,1500,{.minSpeed=60,.earlyExitRange=3});
    chassis.moveToPose(45,48,0,2000,{.maxSpeed=60});
    chassis.turnToHeading(0,1500,{.maxSpeed=80});
    pros::delay(300);
    loaderMech.set_value(true);
    pros::delay(300);
    chassis.moveToPoint(46,70,3000,{.maxSpeed=60});
    pros::delay(1000);
    chassis.moveToPoint(46,22,2500,{.forwards=false,.maxSpeed=80});
    pros::delay(1300);
    scoringGate.set_value(true);
    loaderMech.set_value(false);
    pros::delay(2000);
    chassis.setPose(chassis.getPose().x, 30, chassis.getPose().theta);
    chassis.moveToPose(18,63,-90,2500,{.minSpeed=70,.earlyExitRange=5});
    chassis.turnToHeading(-85,500,{.earlyExitRange=3},false);
    scoringGate.set_value(false); 
    right_dt.move(90);
    left_dt.move(90);
    loaderMech.set_value(true);
    pros::delay(1900);
    loaderMech.set_value(false);
    left_dt.move(0);
    right_dt.move(0);
    chassis.turnToHeading(-105,1500,{.earlyExitRange=5},false);
    right_dt.move(-35);
    left_dt.move(-35);
    pros::delay(500);
    left_dt.move(0);
    right_dt.move(0);

    chassis.turnToHeading(-90,1500,{},false);
    chassis.setPose(-17,wallDistance(false,true), chassis.getPose().theta);
    pros::delay(200);
    chassis.moveToPose(-48,48,-135,3000,{.lead=-0.6,.minSpeed=70});
    chassis.turnToHeading(0,1000,{},false);
    chassis.setPose(wallDistance(false,false), chassis.getPose().y, chassis.getPose().theta);
    chassis.moveToPoint(-48,18,3000,{.forwards=false,.maxSpeed=60});
    pros::delay(500);
    scoringGate.set_value(true);
    loaderMech.set_value(true);
    pros::delay(1200);
    chassis.setPose(wallDistance(false,false), 30, chassis.getPose().theta);
    scoringGate.set_value(false);
    chassis.moveToPoint(-48,70,3000,{.maxSpeed=60});
    pros::delay(1000);
    chassis.moveToPoint(-48,22,2500,{.forwards=false,.maxSpeed=90});
    pros::delay(1300);
    scoringGate.set_value(true);
    loaderMech.set_value(false);
    pros::delay(2000);
    chassis.setPose(chassis.getPose().x, 30, chassis.getPose().theta);
    scoringGate.set_value(false); 
    chassis.moveToPoint(-48,36,1000,{.maxSpeed=85});
    pros::delay(200);
    wingMech.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    chassis.turnToPoint(-60,26,1500,{.maxSpeed=60});
    chassis.moveToPoint(-60,26,1500,{.minSpeed=60,.earlyExitRange=2});
    chassis.turnToHeading(180,1500);
    chassis.moveToPoint(-60,-36,3000,{.minSpeed=60,.earlyExitRange=8});
    chassis.turnToPoint(-45,-48,1500,{.minSpeed=60,.earlyExitRange=3});
    chassis.moveToPose(-45,-48,180,2000,{.maxSpeed=60});
    chassis.turnToHeading(180,1500,{.maxSpeed=80},false);
    pros::delay(300);
    loaderMech.set_value(true);
    pros::delay(300);
    chassis.setPose(wallDistance(false, true), chassis.getPose().y, chassis.getPose().theta);
    //pros::lcd::print(5, "Wall Dist: %.2f", wallDistance(false, true));
    pros::lcd::print(6, "Chassis Y: %.2f", chassis.getPose().y);
    pros::lcd::print(7, "Chassis X: %.2f", chassis.getPose().x);
    chassis.moveToPoint(-46,-70,3000,{.maxSpeed=60});
    pros::delay(1000);
    chassis.moveToPoint(-46,-22,2500,{.forwards=false,.minSpeed=80});
    pros::delay(1300);
    scoringGate.set_value(true);
    loaderMech.set_value(false);
    pros::delay(2000);
    //chassis.setPose(chassis.getPose().x, -30, chassis.getPose().theta);
    scoringGate.set_value(false);
    wingMech.set_value(true);
    chassis.moveToPose(-18,-63,90,3000,{.lead=0.5,.minSpeed=80,.earlyExitRange=3});
    chassis.turnToHeading(95,500,{.earlyExitRange=5},false);
    loaderMech.set_value(true);
    right_dt.move(127);
    left_dt.move(127);
    pros::delay(1200);
    left_dt.move(-25);
    right_dt.move(-25);
*/