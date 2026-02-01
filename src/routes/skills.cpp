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


// void autonSkills() {
//     scoringGate.set_value(true);
//     wingMech.set_value(true);
//     frontIntake.move(127);
//     middleRollers.move(127);
//     scoringRoller.move(127);

//     chassis.setPose(0,-47,180);
//     //go in
//     left_dt.move(50);
//     right_dt.move(50);
//     pros::delay(200);

//     left_dt.move(-20);
//     right_dt.move(-20);
//     pros::delay(1400);
//     //go in

//     left_dt.move(70);
//     right_dt.move(70);
//     pros::delay(500);
//     //intake second part
//     left_dt.move(0);
//     right_dt.move(0);
//     pros::delay(500);
    
//     //go out
//     left_dt.move(-40);
//     right_dt.move(-40);
//     pros::delay(400);

//     //go in
//     left_dt.move(70);
//     right_dt.move(70);
//     pros::delay(600);

//     left_dt.move(-20);
//     right_dt.move(-20);
//     pros::delay(600);
//     //800 before
//     //go out of park
//     left_dt.move(-80);
//     right_dt.move(-80);
//     pros::delay(700);
//     //go in slow to align
//     left_dt.move(30);
//     right_dt.move(30);
//     pros::delay(800);
//     //stop
//     left_dt.move(0);    
//     right_dt.move(0);
//     pros::delay(800);
//     wallDistance(true,true);
//     chassis.setPose(chassis.getPose().x,-47,180);

//     //line up for mid goal
//     chassis.moveToPoint(0,-28,1400,{.forwards=false});
//     chassis.turnToPoint(-22,-24,500,{.earlyExitRange=5});
//     chassis.moveToPose(-20,-22, -90,1500,{ .minSpeed=60, .earlyExitRange=7},false);
//     chassis.turnToPoint(0,0,700,{.forwards=false,.minSpeed=60,.earlyExitRange=4});
//     chassis.moveToPoint(-10,-10.5,3000,{.forwards = false, .maxSpeed=50});

//     //scoring mid goal
//     pros::delay(900);
//     scoreMidGoal();
//     scoreMidGoal();
//     pros::delay(500);

//     //move to 1st loader
//     loaderMech.set_value(true);
//     pros::delay(500);    

//     //chassis.moveToPose(-45,-65,180,4000,{.lead=0.5},false);
//     frontIntake.move(127);
//     middleRollers.move(127);
//     scoringRoller.move(127);
//     chassis.moveToPose(-47.5,-48,180,2400,{.lead=0.3},false);
//     wallDistance(true,true);
//     scoringGate.set_value(true);
//     chassis.moveToPoint(-47.5,-70,2500,{.maxSpeed=55});
//     pros::delay(900);
//     //collect from 1st loader
//     wallDistance(true,true);

//     //move to other side to score
//     chassis.moveToPoint(-48,-53,1000,{.forwards=false,.minSpeed=60,.earlyExitRange=5});
//     frontIntake.move(0);
//     loaderMech.set_value(false);
//     chassis.turnToPoint(-60,-37,1500,{.minSpeed=60,.earlyExitRange=5});
//     chassis.moveToPoint(-60,-37,1500,{.minSpeed=60,.earlyExitRange=5});
//     chassis.turnToHeading(0,1500,{.minSpeed=60,.earlyExitRange=5});
//     chassis.moveToPoint(-60,34,2000,{.minSpeed=60,.earlyExitRange=8});

//     //line up to score
//     chassis.turnToPoint(-50,24,1500,{.forwards=false,.minSpeed=60,.earlyExitRange=3});
//     frontIntake.move(127);
//     chassis.moveToPose(-51,18,0,2000,{.forwards=false,.lead=0.4,.minSpeed=60,.earlyExitRange=5});
//     pros::delay(300);
//     //chassis.moveToPoint(-50,22,400,{.forwards=false,.minSpeed=70,.earlyExitRange=4});
//     //chassis.turnToHeading(0,700,{.minSpeed=80,.earlyExitRange=4});
//     loaderMech.set_value(true);

//     //score first time in 1st long goal
//     frontIntake.move(-127);
//     middleRollers.move(-127);
//     scoringRoller.move(-127);
//     pros::delay(250);
//     scoringGate.set_value(false);
//     frontIntake.move(127);
//     middleRollers.move(127);
//     scoringRoller.move(127);
//     pros::delay(1500);
//     wallDistance(true,false);
//     chassis.setPose(chassis.getPose().x,28, chassis.getPose().theta);
//     pros::delay(1000);

//     //collect 2nd loader
//     chassis.moveToPoint(-47.5,70,2500,{.maxSpeed=60});
//     pros::delay(900);

//     //line up to score 2nd time in 1st long goal
//     scoringGate.set_value(true);
//     chassis.moveToPoint(-48.5,23,2500,{.forwards=false,.minSpeed=80});
//     pros::delay(300);
    
