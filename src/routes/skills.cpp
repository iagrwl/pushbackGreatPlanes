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
    chassis.moveToPoint(-17.5, -32, 1200, {}, false);
    pros::delay(300);
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
    scoringRoller.move(-127);
    pros::delay(800);
    scoringRoller.move(127);
    chassis.turnToHeading(-180, 400, {}, false);
    
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
    chassis.moveToPoint(-61, -36, 1500, {.minSpeed = 40, .earlyExitRange = 5});
    frontIntake.move(0);
    chassis.moveToPoint(-60, 40, 2000);
    
    // allign to goal
    chassis.moveToPoint(-48, 40, 1000, {.forwards = false});
    chassis.moveToPoint(-48, 20, 2000, {.forwards = false});

    // score 1st time
    pros::delay(650);
    frontIntake.move(-80);
    middleRollers.move(-80);
    scoringRoller.move(-80);
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    pros::delay(1400);

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
    pros::delay(850);
    frontIntake.move(-80);
    middleRollers.move(-80);
    scoringRoller.move(-80);
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);  
    scoringGate.set_value(false);
    pros::delay(1400);
    loaderMech.set_value(false);

    // reset pose at the goal after scoring
    wallDistance(true,false);
    chassis.setPose(chassis.getPose().x,28, chassis.getPose().theta);

    // push for control zone
    chassis.moveToPoint(-48,34,2500,{.minSpeed=127});
    pros::delay(300);
    scoringGate.set_value(true);
    chassis.moveToPoint(-48,20,750,{.forwards=false,.maxSpeed=40}); 

    // allign to park zone
    chassis.moveToPoint(-48, 52, 2000, {.minSpeed = 40, .earlyExitRange = 5});
    chassis.moveToPoint(-20, 64, 2000, {.minSpeed = 40, .earlyExitRange = 5});
    chassis.turnToHeading(90, 300, {}, false);

    // extend loader before entering park zone
    loaderMech.set_value(true);
    // wait for loader to come down
    pros::delay(200);

    // enter park zone at full speed
    left_dt.move(127);
    right_dt.move(127);
    pros::delay(500);

    // retract loader partway through the motion for better intaking
    loaderMech.set_value(false);
    // keep going forward at full speed for a little longer
    pros::delay(250);

    // exit park zone slower to intake more blocks 
    // and to avoid climbing on top of blocks
    left_dt.move(50);
    right_dt.move(50);

    // wait until halfway between loader and park zone
    pros::delay(1700);
    left_dt.move(0);
    right_dt.move(0);

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
    chassis.turnToPoint(24,24,750);
    chassis.moveToPoint(18.5, 29, 1200, {}, false);
    pros::delay(300);
    frontIntake.move(10);
    
    // collect rest of cluster
    chassis.moveToPoint(25, 25, 1000);

    // allign to middle goal
    chassis.turnToPoint(11, 11, 750, {.forwards = false});  
    chassis.moveToPoint(11, 11, 1500, {.forwards = false});

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

    // allign to loader
    chassis.moveToPoint(46, 48, 1500);
    loaderMech.set_value(true);
    pros::delay(800);
    scoringRoller.move(127);
    middleRollers.move(127);
    frontIntake.move(127);
    chassis.turnToHeading(0, 400, {}, false);
    
    // reset pose to ensure we hit loader centered
    wallDistance(false, true);

    // collect loader
    chassis.moveToPoint(46, 72, 1500, {.maxSpeed = 70}, false);
    left_dt.move(-40);
    right_dt.move(-40);
    pros::delay(200);
    left_dt.move(90);
    right_dt.move(90);
    pros::delay(800);
    
    // go through alley
    chassis.moveToPoint(46, 48, 1200, {.forwards = false});
    //chassis.turnToPoint(-60, -30, 750);
    chassis.moveToPoint(61, 36, 1500, {.minSpeed = 40, .earlyExitRange = 5});
    pros::delay(200);
    loaderMech.set_value(false);
    
    chassis.moveToPoint(60, -40, 2000);
    frontIntake.move(0);

    // allign to goal
    chassis.moveToPoint(48, -40, 1000, {.forwards = false});
    chassis.moveToPoint(48, -20, 2000, {.forwards = false});

    // score 1st time
    pros::delay(650);
    frontIntake.move(-80);
    middleRollers.move(-80);
    scoringRoller.move(-80);
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(false);
    pros::delay(1400);

    // reset pose (x)
    wallDistance(false, false);

    // get loader
    loaderMech.set_value(true);
    chassis.moveToPoint(48, -72, 2000, {.maxSpeed = 70});
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
    pros::delay(1400);
    loaderMech.set_value(false);

    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);

    wallDistance(true,false);
    chassis.setPose(chassis.getPose().x,-28, chassis.getPose().theta);

    // push for control zone
    chassis.moveToPoint(48, -34,2500,{.minSpeed=127});
    pros::delay(300);
    scoringGate.set_value(true);
    chassis.moveToPoint(48, -20,750,{.forwards=false,.maxSpeed=40}); 
    
    // allign to park zone
    chassis.moveToPoint(48, -52, 2000, {.minSpeed = 40, .earlyExitRange = 5});
    chassis.moveToPoint(20, -64, 2000, {.minSpeed = 40, .earlyExitRange = 5});
    chassis.turnToHeading(-90, 300, {}, false);

    // park
    loaderMech.set_value(true);
    scoringGate.set_value(false);
    pros::delay(200);
    left_dt.move(127);
    right_dt.move(127);
    pros::delay(500);
    loaderMech.set_value(false);
    pros::delay(250);
    left_dt.move(0);
    right_dt.move(0);
}