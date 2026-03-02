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
    // =========================
    // INITIAL SETUP
    // =========================
    scoringGate.set_value(true);
    wingMech.set_value(true);

    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    chassis.setPose(0, 0, 180);
    right_dt.get_temperature();
    left_dt.get_temperature();
    // =========================
    // CLEAR STARTING ZONE
    // =========================
    left_dt.move(50);
    right_dt.move(50);
    pros::delay(200);

    left_dt.move(-20);
    right_dt.move(-20);
    pros::delay(1200);

    left_dt.move(70);
    right_dt.move(70);
    pros::delay(500);

    left_dt.move(0);
    right_dt.move(0);
    pros::delay(1000);

    // Exit starting area
    left_dt.move(-90);
    right_dt.move(-90);
    pros::delay(600);

    // Slow forward alignment
    left_dt.move(20);
    right_dt.move(20);
    pros::delay(700);

    left_dt.move(0);
    right_dt.move(0);
    pros::delay(200);

    // Wall reset
    wallDistance(true, true);
    chassis.setPose(chassis.getPose().x, -47, 180);

    chassis.moveToPoint(0, -40, 1400, {.forwards = false});

    chassis.turnToPoint(24, -24, 500, {.earlyExitRange = 5});
    chassis.moveToPoint(24, -24, 1000, {.maxSpeed = 80},false);
    frontIntake.move(-60);
    pros::delay(100);
    frontIntake.move(0);
    middleRollers.move(0);
    scoringRoller.move(127);
    pistake.set_value(true);

    chassis.turnToPoint(0, 0, 800,{.maxSpeed = 60,});
    chassis.moveToPoint(0, 0, 900,{.maxSpeed = 50},false);
    left_dt.move(-20);
    right_dt.move(-20);
    pros::delay(170);
    left_dt.move(0);    
    right_dt.move(0);

    pros::delay(800);
    frontIntake.move(-100);
    middleRollers.move(-127);
    scoringRoller.move(127);
    pros::delay(500);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(200);
    frontIntake.move(-100);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(1800);
    left_dt.move(30);
    right_dt.move(30);
    pros::delay(200);
    left_dt.move(0);    
    right_dt.move(0);

    chassis.moveToPoint(24, -24, 1000, {.forwards = false});
    frontIntake.move(0);
    middleRollers.move(0);
    scoringRoller.move(0);

    chassis.turnToPoint(-47.5, -48, 800,{.minSpeed = 60,.earlyExitRange = 5});
    chassis.moveToPoint(-47.5, -48, 2400, {.maxSpeed = 80});
    chassis.turnToHeading(180, 500, {.maxSpeed = 80},false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pistake.set_value(false);
    
    loaderMech.set_value(true);
    scoringGate.set_value(true);

    wallDistance(true, true);
    chassis.moveToPoint(-48, -72, 1500, {.maxSpeed = 50}, false);
    left_dt.move(40);
    right_dt.move(40);
    pros::delay(1400);
    left_dt.move(0);
    right_dt.move(0);


    // go through alley
    chassis.moveToPoint(-48, -48, 1200, {.forwards = false});

    chassis.moveToPoint(-59, -36, 1500, {.minSpeed = 40, .earlyExitRange = 5});
    loaderMech.set_value(false);
    frontIntake.move(0);

    chassis.moveToPoint(-59, 42, 2000);

    // allign to goal
    chassis.moveToPoint(-50, 42, 1000, {.forwards = false});
    chassis.moveToPoint(-50, 20, 2000, {.forwards = false});

    // score 1st time
    // start scoring after 600ms while still moving towards the point
    pros::delay(600);
    loaderMech.set_value(true);
    frontIntake.move(-80);
    pros::delay(50);
    middleRollers.move(-80);
    scoringRoller.move(-80);
    pros::delay(150);
    scoringGate.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(1200);

    // reset pose (x)
    wallDistance(false, false);

    // get loader
    chassis.moveToPoint(-47.5, 72, 2000, {.maxSpeed = 50},false);
    scoringGate.set_value(true);
    left_dt.move(40);
    right_dt.move(40);
    pros::delay(1400);
    left_dt.move(0);
    right_dt.move(0);

    // score 2nd time
    chassis.moveToPoint(-48, 20, 2500, {.forwards = false});
    pros::delay(850);
    frontIntake.move(-80);
    pros::delay(50);
    middleRollers.move(-80);
    scoringRoller.move(-80);
    pros::delay(150);
    scoringGate.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(1200);
    loaderMech.set_value(false);
    wallDistance(true, false);
    chassis.setPose(chassis.getPose().x, 28, chassis.getPose().theta);



    chassis.moveToPoint(-48, 48, 3000, { .minSpeed=40, .earlyExitRange=5});
    scoringGate.set_value(true);
    chassis.turnToHeading(45, 500, { .minSpeed=60, .earlyExitRange=5 });
    chassis.moveToPose(-12, 66, 85, 2000, { .lead=0.2,.maxSpeed=80 });
    chassis.moveToPoint(-2, 66, 2000, { .maxSpeed=80 });
    chassis.moveToPoint(24, 66, 3000, { .maxSpeed=70 });
    pros::delay(700);
    loaderMech.set_value(true);

    chassis.moveToPoint(48.5, 48, 1200, { .maxSpeed=80 });
    chassis.turnToHeading(0, 500, { .minSpeed=60, .earlyExitRange=5 });
    chassis.moveToPoint(48.5, 0, 2000, { .forwards=false, .maxSpeed=80 });;

    pros::delay(700);
    left_dt.move(-50);
    right_dt.move(-60);
    loaderMech.set_value(true);
    //move to collect from 3rd loader

    scoringGate.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(1600);
    left_dt.move(0);
    right_dt.move(0);
    wallDistance(true,true);
    chassis.setPose(chassis.getPose().x, 28, chassis.getPose().theta);

    // collect loader
    chassis.moveToPoint(47, 72, 1500, {.maxSpeed = 60}, false);
    left_dt.move(40); 
    right_dt.move(40); 
    scoringGate.set_value(true);
    pros::delay(1400);

    chassis.moveToPoint(48.5, 0, 2000, { .forwards=false, .maxSpeed=80});

    pros::delay(850);
    left_dt.move(-50);
    right_dt.move(-60);
    loaderMech.set_value(true);
    //move to collect from 3rd loader
    //pros::delay(1000);

    scoringGate.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(1800);
    left_dt.move(0);
    right_dt.move(0);
    wallDistance(true,true);
    chassis.setPose(chassis.getPose().x, 28, chassis.getPose().theta);

    // go through alley
    chassis.moveToPoint(46, 48, 1200, {});
    //chassis.turnToPoint(-60, -30, 750);
    chassis.moveToPoint(61, 36, 1500, {.minSpeed = 40, .earlyExitRange = 5});
    pros::delay(200);
    loaderMech.set_value(false);
    
    chassis.moveToPoint(60, -48, 2000);

    // allign to goal
    chassis.moveToPoint(48, -44, 1000, {.forwards = false});
    chassis.turnToHeading(180, 500, {.maxSpeed = 80},false);
    wallDistance(false, false);

    // get loader
    loaderMech.set_value(true);
    scoringGate.set_value(true);
    chassis.moveToPoint(48, -72, 2000, {.maxSpeed = 70});
    left_dt.move(40); 
    right_dt.move(40); 
    pros::delay(1800);

    // score 2nd time
    chassis.moveToPoint(48, -20, 2500, {.forwards = false});
    pros::delay(850);
    frontIntake.move(-80);
    middleRollers.move(-80);
    scoringRoller.move(-80);
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);  
    scoringGate.set_value(false);
    pros::delay(1600);
    loaderMech.set_value(false);

    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);

    wallDistance(true,false);
    chassis.setPose(chassis.getPose().x,-28, chassis.getPose().theta);
    
    // allign to park zone
    chassis.moveToPoint(48, -48, 2000, {.minSpeed = 40, .earlyExitRange = 5});
    chassis.turnToHeading(225, 500, { .minSpeed=60, .earlyExitRange=5 });
    chassis.moveToPose(-4, -66, -90, 3000, { .lead=0.2,.minSpeed=80 });
    
}

