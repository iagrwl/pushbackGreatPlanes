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
    loaderMech.set_value(false);

    // reset pose

    // park cross
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);

    wallDistance(true,false);
    chassis.setPose(chassis.getPose().x,28, chassis.getPose().theta);

    // push for control zone
    chassis.moveToPoint(-48,34,2500,{.minSpeed=127});
    pros::delay(300);
    scoringGate.set_value(true);
    chassis.moveToPoint(-48,20,750,{.forwards=false,.maxSpeed=40}); 

    chassis.moveToPoint(-48, 52, 2000, {.minSpeed = 40, .earlyExitRange = 5});
    chassis.moveToPoint(-20, 64, 2000);
    chassis.turnToHeading(90, 750, {}, false);
    loaderMech.set_value(true);
    pros::delay(200);
    //chassis.moveToPoint(-22, 64, 1500, {.forwards = false, .minSpeed = 40});
    //chassis.moveToPoint(8, 64, 2500, {.minSpeed = 127}, false);
    left_dt.move(127);
    right_dt.move(127);
    pros::delay(500);
    loaderMech.set_value(false);
    pros::delay(250);
    left_dt.move(50);
    right_dt.move(50);
    pros::delay(1700);
    left_dt.move(0);
    right_dt.move(0);
    chassis.turnToHeading(-180, 750, {.minSpeed = 60, .earlyExitRange = 40}, false);
    left_dt.move(-127);
    right_dt.move(-127);
    pros::delay(700);
    left_dt.move(0);
    right_dt.move(0);

    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringGate.set_value(true);
    wingMech.set_value(true);

    chassis.setPose(30, 62, 180);

    wallDistance(false, false);
    
    chassis.moveToPoint(12, 36, 1500);
    chassis.turnToPoint(24,24,750);
    chassis.moveToPoint(18.5, 29, 1200, {}, false);
    pros::delay(500);
    frontIntake.move(10);
    
    // collect rest of cluster
    chassis.moveToPoint(25, 25, 1000);

    // allign to middle goal
    chassis.turnToPoint(11, 11, 750, {.forwards = false});  
    chassis.moveToPoint(11, 11, 1500, {.forwards = false});

    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(0);
    pros::delay(350);
    frontIntake.move(127);
    middleRollers.move(60);
    const int totalSteps = 10;   
    const int stepDelay = 100;     

    for (int i = 0; i <= totalSteps; i++) {
        double t = (double)i / totalSteps;  

        double speed = 45 - 25 * t * t;

        scoringRoller.move(-(int)speed);
        pros::delay(stepDelay);
    }

    chassis.moveToPoint(46, 48, 1500);
    loaderMech.set_value(true);
    pros::delay(800);
    scoringRoller.move(127);
    middleRollers.move(127);
    frontIntake.move(127);
    chassis.turnToHeading(0, 750, {}, false);
    
    wallDistance(false, true);

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
    
    //chassis.turnToPoint(-60, 40, 750);
    chassis.moveToPoint(60, -40, 2000);
    frontIntake.move(0);
    // allign to goal
    //chassis.turnToHeading(-90, 750);
    chassis.moveToPoint(48, -40, 1000, {.forwards = false});
    //chassis.turnToHeading(0, 750);
    chassis.moveToPoint(48, -20, 2000, {.forwards = false});

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
    
    chassis.moveToPoint(48, -52, 2000, {.minSpeed = 40, .earlyExitRange = 5});
    chassis.moveToPoint(20, -64, 2000);
    chassis.turnToHeading(-90, 750, {}, false);
    loaderMech.set_value(true);
    scoringGate.set_value(false);
    pros::delay(200);
    //chassis.moveToPoint(-22, 64, 1500, {.forwards = false, .minSpeed = 40});
    //chassis.moveToPoint(8, 64, 2500, {.minSpeed = 127}, false);
    left_dt.move(127);
    right_dt.move(127);
    pros::delay(500);
    loaderMech.set_value(false);
    pros::delay(250);
    left_dt.move(0);
    right_dt.move(0);
}