//     //score 2nd time in 1st long goal
//     loaderMech.set_value(false);
//     frontIntake.move(-127);
//     middleRollers.move(-127);
//     scoringRoller.move(-127);
//     pros::delay(200);
//     frontIntake.move(127);
//     middleRollers.move(127);
//     scoringRoller.move(127);
//     scoringGate.set_value(false);
//     pros::delay(2000);

//     //descore a lil
//     chassis.moveToPoint(-48,34,2500,{.minSpeed=127});
//     pros::delay(300);
//     scoringGate.set_value(true);
//     chassis.moveToPoint(-48,20,750,{.forwards=false,.maxSpeed=40});
//     //move to far park zone

//     chassis.moveToPose(-14,65,90,2500,{.minSpeed=70,.earlyExitRange=5});
//     pros::delay(1600);

//     //clear far park zone
//     loaderMech.set_value(true);
//     chassis.turnToHeading(83,500,{.minSpeed=50,.earlyExitRange=3},false);
//     scoringGate.set_value(true);
//     frontIntake.move(-127);
//     chassis.moveToPoint(12,66,1000,{.minSpeed=90},false);
//     frontIntake.move(127);
//     chassis.moveToPoint(24,66,1500,{.minSpeed=55});
//     pros::delay(500);
//     loaderMech.set_value(false);
//     /*
//     right_dt.move(110);
//     left_dt.move(107);
//     pros::delay(550);
//     loaderMech.set_value(false);
//     pros::delay(250);
//     right_dt.move(90);
//     left_dt.move(90);
//     pros::delay(500);
//     left_dt.move(0);
//     right_dt.move(0);
//     */
//     /*
//     chassis.turnToHeading(105,1500,{.minSpeed=60,.earlyExitRange=5},false);
//     right_dt.move(-35);
//     left_dt.move(-35);
//     pros::delay(800);
//     left_dt.move(0);
//     right_dt.move(0);
//     chassis.turnToHeading(90,500,{},false);
//     wallDistance(true,false);
//     chassis.setPose(18,chassis.getPose().y, chassis.getPose().theta);
//     */
//     pros::delay(400);
//     chassis.swingToHeading(0,lemlib::DriveSide::RIGHT,500,{},false);
//     right_dt.move(65);
//     left_dt.move(65);
//     pros::delay(800);
//     wallDistance(true,true);
//     /*

//     //align with 2nd long goal
//     chassis.moveToPose(48,48,135,1500,{.lead=-0.6,.minSpeed=70});
//     chassis.turnToHeading(0,500,{},false);
//     wallDistance(true,true);
//     */
//     chassis.turnToPoint(48,48,500,{.forwards=false,.minSpeed=70});
//     chassis.moveToPoint(48,48,1500,{.forwards=false,.minSpeed=70,.earlyExitRange=5});
//     chassis.moveToPoint(48,24,1500,{.forwards=false,.minSpeed=70});

//     //chassis.moveToPose(47.5,24, 0,3000,{.forwards=false,.minSpeed=70});

//     //score 1st time in 2nd long goal 
//     /* 
//     frontIntake.move(-127);
//     middleRollers.move(-127);
//     scoringRoller.move(-127);
//     pros::delay(200);
//     */
//     pros::delay(700);
//     scoringGate.set_value(false);
//     frontIntake.move(127);
//     middleRollers.move(127);
//     scoringRoller.move(127);
//     loaderMech.set_value(true);

//     //move to collect from 3rd loader
//     pros::delay(1000);
//     wallDistance(true,true);
//     chassis.setPose(chassis.getPose().x,28, chassis.getPose().theta);
//     scoringGate.set_value(true);
//     chassis.moveToPoint(46,70,3000,{.maxSpeed=70});
//     pros::delay(500);

//     //prep to score 2nd time in 2nd long goal
//     wingMech.set_value(true);
//     chassis.moveToPoint(48,24,3000,{.forwards=false,.maxSpeed=70});
//     pros::delay(1000);

//     //score 2nd time in 2nd long goal   
//     /*
//     frontIntake.move(-127);
//     middleRollers.move(-127);
//     scoringRoller.move(-127);
//     */
//     pros::delay(300);
//     scoringGate.set_value(false);
//     frontIntake.move(127);
//     middleRollers.move(127);
//     scoringRoller.move(127);
//     pros::delay(1800);
//     wallDistance(true,true);

//     chassis.setPose(48,28,0);
//     //prep to score 3rd time in 2nd long goal
//     loaderMech.set_value(false);
//     scoringGate.set_value(true);
//     chassis.moveToPoint(48,45,1500,{.minSpeed=60,.earlyExitRange=5});
//     chassis.turnToPoint(57,36,1500,{.minSpeed=60,.earlyExitRange=5});
//     chassis.moveToPoint(61,36,1500,{.minSpeed=60,.earlyExitRange=2});
//     chassis.turnToPoint(62,-32,700,{.minSpeed=60},false);
//     wallDistance(true,false);
//     chassis.moveToPoint(62,-32,3000,{.minSpeed=60,.earlyExitRange=8});
//     chassis.turnToHeading(180,750,{},false);
//     loaderMech.set_value(true);
//     wallDistance(true,false);