/*
void autonSkills() {
    
    // =========================
    // INITIAL SETUP
    // =========================
    scoringGate.set_value(true);
    wingMech.set_value(true);

    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    chassis.setPose(0, 0, 180);
    right_dt.get_temperature();
    left_dt.get_temperature();

    // =========================
    // CLEAR STARTING ZONE
    // =========================
    left_dt.move(50);
    right_dt.move(50);
    pros::delay(200);

    left_dt.move(-20);
    right_dt.move(-20);
    pros::delay(1400);

    left_dt.move(70);
    right_dt.move(70);
    pros::delay(500);

    left_dt.move(0);
    right_dt.move(0);
    pros::delay(500);

    // Back out slightly
    left_dt.move(-40);
    right_dt.move(-40);
    pros::delay(400);

    // Re-enter to finish intake
    left_dt.move(70);
    right_dt.move(70);
    pros::delay(600);

    left_dt.move(-20);
    right_dt.move(-20);
    pros::delay(600);

    // Exit starting area
    left_dt.move(-80);
    right_dt.move(-80);
    pros::delay(700);

    // Slow forward alignment
    left_dt.move(30);
    right_dt.move(30);
    pros::delay(800);

    left_dt.move(0);
    right_dt.move(0);
    pros::delay(800);

    // Wall reset
    wallDistance(true, true);
    chassis.setPose(chassis.getPose().x, -47, 180);

    // =========================
    // MID GOAL SCORE
    // =========================
    chassis.moveToPoint(0, -28, 1400, {.forwards = false});

    chassis.turnToPoint(-22, -24, 500, {.earlyExitRange = 5});
    chassis.moveToPose(-20, -22, -90, 1500, {.minSpeed = 60, .earlyExitRange = 7}, false);

    chassis.turnToPoint(0, 0, 700,{.forwards = false, .minSpeed = 60, .earlyExitRange = 4});
    chassis.moveToPoint(-9.75, -9.75, 3000,{.forwards = false, .maxSpeed = 50});

    pros::delay(1000);
    scoreMidGoal();
    pros::delay(2000);

    // =========================
    // FIRST LOADER COLLECTION
    // =========================
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);

    chassis.moveToPose(-47.5, -48, 180, 2400,
        {.lead = 0.3}, false);

    loaderMech.set_value(true);
    scoringGate.set_value(true);

    wallDistance(true, true);

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
    chassis.moveToPoint(-60, -36, 1500, {.minSpeed = 40, .earlyExitRange = 5});
    frontIntake.move(0);

    chassis.moveToPoint(-60, 42, 3500, {.maxSpeed = 80, .minSpeed=40, .earlyExitRange = 5});

    //chassis.turnToPoint(-51.5, 24, 1500,{.forwards = false, .minSpeed = 60, .earlyExitRange = 3});

    chassis.moveToPose(-51.5, 18, 0, 2000,
        {.forwards = false, .lead = 0.5, .minSpeed = 60, .earlyExitRange = 5}, false);
    left_dt.move(-50);
    right_dt.move(-60);
    loaderMech.set_value(true);

    pros::delay(250);

    scoringGate.set_value(false);

    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(1500);

    wallDistance(true, false);
    chassis.setPose(chassis.getPose().x, 28, chassis.getPose().theta);
    pros::delay(1000);
    // =========================
    // SECOND LOADER + SCORE
    // =========================
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


    chassis.moveToPose(-48, 23, 0, 2500,
        {.forwards = false, .minSpeed = 60});

    loaderMech.set_value(false);
    pros::delay(900);

    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);

    scoringGate.set_value(false);
    pros::delay(2000);

    // =========================
    // DESCORING ADJUSTMENT
    // =========================
    chassis.moveToPoint(-48, 34, 2500, {.minSpeed = 127});
    pros::delay(300);

    scoringGate.set_value(true);
    chassis.moveToPoint(-48, 20, 750,
        {.forwards = false, .maxSpeed = 40});
    chassis.moveToPoint(-48, 40, 3000, {.maxSpeed=60, .minSpeed=40, .earlyExitRange=5});
    chassis.turnToHeading(90, 500, {.minSpeed=60, .earlyExitRange=5});
    chassis.moveToPoint(47, 40, 3000, {.maxSpeed=90});
    chassis.turnToHeading(0, 700, {}, false);

    loaderMech.set_value(true); // Prep loader for intake
    wallDistance(true, true);

    chassis.moveToPoint(46, 72, 1800, {.maxSpeed=70}, false); // Collect second loader
    left_dt.move(-40); right_dt.move(-40); pros::delay(200);
    left_dt.move(90); right_dt.move(90); pros::delay(800);

    chassis.moveToPoint(48,53,700,{.forwards=false,.minSpeed=60,.earlyExitRange=5});
    frontIntake.move(127);
    chassis.turnToPoint(60,37,1500,{.minSpeed=60,.earlyExitRange=5});
    pros::delay(500);
    loaderMech.set_value(false);
    chassis.moveToPoint(60,37,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.turnToHeading(180,1500,{.minSpeed=60,.earlyExitRange=5});
    chassis.moveToPoint(60,-39,2300,{.minSpeed=60,.earlyExitRange=8});

    //line up to score
    chassis.turnToPoint(51.5,-24,1500,{.forwards=false,.minSpeed=60,.earlyExitRange=3});
    frontIntake.move(127);
    chassis.moveToPose(51.5,-18,180,2000,{.forwards=false,.lead=0.6,.minSpeed=60,.earlyExitRange=5},false);
    left_dt.move(-50);
    right_dt.move(-60);
    loaderMech.set_value(true);
    //move to collect from 3rd loader
    //pros::delay(1000);
    wallDistance(true,false);

    pros::delay(300);
    scoringGate.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(2200);
    left_dt.move(0);
    right_dt.move(0);

    //chassis.setPose(chassis.getPose().x,28, chassis.getPose().theta);
    //chassis.moveToPoint(45.75,70,3000,{.maxSpeed=70});
    chassis.moveToPoint(48.5,-70,2000,{.maxSpeed=70});
    pros::delay(500);
    scoringGate.set_value(true);
    pros::delay(1500);
    left_dt.move(-40);
    right_dt.move(-40);
    pros::delay(200);
    left_dt.move(90);
    right_dt.move(90);
    pros::delay(800);
    pros::delay(500);

    //prep to score 2nd time in 2nd long goal
    wingMech.set_value(true);


    chassis.moveToPoint(48,-22,2200,{.forwards=false,.minSpeed=80,.earlyExitRange=4},false);
    left_dt.move(-50);
    right_dt.move(-60);

    //score 3rd time in 2nd long goal
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    loaderMech.set_value(false);
    pros::delay(1600);
    left_dt.move(0);
    right_dt.move(0);


    //chassis.moveToPoint(48,-34,2500,{.minSpeed=127});
    //pros::delay(300);
    //chassis.moveToPoint(48,-20,1000,{.forwards=false,.maxSpeed=40});
    //line up to park
    //was 18
    chassis.moveToPose(-8,-67,-90,2700,{.lead=0.5,.minSpeed=127,.earlyExitRange=4},false);
    left_dt.move(-30);
    right_dt.move(-30);


    //park
    
}
*/