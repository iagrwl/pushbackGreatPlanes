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
    pros::delay(1300);

    left_dt.move(50);
    right_dt.move(50);
    pros::delay(300);

    left_dt.move(-10);
    right_dt.move(-10);
    pros::delay(1000);

    // Exit starting area
    left_dt.move(-90);
    right_dt.move(-90);
    pros::delay(600);

    // Slow forward alignment
    left_dt.move(25);
    right_dt.move(25);
    pros::delay(800);

    left_dt.move(0);
    right_dt.move(0);
    pros::delay(200);

    // Wall reset
    wallDistance(true, true);
    chassis.setPose(chassis.getPose().x, -47, 180);

    chassis.moveToPoint(0, -40, 1400, {.forwards = false});

    chassis.turnToPoint(22, -26, 500, {.earlyExitRange = 5});
    chassis.moveToPoint(22, -26, 1500,{.maxSpeed = 75},false);
    frontIntake.move(-60);
    pros::delay(100);
    frontIntake.move(0);
    middleRollers.move(0);
    scoringRoller.move(127);
    pistake.set_value(true);

    chassis.turnToPoint(0, 0, 800,{.maxSpeed = 60,});
    chassis.moveToPoint(0, 0, 900,{.maxSpeed = 50},false);
    chassis.moveToPoint(12, -12, 500,{.forwards =false,.maxSpeed = 40},false);
    frontIntake.move(-70);
    middleRollers.move(-127);
    scoringRoller.move(127);
    pros::delay(1200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(200);
    frontIntake.move(-70);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(1300);

    chassis.moveToPoint(24, -24, 1000, {.forwards = false,.maxSpeed = 60});
    
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
    pros::delay(1300);
    left_dt.move(0);
    right_dt.move(0);


    // go through alley
    chassis.moveToPoint(-48, -48, 1200, {.forwards = false});

    chassis.moveToPoint(-59, -36, 1500, {.minSpeed = 40, .earlyExitRange = 5});
    loaderMech.set_value(false);
    frontIntake.move(0);

    chassis.moveToPoint(-59, 42, 2000);

    // allign to goal
    chassis.moveToPoint(-49, 42, 1000, {.forwards = false});
    chassis.moveToPoint(-49, 20, 2000, {.forwards = false});

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
    pros::delay(1300);
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
    chassis.turnToHeading(45, 500, { .minSpeed=60, .earlyExitRange=5 });
    scoringGate.set_value(true);
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
    pros::delay(1300);

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
    chassis.moveToPose(-6, -66, -90, 5000, { .lead=0.2,.minSpeed=127 });

}

void HARDSkills() {
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
    /*
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
    pros::delay(550);

    // Slow forward alignment
    left_dt.move(20);
    right_dt.move(20);
    pros::delay(800);

    left_dt.move(0);
    right_dt.move(0);
    pros::delay(200);

    // Wall reset
    wallDistance(true, true);
    chassis.setPose(chassis.getPose().x, -47, 180);

    chassis.moveToPoint(0, -40, 1400, {.forwards = false});

    chassis.turnToPoint(24, -24, 500, {.earlyExitRange = 5});
    chassis.moveToPoint(24, -24, 1500,{.maxSpeed = 75},false);
    frontIntake.move(-60);
    pros::delay(100);
    frontIntake.move(0);
    middleRollers.move(0);
    scoringRoller.move(127);
    pistake.set_value(true);

    chassis.turnToPoint(0, 0, 800,{.maxSpeed = 60,});
    chassis.moveToPoint(0, 0, 900,{.maxSpeed = 50},false);

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
    frontIntake.move(-127);
    pros::delay(250);
    left_dt.move(0);    
    right_dt.move(0);

    chassis.moveToPoint(24, -24, 1000, {.forwards = false});

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
    pros::delay(1300);
    left_dt.move(0);
    right_dt.move(0);


    // go through alley
    chassis.moveToPoint(-48, -48, 1200, {.forwards = false});

    chassis.moveToPoint(-59, -36, 1500, {.minSpeed = 40, .earlyExitRange = 5});
    loaderMech.set_value(false);
    frontIntake.move(0);

    chassis.moveToPoint(-59, 42, 2000);

    // allign to goal
    chassis.moveToPoint(-49, 42, 1000, {.forwards = false});
    chassis.moveToPoint(-49, 20, 2000, {.forwards = false});

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
    pros::delay(1300);
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
    */
    chassis.setPose(-48, 28, 0);

    chassis.moveToPoint(-48, 48, 3000, { .minSpeed=40, .earlyExitRange=5});
    scoringGate.set_value(true);
    chassis.turnToHeading(45, 500, { .minSpeed=60, .earlyExitRange=5 });
    chassis.moveToPose(-12, 66, 85, 2000, { .lead=0.2,.maxSpeed=80 });
    chassis.moveToPoint(-2, 66, 2000, { .maxSpeed=80 });
    chassis.moveToPoint(24, 66, 3000, { .maxSpeed=70 });
    pros::delay(700);
    loaderMech.set_value(true);

    // reset pose against the wall
    chassis.turnToHeading(-180, 750, {.minSpeed = 60, .earlyExitRange = 40}, false);
    left_dt.move(-127);
    right_dt.move(-127);
    pros::delay(500);
    left_dt.move(0);
    right_dt.move(0);
    // chassis.setPose(30, 62, 180);
    wallDistance(false, false);
    
    // move to collect 1 red from cluster
    chassis.moveToPoint(12, 36, 1500);
    loaderMech.set_value(false);
    chassis.turnToPoint(24,24,750);
    chassis.moveToPose(24, 24, 135, 1500, {.maxSpeed = 60});
    //chassis.moveToPoint(18.5, 29, 1200, {}, false);
    pros::delay(300);
    frontIntake.move(10);
    
    // collect rest of cluster

    // allign to middle goal
    chassis.turnToPoint(0, 0, 750, {.forwards = false});  
    chassis.moveToPoint(0, 0, 1500, {.forwards = false});

    // reverse intake but keep scoring roller at 0 so first block just drops
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(0);
    pros::delay(350);
    frontIntake.move(127);
    middleRollers.move(60);

    // bhargav's curve
    const int totalSteps = 10;   
    const int stepDelay = 100;     

    for (int i = 0; i <= totalSteps; i++) {
        double t = (double)i / totalSteps;  

        double speed = 45 - 25 * t * t;

        scoringRoller.move(-(int)speed);
        pros::delay(stepDelay);
    }
    
    // wait 1 sec to finish scoring blocks
    pros::delay(1000);


    /*
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
    pros::delay(1300);

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
    chassis.moveToPose(-6, -66, -90, 5000, { .lead=0.2,.minSpeed=127 });
    */
}