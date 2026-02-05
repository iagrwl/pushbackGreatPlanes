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
    chassis.moveToPoint(-9.5, -9.5, 3000,{.forwards = false, .maxSpeed = 50});

    pros::delay(1000);
    scoreMidGoal();
    pros::delay(2700);

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
    left_dt.move(-40);
    right_dt.move(-40);
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
    scoringGate.set_value(true);
    // =========================
    // SECOND LOADER + SCORE
    // =========================
    chassis.moveToPoint(-48, 70, 1800,
        {.maxSpeed = 75}, false);
    

    left_dt.move(-40);
    right_dt.move(-40);
    pros::delay(200);

    left_dt.move(90);
    right_dt.move(90);
    pros::delay(800);
    pros::delay(500);

    chassis.moveToPoint(-48.5, 23, 2500,
        {.forwards = false, .minSpeed = 80});

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
    left_dt.move(-40);
    right_dt.move(-40);
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
    scoringGate.set_value(true);
    //chassis.moveToPoint(45.75,70,3000,{.maxSpeed=70});
    chassis.moveToPoint(48.5,-70,1500,{.maxSpeed=70},false);
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
    left_dt.move(-40);
    right_dt.move(-40);

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
    chassis.moveToPose(-8,-67,-90,2500,{.lead=0.5,.minSpeed=127,.earlyExitRange=4},false);
    left_dt.move(-20);
    right_dt.move(-20);


    //park

}
