#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "op_control.hpp"

void two_goal_LEFT() {
    //turn on intake
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    //getting off the park zone
    chassis.moveToPoint(0,4,500);
    //collecting 3 stack
    chassis.turnToHeading(-18,1000);
    //chassis.moveToPoint(-10, 30, 2000,{.maxSpeed=60});
    chassis.moveToPoint(-8, 28, 2000,{.maxSpeed=70});
    pros::delay(600);
    loaderMech.set_value(true);
    pros::delay(600);
    //chassis.turnToHeading(-135,1000,{.maxSpeed=70});
    chassis.turnToPoint(3,34,1500,{.forwards=false,.maxSpeed=70});
    loaderMech.set_value(false);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    chassis.moveToPoint(3,34,2500,{.forwards=false,.maxSpeed=80});
    pros::delay(400);
    middleRollers.move(127);
    pros::delay(700);
    chassis.moveToPoint(-34,-4,2500,{.maxSpeed=80},false);
    scoringRoller.move(0);
    chassis.turnToHeading(180,1000,{},false);
    loaderMech.set_value(true);
    chassis.moveToPoint(-33,-25,4000,{.maxSpeed= 80},false);
    chassis.moveToPoint(-33,20,1500,{.forwards = false, .maxSpeed= 70},false);
    scoringRoller.move(127);
    scoringBar.set_value(true);
    /*
    chassis.moveToPose(6,32,-134,2000,{.forwards=false,.maxSpeed = 70},false);
    //reverses intake

    pros::delay(150);
    middleRollers.move(127);
    //scoring delay
    pros::delay(2000);
    //back out and turn towards destin.
    frontIntake.move(127);
    middleRollers.move(127);   
    scoringRoller.move(127);

    chassis.moveToPoint(-32, 0, 2000,{});
    chassis.turnToHeading(180,700);
    loaderMech.set_value(true);
    chassis.moveToPoint(-32,-7,3000,{.maxSpeed=60});
    */
}

void solo_awp(){
    //turn on intake
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    //getting off the park zone
    chassis.moveToPoint(0,4,500);
    //collecting 3 stack
    chassis.turnToHeading(-18,1000);
    chassis.moveToPoint(-10, 30, 2000);
    pros::delay(500);
    loaderMech.set_value(true);
    pros::delay(300);
    chassis.turnToHeading(-135,1000);

    
    //low goal alignment
    chassis.turnToHeading(-135,1000);
    loaderMech.set_value(false);
    chassis.moveToPose(6,32,-134,2000,{.forwards=false,.maxSpeed = 70},false);
    //reverses intake
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(150);
    middleRollers.move(127);
    //scoring delay
    pros::delay(2000);
    //intake forward
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    //back out and turn towards destin.
    chassis.moveToPoint(-1, 23, 2000, {.minSpeed = 40, .earlyExitRange = 4});
    chassis.turnToHeading(92,400,{.maxSpeed = 90});
    chassis.moveToPose(44, 24,90, 2300, {.lead=0.2,.maxSpeed = 80,.minSpeed = 40});
    pros::delay(1250);
    loaderMech.set_value(true);
    pros::delay(800);
    chassis.turnToHeading(-45,700);
    loaderMech.set_value(false);
    chassis.moveToPose(26,39.5,318,1200);
    
    // //align with mid goal
    // chassis.moveToPose(30,39,130,3000,{.maxSpeed=65, .minSpeed = 40},false);
    // //reverse mid rollers for 100ms to give space for blocks to score
    // middleRollers.move(-127);
    // scoringRoller.move(-127);
    // pros::delay(150);
    // middleRollers.move(127);
    // pros::delay(2000);
    // //move to loader
    // scoringRoller.move(127);
    // chassis.moveToPoint(50,20,1000,{.maxSpeed=70, .minSpeed = 40});
    // chassis.turnToHeading(180,500);
    // //drive into loader
    // chassis.moveToPoint(50,-10,1300, {.maxSpeed=90, .minSpeed = 50},false);
    // pros::delay(3000);
    // //backout from loader
    // chassis.moveToPoint(50,0,500);
    // //start alignment for scoring
    // chassis.turnToHeading(180,500);
    // chassis.moveToPoint(50,20,1500,{.forwards = false ,.maxSpeed=65, .minSpeed = 40},false);
    // scoringBar.set_value(true);
    // scoringRoller.move(127);
    // pros::delay(2000);
    // //descore/controlzone
    // chassis.moveToPoint(50,12,750,{.maxSpeed=80, .minSpeed = 40});
    // chassis.moveToPoint(50,25,1500,{.forwards = false , .minSpeed = 80});
}

void one_goal() {
    frontIntake.move(127);
    colorSortRoller.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    chassis.moveToPoint(0,4,500);
    chassis.turnToHeading(-17.5,1000);
    chassis.moveToPoint(-7, 26, 3000, {.maxSpeed = 80, .minSpeed = 40});
    pros::delay(600);
    loaderMech.set_value(true);
    chassis.turnToPoint(-25.82, 38.44, 800);
    chassis.moveToPoint(-25.82, 38.44, 1200);
    pros::delay(200);
    loaderMech.set_value(false);
    chassis.turnToHeading(-72, 800, {});
    pros::delay(50);
    loaderMech.set_value(true);
    chassis.moveToPoint(-16.27, 27.05, 1500, {.forwards = false, .minSpeed = 30, .earlyExitRange = 10});
    chassis.turnToPoint(-31.21, -3.95, 800);
    chassis.moveToPoint(-32.21, -3.95, 1500);
    chassis.turnToPoint(-31.51, 20.44, 800, {.forwards = false});
    chassis.moveToPoint(-31.51, 20.44, 1500, {.forwards = false});
    pros::delay(700);
    scoringBar.set_value(true);
    pros::delay(1300);
    chassis.moveToPoint(-31.51, -17.41, 2000, {.minSpeed = 40});
    pros::delay(200);
    scoringBar.set_value(false);
    chassis.moveToPoint(-31.51, -16.41, 2000, {}, false);
    pros::delay(100);
    chassis.moveToPoint(-31.51, 22.44, 1500, {.forwards = false});
    pros::delay(1000);
    scoringBar.set_value(true);
    pros::delay(750);
    chassis.moveToPoint(-31.51, 13.44, 1000, {});
    scoringBar.set_value(false);
    chassis.moveToPoint(-31.51, 30.44, 2000, {.forwards = false});


}

void turnTesting(bool isCW) {

    const int SIZE = 6;
    int turns[SIZE] = {15, 30, 45, 60, 90, 120};
    int actualTurn[SIZE] = {};
    int currTurn;

    for (int i = 0; i < SIZE; i++) {
        isCW ? currTurn = turns[i] : currTurn = -turns[i];

        chassis.turnToHeading(currTurn,2000, {}, false);

        pros::delay(500);

        pros::lcd::print(i+2, "%d: %.2f", currTurn, chassis.getPose().theta);

        chassis.turnToHeading(0, 2000);
        
        

    }
}



void driveTesting(bool isForward) {

    const int SIZE = 3;
    int dist[SIZE] = {12, 24, 48};
    int actualDist[SIZE] = {};
    int currDist;

    for (int i = 0; i < SIZE; i++) {
        isForward ? currDist = dist[i] : currDist = -dist[i];

        chassis.moveToPoint(0, currDist,3000, {}, false);

        pros::delay(500);

        pros::lcd::print(i+4, "%d: %.2f", currDist, chassis.getPose().y);

        chassis.moveToPoint(0, 0, 3000, {.forwards = false});
        
        

    }
}