//     //intake last loader
//     loaderMech.set_value(true);
//     //chassis.moveToPose(50.5,-60,180,3000,{.minSpeed=60});
//     //chassis.moveToPose(50,-49,180,1000,{.minSpeed=60},false);
//     //chassis.turnToPoint(49,-48,1000,{.minSpeed=60,.earlyExitRange=5});
//     chassis.moveToPose(48,-50, 180, 2000,{.minSpeed=70,.earlyExitRange=5});
//     chassis.moveToPoint(48.5,-70, 2000,{.minSpeed=60});
//     pros::delay(700);

//     //move to score 3rd time in 2nd long goal
//     chassis.moveToPoint(48.5,-22,500,{.forwards=false,.minSpeed=80,.earlyExitRange=4},false);

//     //score 3rd time in 2nd long goal
//     /*
//     frontIntake.move(-127);
//     middleRollers.move(-127);
//     scoringRoller.move(-127);
//     pros::delay(300);
//     */
//     frontIntake.move(127);
//     middleRollers.move(127);
//     scoringRoller.move(127);
//     scoringGate.set_value(false);
//     loaderMech.set_value(false);
//     pros::delay(1600);

//     //line up to park
//     //was 18
//     chassis.moveToPose(2,-63,-90,2000,{.lead=0.5,.minSpeed=127,.earlyExitRange=4},false);

//     //park
//     /*
//     right_dt.move(127);
//     left_dt.move(127);
//     pros::delay(600);
//     right_dt.move(-15);
//     left_dt.move(-15);
//     */
// }

void autonSkills() {
    // set pose relative to center of field
    chassis.setPose(-6.75, -47, 0);

    // set wing up and scoring gate to keep blocks
    scoringGate.set_value(true);
    wingMech.set_value(true);

    // start intake
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);   

    // collect first red from cluster
    chassis.moveToPoint(-17.5, -34, 1200, {}, false);
    pros::delay(500);
    frontIntake.move(10);
    
    // collect rest of cluster
    chassis.moveToPoint(-25, -25, 1000);

    // allign to middle goal
    chassis.turnToPoint(-11, -13, 750, {.forwards = false});  
    chassis.moveToPoint(-11, -13, 1500, {.forwards = false});

    // score in mid goal
    frontIntake.move(127);
    pros::delay(700);
    scoringRoller.move(-50);
    frontIntake.move(-40);
    pros::delay(600);
    frontIntake.move(127);

    // allign to first loader
    chassis.moveToPoint(-46, -48, 1500);
    loaderMech.set_value(true);
    pros::delay(800);
    scoringRoller.move(127);
    chassis.turnToHeading(-180, 750, {}, false);
    
    wallDistance(false, true);

    // get first loader
    chassis.moveToPoint(-46, -72, 1500, {.maxSpeed = 70}, false);
    left_dt.move(-40);
    right_dt.move(-40);
    pros::delay(200);
    left_dt.move(90);
    right_dt.move(90);
    pros::delay(800);

    // go through alley
    chassis.moveToPoint(-46, -48, 1200, {.forwards = false});
    loaderMech.set_value(false);
    //chassis.turnToPoint(-60, -30, 750);
    chassis.moveToPoint(-61, -36, 1500, {.minSpeed = 40, .earlyExitRange = 5});
    frontIntake.move(0);
    //chassis.turnToPoint(-60, 40, 750);
    chassis.moveToPoint(-60, 40, 2000);
    
    // allign to goal
    //chassis.turnToHeading(-90, 750);
    chassis.moveToPoint(-48, 40, 1000, {.forwards = false});
    //chassis.turnToHeading(0, 750);
    chassis.moveToPoint(-48, 20, 2000, {.forwards = false});

    // score 1st time
    pros::delay(600);
    frontIntake.move(-80);
    middleRollers.move(-80);
    scoringRoller.move(-80);
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    pros::delay(1000);

    // reset pose (x)
    wallDistance(false, false);

    // get loader
    loaderMech.set_value(true);
    chassis.moveToPoint(-48, 72, 2000, {.maxSpeed = 70});
    pros::delay(500);
    scoringGate.set_value(true);
    pros::delay(1500);
    left_dt.move(-40);
    right_dt.move(-40);
    pros::delay(200);
    left_dt.move(90);
    right_dt.move(90);
    pros::delay(700);

    // score 2nd time
    chassis.moveToPoint(-48, 20, 2500, {.forwards = false});
    pros::delay(800);
    frontIntake.move(-80);
    middleRollers.move(-80);
    scoringRoller.move(-80);
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);  
    scoringGate.set_value(false);
    pros::delay(1200);

    // reset pose
    wallDistance(true,false);
    chassis.setPose(chassis.getPose().x,28, chassis.getPose().theta);

    // push for control zone
    chassis.moveToPoint(-48,34,2500,{.minSpeed=127});
    pros::delay(300);
    scoringGate.set_value(true);
    chassis.moveToPoint(-48,20,750,{.forwards=false,.maxSpeed=40});
    
}