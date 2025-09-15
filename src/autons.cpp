#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "op_control.hpp"

void two_goal_LEFT() {
    chassis.setPose(0,0,30);
    
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
    chassis.moveToPoint(-9, 25, 2000);
    pros::delay(500);
    loaderMech.set_value(true);
    pros::delay(300);
    chassis.moveToPoint(-8,25, 1000,{.forwards = false},false);
    //low goal alignment
    chassis.turnToHeading(46,1000);
    loaderMech.set_value(false);
    chassis.moveToPose(4,36,45,1500,{.lead=-20,.maxSpeed = 60},false);
    //reverses intake
    frontIntake.move(-80);
    middleRollers.move(-127);   
    scoringRoller.move(-127);
    //scoring delay
    pros::delay(1400);
    //intake forward
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    // //moving to other side
    // chassis.moveToPoint(-7, 32, 3000, {.forwards = false , .minSpeed = 40});
    // chassis.turnToHeading(90,1000);
    // //collect 3 stack
    // chassis.moveToPose(38,32,90,2000,{.minSpeed=50});
    // pros::delay(1200);
    // loaderMech.set_value(true);
    // chassis.turnToHeading(135,1500);
    // pros::delay(500);
    // loaderMech.set_value(false);
    // //align with mid goal
    // chassis.moveToPose(28,41,130,3000,{.forwards = false ,.maxSpeed=65, .minSpeed = 40},false);
    // //reverse mid rollers for 100ms to give space for blocks to score
    // middleRollers.move(-127);
    // scoringRoller.move(-127);
    // pros::delay(150);
    // middleRollers.move(127);
    // pros::delay(2000);
    // chassis.moveToPoint(30,30,3000,{.maxSpeed=70, .minSpeed = 40},false);
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