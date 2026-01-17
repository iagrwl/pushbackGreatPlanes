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


void keepScoringMid() {
    pros::delay(1000);
    middleRollers.move(127);
}


void autonSkills() {
    scoringGate.set_value(true);
    wingMech.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);

    chassis.setPose(0,-47,180);
    //go in
    left_dt.move(50);
    right_dt.move(50);
    pros::delay(200);

    left_dt.move(-20);
    right_dt.move(-20);
    pros::delay(1400);
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
    pros::delay(400);

    //go in
    left_dt.move(70);
    right_dt.move(70);
    pros::delay(600);

    left_dt.move(-20);
    right_dt.move(-20);
    pros::delay(600);
    //800 before
    //go out of park
    left_dt.move(-80);
    right_dt.move(-80);
    pros::delay(700);
    //go in slow to align
    left_dt.move(30);
    right_dt.move(30);
    pros::delay(800);
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
    chassis.turnToPoint(0,0,700,{.forwards=false,.minSpeed=60,.earlyExitRange=4});
    chassis.moveToPoint(-10,-10.5,3000,{.forwards = false, .maxSpeed=50});

    //scoring mid goal
    pros::delay(900);
    scoreMidGoal();
    scoreMidGoal();
    pros::delay(500);

    //move to 1st loader
    loaderMech.set_value(true);
    pros::delay(500);    

    //chassis.moveToPose(-45,-65,180,4000,{.lead=0.5},false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    chassis.moveToPose(-47.5,-48,180,2400,{.lead=0.3},false);
    wallDistance(true,true);
    scoringGate.set_value(true);
    chassis.moveToPoint(-47.5,-70,2500,{.maxSpeed=55});
    pros::delay(900);
    //collect from 1st loader
    wallDistance(true,true);

    //move to other side to score
    chassis.moveToPoint(-48,-53,1000,{.forwards=false,.minSpeed=60,.earlyExitRange=5});
    frontIntake.move(0);
    loaderMech.set_value(false);
    chassis.turnToPoint(-60,-37,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.moveToPoint(-60,-37,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.turnToHeading(0,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.moveToPoint(-60,34,2000,{.minSpeed=60,.earlyExitRange=8});

    //line up to score
    chassis.turnToPoint(-50,24,1500,{.forwards=false,.minSpeed=60,.earlyExitRange=3});
    frontIntake.move(127);
    chassis.moveToPose(-51,18,0,2000,{.forwards=false,.lead=0.4,.minSpeed=60,.earlyExitRange=5});
    pros::delay(300);
    //chassis.moveToPoint(-50,22,400,{.forwards=false,.minSpeed=70,.earlyExitRange=4});
    //chassis.turnToHeading(0,700,{.minSpeed=80,.earlyExitRange=4});
    loaderMech.set_value(true);

    //score first time in 1st long goal
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(250);
    scoringGate.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(1500);
    wallDistance(true,false);
    chassis.setPose(chassis.getPose().x,28, chassis.getPose().theta);
    pros::delay(1000);

    //collect 2nd loader
    chassis.moveToPoint(-47.5,70,2500,{.maxSpeed=60});
    pros::delay(900);

    //line up to score 2nd time in 1st long goal
    scoringGate.set_value(true);
    chassis.moveToPoint(-48.5,23,2500,{.forwards=false,.minSpeed=80});
    pros::delay(300);
    
    //score 2nd time in 1st long goal
    loaderMech.set_value(false);
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    pros::delay(2000);

    //descore a lil
    chassis.moveToPoint(-48,34,2500,{.minSpeed=127});
    pros::delay(300);
    scoringGate.set_value(true);
    chassis.moveToPoint(-48,20,750,{.forwards=false,.maxSpeed=40});
    //move to far park zone

    chassis.moveToPose(-14,65,90,2500,{.minSpeed=70,.earlyExitRange=5});
    pros::delay(1600);

    //clear far park zone
    loaderMech.set_value(true);
    chassis.turnToHeading(83,500,{.minSpeed=50,.earlyExitRange=3},false);
    scoringGate.set_value(true);
    frontIntake.move(-127);
    chassis.moveToPoint(12,66,1000,{.minSpeed=90},false);
    frontIntake.move(127);
    chassis.moveToPoint(24,66,1500,{.minSpeed=55});
    pros::delay(500);
    loaderMech.set_value(false);
    /*
    right_dt.move(110);
    left_dt.move(107);
    pros::delay(550);
    loaderMech.set_value(false);
    pros::delay(250);
    right_dt.move(90);
    left_dt.move(90);
    pros::delay(500);
    left_dt.move(0);
    right_dt.move(0);
    */
    /*
    chassis.turnToHeading(105,1500,{.minSpeed=60,.earlyExitRange=5},false);
    right_dt.move(-35);
    left_dt.move(-35);
    pros::delay(800);
    left_dt.move(0);
    right_dt.move(0);
    chassis.turnToHeading(90,500,{},false);
    wallDistance(true,false);
    chassis.setPose(18,chassis.getPose().y, chassis.getPose().theta);
    */
    pros::delay(400);
    chassis.swingToHeading(0,lemlib::DriveSide::RIGHT,500,{},false);
    right_dt.move(65);
    left_dt.move(65);
    pros::delay(800);
    wallDistance(true,true);
    /*

    //align with 2nd long goal
    chassis.moveToPose(48,48,135,1500,{.lead=-0.6,.minSpeed=70});
    chassis.turnToHeading(0,500,{},false);
    wallDistance(true,true);
    */
    chassis.turnToPoint(48,48,500,{.forwards=false,.minSpeed=70});
    chassis.moveToPoint(48,48,1500,{.forwards=false,.minSpeed=70,.earlyExitRange=5});
    chassis.moveToPoint(48,24,1500,{.forwards=false,.minSpeed=70});

    //chassis.moveToPose(47.5,24, 0,3000,{.forwards=false,.minSpeed=70});

    //score 1st time in 2nd long goal 
    /* 
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);
    */
    pros::delay(700);
    scoringGate.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    loaderMech.set_value(true);

    //move to collect from 3rd loader
    pros::delay(1000);
    wallDistance(true,true);
    chassis.setPose(chassis.getPose().x,28, chassis.getPose().theta);
    scoringGate.set_value(true);
    chassis.moveToPoint(46,70,3000,{.maxSpeed=70});
    pros::delay(500);

    //prep to score 2nd time in 2nd long goal
    wingMech.set_value(true);
    chassis.moveToPoint(48,24,3000,{.forwards=false,.maxSpeed=70});
    pros::delay(1000);

    //score 2nd time in 2nd long goal   
    /*
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    */
    pros::delay(300);
    scoringGate.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(1800);
    wallDistance(true,true);

    chassis.setPose(48,28,0);
    //prep to score 3rd time in 2nd long goal
    loaderMech.set_value(false);
    scoringGate.set_value(true);
    chassis.moveToPoint(48,45,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.turnToPoint(57,36,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.moveToPoint(61,36,1500,{.minSpeed=60,.earlyExitRange=2});
    chassis.turnToPoint(62,-32,700,{.minSpeed=60},false);
    wallDistance(true,false);
    chassis.moveToPoint(62,-32,3000,{.minSpeed=60,.earlyExitRange=8});
    chassis.turnToHeading(180,750,{},false);
    loaderMech.set_value(true);
    wallDistance(true,false);

    //intake last loader
    loaderMech.set_value(true);
    //chassis.moveToPose(50.5,-60,180,3000,{.minSpeed=60});
    //chassis.moveToPose(50,-49,180,1000,{.minSpeed=60},false);
    //chassis.turnToPoint(49,-48,1000,{.minSpeed=60,.earlyExitRange=5});
    chassis.moveToPose(48,-50, 180, 2000,{.minSpeed=70,.earlyExitRange=5});
    chassis.moveToPoint(48.5,-70, 2000,{.minSpeed=60});
    pros::delay(700);

    //move to score 3rd time in 2nd long goal
    chassis.moveToPoint(48.5,-22,500,{.forwards=false,.minSpeed=80,.earlyExitRange=4},false);

    //score 3rd time in 2nd long goal
    /*
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(300);
    */
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    loaderMech.set_value(false);
    pros::delay(1600);

    //line up to park
    //was 18
    chassis.moveToPose(2,-63,-90,2000,{.lead=0.5,.minSpeed=127,.earlyExitRange=4},false);

    //park
    /*
    right_dt.move(127);
    left_dt.move(127);
    pros::delay(600);
    right_dt.move(-15);
    left_dt.move(-15);
    */
}

    /*
    //move to far park zone
    chassis.moveToPose(-15,65,90,2500,{.minSpeed=70,.earlyExitRange=5});
    pros::delay(1300);

    //clear far park zone
    loaderMech.set_value(true);
    chassis.turnToHeading(83,500,{.minSpeed=50,.earlyExitRange=3},false);
    scoringGate.set_value(true);
    right_dt.move(110);
    left_dt.move(107);
    pros::delay(450);
    loaderMech.set_value(false);
    pros::delay(500);
    right_dt.move(90);
    left_dt.move(90);
    pros::delay(300);
    left_dt.move(0);
    right_dt.move(0);
    chassis.turnToHeading(105,1500,{.minSpeed=60,.earlyExitRange=5},false);
    right_dt.move(-35);
    left_dt.move(-35);
    pros::delay(800);
    left_dt.move(0);
    right_dt.move(0);
    chassis.turnToHeading(90,500,{},false);
    wallDistance(true,false);
    chassis.setPose(18,chassis.getPose().y, chassis.getPose().theta);

    //align with 2nd long goal
    chassis.moveToPose(48,48,135,1500,{.lead=-0.6,.minSpeed=70});
    chassis.turnToHeading(0,500,{},false);
    wallDistance(true,true);
    chassis.moveToPoint(48,24,3000,{.forwards=false,.maxSpeed=60});
    pros::delay(500);

    //score 1st time in 2nd long goal  
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);
    scoringGate.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    loaderMech.set_value(true);
    pros::delay(300);
    scoringGate.set_value(true);

    //move to collect from 3rd loader
    chassis.turnToHeading(0,500,{},false);
    wallDistance(true,true);
    chassis.moveToPoint(46,70,3000,{.maxSpeed=90});
    pros::delay(500);

    //prep to score 2nd time in 2nd long goal
    wingMech.set_value(true);
    chassis.moveToPoint(48,24,3000,{.forwards=false,.minSpeed=80});
    pros::delay(700);

    //score 2nd time in 2nd long goal   
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(300);
    scoringGate.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(1400);
    wallDistance(true,true);


    //prep to score 3rd time in 2nd long goal
    loaderMech.set_value(false);
    scoringGate.set_value(true);
    chassis.moveToPoint(48,45,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.turnToPoint(57,36,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.moveToPoint(57,36,1500,{.minSpeed=60,.earlyExitRange=2});
    chassis.turnToPoint(63,-32,700,{.minSpeed=60});
    wallDistance(true,false);
    chassis.moveToPoint(63,-32,3000,{.minSpeed=60,.earlyExitRange=8});
    chassis.turnToHeading(180,750,{},false);
    loaderMech.set_value(true);
    wallDistance(true,false);

    //intake last loader
    loaderMech.set_value(true);
    chassis.moveToPose(50,-60,175,3000,{.minSpeed=60,.earlyExitRange=8});

    wallDistance(true,false);

    //move to score 3rd time in 2nd long goal
    chassis.moveToPoint(48,-22,500,{.forwards=false,.minSpeed=80,.earlyExitRange=4},false);

    //score 3rd time in 2nd long goal
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(300);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    loaderMech.set_value(false);
    pros::delay(1600);

    //line up to park
    //was 18
    chassis.moveToPose(0,-63,-90,2000,{.lead=0.5,.minSpeed=100,.earlyExitRange=4},false);

    //park
    right_dt.move(127);
    left_dt.move(127);
    pros::delay(600);
    right_dt.move(-15);
    left_dt.move(-15);
    
}
    




///////////////////////////////////////////////////////



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


/*
//prep to score 2nd time in 2nd long goal
    wingMech.set_value(true);
    chassis.turnToPoint(57,32,1500,{.forwards=false,.minSpeed=60,.earlyExitRange=5});
    chassis.moveToPoint(57,32,1500,{.forwards=false,.minSpeed=60,.earlyExitRange=2});
    loaderMech.set_value(false);
    chassis.turnToHeading(0,500,{},false);
    wallDistance(true,true);
    chassis.moveToPoint(61,-32,3000,{.forwards=false,.minSpeed=60,.earlyExitRange=8});
    chassis.turnToHeading(180,750,{},false);
    wallDistance(true,false);
    loaderMech.set_value(true);

    //move to score 2nd time in 2nd long goal
    chassis.turnToPoint(48,-22,500,{.forwards=false,.minSpeed=80,.earlyExitRange=4});
    chassis.moveToPoint(48,-22,2500,{.forwards=false,.minSpeed=80,.earlyExitRange=4});
    chassis.turnToHeading(180,700,{.minSpeed=80,.earlyExitRange=4},false);
    wallDistance(true,false);

    //score 2nd time in 2nd long goal
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    loaderMech.set_value(true);
    pros::delay(2000);

    //intake last loader
    chassis.moveToPoint(48,-70,2500,{.maxSpeed=60});
    scoringGate.set_value(true);
    pros::delay(1000);

    //line up to score last time in 2nd long goal
    chassis.moveToPoint(48,-22,2500,{.forwards=false,.maxSpeed=80});
    pros::delay(1000);

    //score last time in 2nd long goal
    scoringGate.set_value(false);
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    loaderMech.set_value(false);
    pros::delay(2000);
    */

/*
void autonSkills() {
    
    scoringGate.set_value(true);
    wingMech.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    
    chassis.setPose(0,-47,180);
    //go in
    left_dt.move(50);
    right_dt.move(50);
    pros::delay(400);

    left_dt.move(0);
    right_dt.move(0);
    pros::delay(1400);
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
    pros::delay(400);

    //go in
    left_dt.move(70);
    right_dt.move(70);
    pros::delay(1400);
    //800 before
    //go out of park
    left_dt.move(-80);
    right_dt.move(-80);
    pros::delay(700);
    //go in slow to align
    left_dt.move(30);
    right_dt.move(30);
    pros::delay(800);
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
    chassis.turnToPoint(0,0,700,{.forwards=false,.minSpeed=60,.earlyExitRange=4});
    chassis.moveToPoint(-9,-11,3000,{.forwards = false, .maxSpeed=50});

    //scoring mid goal
    pros::delay(350);
    scoreMidGoal();

    //move to 1st loader
    loaderMech.set_value(true);
    pros::delay(500);    
    chassis.moveToPose(-44.5,-65,175,4000,{.lead=0.45},false);
    scoringGate.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(1300);
    //collect from 1st loader
    wallDistance(true,true);


    //collect from 1st loader
    scoringRoller.move(127);
    frontIntake.move(127);
    middleRollers.move(127);
    left_dt.move(80);
    right_dt.move(80);
    pros::delay(1800);
    wallDistance(true,true);

    //move to other side to score
    chassis.moveToPoint(-48,-53,1000,{.forwards=false,.minSpeed=60,.earlyExitRange=5});
    frontIntake.move(0);
    chassis.turnToPoint(-60,-37,1500,{.minSpeed=60,.earlyExitRange=5});
    loaderMech.set_value(false);
    chassis.moveToPoint(-60,-37,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.turnToHeading(0,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.moveToPoint(-60,40,3000,{.minSpeed=60,.earlyExitRange=8});

    //line up to score
    chassis.turnToPoint(-50,18,1500,{.forwards=false,.minSpeed=60,.earlyExitRange=3});
    frontIntake.move(127);
    chassis.moveToPose(-49.5,20,0,1500,{.forwards=false,.lead=0.2,.maxSpeed=60,.earlyExitRange=5});
    chassis.moveToPose(-49.5,20,0,500,{.forwards=false,.lead=0.2,.maxSpeed=60,.earlyExitRange=5});
    //chassis.turnToHeading(0,700,{.minSpeed=80,.earlyExitRange=4});
    loaderMech.set_value(true);

    //score first time in 1st long goal
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(250);
    scoringGate.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(1500);
    wallDistance(true,false);
    chassis.setPose(chassis.getPose().x,28, chassis.getPose().theta);
    pros::delay(1000);

    //collect 2nd loader
    chassis.moveToPoint(-48,70,2500,{.maxSpeed=60});
    pros::delay(800);

   //line up to score
    chassis.turnToPoint(-50,24,1500,{.forwards=false,.minSpeed=60,.earlyExitRange=3});
    frontIntake.move(127);
    chassis.moveToPose(-50,20,0,2000,{.forwards=false,.lead=0.2,.minSpeed=60,.earlyExitRange=5});
    chassis.moveToPoint(-50,20,400,{.forwards=false,.minSpeed=70,.earlyExitRange=4});
    //chassis.turnToHeading(0,700,{.minSpeed=80,.earlyExitRange=4});
    loaderMech.set_value(true);


    //score 2nd time in 1st long goal
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    pros::delay(1700);
    loaderMech.set_value(false);
    wallDistance(true,true);
    /*
    //move to far park zone
    chassis.moveToPose(-15,65,90,2500,{.minSpeed=70,.earlyExitRange=5});
    pros::delay(1300);

    //clear far park zone
    loaderMech.set_value(true);
    chassis.turnToHeading(83,500,{.minSpeed=50,.earlyExitRange=3},false);
    scoringGate.set_value(true);
    right_dt.move(110);
    left_dt.move(107);
    pros::delay(950);
    right_dt.move(90);
    left_dt.move(90);
    pros::delay(300);
    left_dt.move(0);
    right_dt.move(0);
    chassis.turnToHeading(105,1500,{.minSpeed=60,.earlyExitRange=5},false);
    right_dt.move(-35);
    left_dt.move(-35);
    pros::delay(800);
    left_dt.move(0);
    right_dt.move(0);
    chassis.turnToHeading(90,500,{},false);
    wallDistance(true,false);
    chassis.setPose(18,chassis.getPose().y, chassis.getPose().theta);
    

    //align with 2nd long goal
    chassis.setPose(-48,28, 0);
    chassis.moveToPoint(-48,42,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.turnToPoint(48,42,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.moveToPoint(36,42,4000,{.minSpeed=60,.earlyExitRange=5});
    scoringGate.set_value(true);
    //chassis.moveToPose(48,48,135,1500,{.lead=-0.6,.minSpeed=70});
    chassis.turnToHeading(0,500,{},false);
    wallDistance(true,true);
    chassis.moveToPoint(48,24,1000,{.forwards=false,.maxSpeed=60});
    loaderMech.set_value(true);
    chassis.moveToPoint(47,70,4000,{.maxSpeed=50});
    pros::delay(1000);
    wingMech.set_value(true);
    chassis.turnToPoint(57,32,1500,{.forwards=false,.maxSpeed=60});
    chassis.moveToPoint(57,32,1500,{.forwards=false,.minSpeed=60,.earlyExitRange=2});
    loaderMech.set_value(false);
    chassis.turnToHeading(0,1500,{},false);
    wallDistance(true,true);
    chassis.moveToPoint(60,-32,3000,{.forwards=false,.minSpeed=60,.earlyExitRange=8});
    chassis.turnToPoint(45,-45,1500,{.forwards=false,.minSpeed=60,.earlyExitRange=3});
    chassis.moveToPoint(45,-45,2000,{.forwards=false,.maxSpeed=60});
    chassis.turnToHeading(180,1500,{.maxSpeed=80},false);
    wallDistance(true,false);
    pros::delay(300);
    loaderMech.set_value(true);
    pros::delay(300);
    chassis.moveToPoint(48,-22,2500,{.forwards=false,.minSpeed=80});
    pros::delay(1000);
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    loaderMech.set_value(true);
    pros::delay(2000);
    chassis.moveToPoint(48,-750,2500,{.maxSpeed=50});
    pros::delay(1000);
    chassis.moveToPoint(48,-22,2500,{.forwards=false,.maxSpeed=80});
    pros::delay(1000);
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    loaderMech.set_value(false);
    pros::delay(2000);

    //line up to park
    chassis.moveToPose(18,-63,-90,2000,{.lead=0.5,.minSpeed=80,.earlyExitRange=4},false);

    //park
    right_dt.move(127);
    left_dt.move(127);
    pros::delay(700);
    right_dt.move(-15);
    left_dt.move(-15);

}
*/


/*void autonSkills() {
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
    //go out of park
    left_dt.move(-90);
    right_dt.move(-90);
    pros::delay(700);
    //go in slow to align
    left_dt.move(30);
    right_dt.move(30);
    pros::delay(800);
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
    chassis.turnToPoint(0,0,700,{.forwards=false,.minSpeed=60,.earlyExitRange=4});
    chassis.moveToPoint(-9,-11,3000,{.forwards = false, .maxSpeed=50});

    //scoring mid goal
    pros::delay(350);
    scoreMidGoal();

    //move to 1st loader
    loaderMech.set_value(true);
    pros::delay(500);    
    chassis.moveToPose(-45,-64,175,2200,{.lead=0.45},false);

    //collect from 1st loader
    scoringRoller.move(127);
    frontIntake.move(127);
    middleRollers.move(127);
    left_dt.move(80);
    right_dt.move(80);
    pros::delay(1300);
    wallDistance(true,true);

    //move to other side to score
    chassis.moveToPoint(-48,-53,1000,{.forwards=false,.minSpeed=60,.earlyExitRange=5});
    frontIntake.move(0);
    chassis.turnToPoint(-60,-37,1500,{.minSpeed=60,.earlyExitRange=5});
    loaderMech.set_value(false);
    chassis.moveToPoint(-60,-37,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.turnToHeading(0,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.moveToPoint(-60,40,3000,{.minSpeed=60,.earlyExitRange=8});

    //line up to score
    chassis.turnToPoint(-50,18,1500,{.forwards=false,.minSpeed=60,.earlyExitRange=3});
    frontIntake.move(127);
    chassis.moveToPose(-49.5,20,0,1500,{.forwards=false,.lead=0.2,.maxSpeed=60,.earlyExitRange=5});
    chassis.moveToPose(-49.5,20,0,500,{.forwards=false,.lead=0.2,.maxSpeed=60,.earlyExitRange=5});
    //chassis.turnToHeading(0,700,{.minSpeed=80,.earlyExitRange=4});
    loaderMech.set_value(true);

    //score first time in 1st long goal
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(250);
    scoringGate.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(1500);
    wallDistance(true,false);
    chassis.setPose(chassis.getPose().x,28, chassis.getPose().theta);
    pros::delay(1000);

    //collect 2nd loader
    chassis.moveToPoint(-48,70,2500,{.maxSpeed=60});
    pros::delay(800);

    //line up to score 2nd time in 1st long goal
    scoringGate.set_value(true);
    chassis.moveToPoint(-48,23,2500,{.forwards=false,.maxSpeed=80});
    pros::delay(800);

    //score 2nd time in 1st long goal
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    pros::delay(1700);
    loaderMech.set_value(false);
    wallDistance(true,true);
    */
    /*
    //move to far park zone
    chassis.moveToPose(-15,65,90,2500,{.minSpeed=70,.earlyExitRange=5});
    pros::delay(1300);

    //clear far park zone
    loaderMech.set_value(true);
    chassis.turnToHeading(83,500,{.minSpeed=50,.earlyExitRange=3},false);
    scoringGate.set_value(true);
    right_dt.move(110);
    left_dt.move(107);
    pros::delay(950);
    right_dt.move(90);
    left_dt.move(90);
    pros::delay(300);
    left_dt.move(0);
    right_dt.move(0);
    chassis.turnToHeading(105,1500,{.minSpeed=60,.earlyExitRange=5},false);
    right_dt.move(-35);
    left_dt.move(-35);
    pros::delay(800);
    left_dt.move(0);
    right_dt.move(0);
    chassis.turnToHeading(90,500,{},false);
    wallDistance(true,false);
    chassis.setPose(18,chassis.getPose().y, chassis.getPose().theta);

    //align with 2nd long goal
    chassis.setPose(-48,28,0);
    chassis.moveToPoint(-48,42,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.turnToPoint(48,42,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.moveToPoint(36,42,4000,{.minSpeed=60,.earlyExitRange=5});
    //chassis.moveToPose(48,48,135,1500,{.lead=-0.6,.minSpeed=70});
    chassis.turnToHeading(0,500,{},false);
    wallDistance(true,true);
    chassis.moveToPoint(48,24,3000,{.forwards=false,.maxSpeed=60});
    pros::delay(700);

    //score 1st time in 2nd long goal  
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);
    scoringGate.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    loaderMech.set_value(true);
    pros::delay(900);
    scoringGate.set_value(true);

    //move to collect from 3rd loader
    chassis.turnToHeading(0,500,{},false);
    wallDistance(true,true);
    chassis.moveToPoint(46,70,3000,{.maxSpeed=60});
    pros::delay(500);

    //prep to score 2nd time in 2nd long goal
    wingMech.set_value(true);
    chassis.moveToPoint(48,24,3000,{.forwards=false,.minSpeed=60});
    pros::delay(700);

    //score 2nd time in 2nd long goal   
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);
    scoringGate.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(1500);
    wallDistance(true,true);


    //prep to score 3rd time in 2nd long goal
    loaderMech.set_value(false);
    scoringGate.set_value(true);
    chassis.moveToPoint(48,45,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.turnToPoint(57,36,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.moveToPoint(57,36,1500,{.minSpeed=60,.earlyExitRange=2});
    chassis.turnToHeading(180,500,{},false);
    wallDistance(true,false);
    chassis.moveToPoint(61,-32,3000,{.minSpeed=60,.earlyExitRange=8});
    chassis.turnToHeading(180,750,{},false);
    loaderMech.set_value(true);
    wallDistance(true,false);

    //intake last loader
    loaderMech.set_value(true);
    chassis.moveToPose(48,-60,185,3000,{.minSpeed=60,.earlyExitRange=8});
    chassis.turnToHeading(180,750,{},false);
    wallDistance(true,false);

    //move to score 3rd time in 2nd long goal
    chassis.moveToPoint(48,-22,500,{.forwards=false,.minSpeed=80,.earlyExitRange=4},false);

    //score 3rd time in 2nd long goal
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    loaderMech.set_value(false);
    pros::delay(2000);

    //line up to park
    chassis.moveToPose(18,-63,-90,2000,{.lead=0.5,.minSpeed=80,.earlyExitRange=4},false);

    //park
    right_dt.move(127);
    left_dt.move(127);
    pros::delay(600);
    right_dt.move(-15);
    left_dt.move(-15);

    */