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
    pros::delay(250);
    // collect rest of cluster
    chassis.moveToPoint(-25, -25, 1000, {}, false);

    loaderMech.set_value(true);

    // allign to middle goal
    chassis.turnToPoint(-11, -13, 600, {.forwards = false});

    // start moving towards the mid goal
    chassis.moveToPoint(-11, -13, 1500, {.forwards = false});

    pros::delay(350);
    // reverse intake but keep scoring roller at 0 so first block just drops
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(0);
    pros::delay(350);

    // start scoring after 700ms while still moving towards the point
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(-35);
    pros::delay(600);

    // spit out any remaining blocks while moving towards the loader
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(-127);

    // allign to first loader
    chassis.moveToPoint(-46, -48, 1500);
    chassis.turnToHeading(-180, 400, {}, false);

    wallDistance(false, true);

    // stop spitting out blocks
    scoringRoller.move(127);

    // get first loader
    chassis.moveToPoint(-46, -72, 1500, {.maxSpeed = 70}, false);

    // shake to prevent jams
    left_dt.move(-40);
    right_dt.move(-40);
    pros::delay(200);
    left_dt.move(90);
    right_dt.move(90);
    pros::delay(800);

    // go through alley
    chassis.moveToPoint(-46, -48, 1200, {.forwards = false});

    chassis.moveToPoint(-61, -36, 1500, {.minSpeed = 40, .earlyExitRange = 5});
    loaderMech.set_value(false);
    frontIntake.move(0);

    chassis.moveToPoint(-60, 40, 2000);

    // allign to goal
    chassis.moveToPoint(-48, 40, 1000, {.forwards = false});
    chassis.moveToPoint(-48, 20, 2000, {.forwards = false});

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
    chassis.moveToPoint(-48, 72, 2000, {.maxSpeed = 70});
    pros::delay(500);
    scoringGate.set_value(true);
    pros::delay(1500);
    left_dt.move(-40);
    right_dt.move(-40);
    pros::delay(200);
    left_dt.move(90);
    right_dt.move(90);
    pros::delay(800);

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

    // reset pose at the goal after scoring
    wallDistance(true, false);
    chassis.setPose(chassis.getPose().x, 28, chassis.getPose().theta);

    // push for control zone
    chassis.moveToPoint(-48, 34, 2500, {.minSpeed=127});
    pros::delay(300);
    scoringGate.set_value(true);
    chassis.moveToPoint(-48, 20, 750, { .forwards=false, .maxSpeed=40 }); 

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

    wallDistance(false, false);
    chassis.setPose(chassis.getPose().x, 62, chassis.getPose().theta);

    // move to collect 1 red from cluster
    chassis.moveToPoint(12, 36, 1300);
    chassis.turnToPoint(24, 24, 600);
    chassis.moveToPoint(18.5, 29, 1200, {}, false);
    pros::delay(250);

    // collect rest of cluster
    chassis.moveToPoint(25, 25, 1000);

    loaderMech.set_value(true);

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


    // spit out any remaining blocks while moving towards the loader
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(-127);

    // allign to loader
    chassis.moveToPoint(46, 48, 1500);
    chassis.turnToHeading(0, 400, {}, false);

    wallDistance(false, true);
    scoringRoller.move(127);

    // collect loader
    chassis.moveToPoint(46, 72, 1500, {.maxSpeed = 70}, false);

    // shake to prevent jams
    left_dt.move(-40);
    right_dt.move(-40);
    pros::delay(200);
    left_dt.move(90);
    right_dt.move(90);
    pros::delay(800);

    // go through alley
    chassis.moveToPoint(46, 48, 1200, {.forwards = false});

    chassis.moveToPoint(61, 36, 1500, {.minSpeed = 40, .earlyExitRange = 5});
    loaderMech.set_value(false);
    frontIntake.move(0);

    chassis.moveToPoint(60, -40, 2000);

    // allign to goal
    chassis.moveToPoint(48, -40, 1000, {.forwards = false});
    chassis.moveToPoint(48, -20, 2000, {.forwards = false});

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
    chassis.moveToPoint(48, -72, 2000, {.maxSpeed = 70});
    pros::delay(500);
    scoringGate.set_value(true);
    pros::delay(1500);
    left_dt.move(-40);
    right_dt.move(-40);
    pros::delay(200);
    left_dt.move(90);
    right_dt.move(90);
    pros::delay(800);

    // score 2nd time
    chassis.moveToPoint(48, -20, 2500, {.forwards = false});
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
    chassis.setPose(chassis.getPose().x, -28, chassis.getPose().theta);

    // push for control zone
    chassis.moveToPoint(48, -34, 2500, {.minSpeed=127});
    pros::delay(300);
    scoringGate.set_value(true);
    chassis.moveToPoint(48, -20, 750, { .forwards=false, .maxSpeed=40 }); 

    // allign to park zone
    chassis.moveToPoint(48, -52, 2000, {.minSpeed = 40, .earlyExitRange = 5});
    chassis.moveToPoint(20, -64, 2000, {.minSpeed = 40, .earlyExitRange = 5});
    chassis.turnToHeading(-90, 300, {}, false);

    // extend loader before entering park zone
    loaderMech.set_value(true);
    scoringGate.set_value(false);
    pros::delay(200);

    // enter park zone at full speed
    left_dt.move(127);
    right_dt.move(127);
    pros::delay(500);

    // retract loader partway through the motion for better intaking
    loaderMech.set_value(false);
    // keep going forward at full speed for a little longer
    pros::delay(200);

    left_dt.move(0);
    right_dt.move(0);
}