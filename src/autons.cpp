#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "op_control.hpp"

void autonSkills() {
    chassis.setPose(0,0,-90);
    chassis.moveToPoint(-28,0,2000);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    chassis.turnToHeading(180,500);
    loaderMech.set_value(true);
    chassis.moveToPoint(-28,-20,3000);
}

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
    middleRollers.move(100);
    pros::delay(1500);
    chassis.moveToPoint(-34,-4,2500,{.maxSpeed=80},false);
    scoringRoller.move(127);
    chassis.turnToHeading(180,1000,{},false);
    
    loaderMech.set_value(true);
    chassis.moveToPoint(-33,-25,1200,{.maxSpeed= 70},false);
    chassis.moveToPoint(-33,20,2000,{.forwards = false, .maxSpeed= 70},false);
    scoringBar.set_value(true);
    pros::delay(500);
    scoringRoller.move(0);
    scoringBar.set_value(false);
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
void ihateprog(){
    //turn on intake
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);


    chassis.moveToPoint(0,31.5,1400,{.maxSpeed=85});
    chassis.turnToHeading(90,800,{.maxSpeed=70});
    loaderMech.set_value(true);

    chassis.moveToPoint(15,34.25,1300,{.maxSpeed=100},false);

    //chassis.moveToPoint(0,34.25,500,{.forwards=false,.maxSpeed=85});
    chassis.turnToHeading(90,500,{.maxSpeed=80});
    loaderMech.set_value(false);
    chassis.moveToPoint(-20,35,1000,{.forwards=false},false);
    scoringBar.set_value(true);
    pros::delay(1100);
    
    left_dt.move(127);
    right_dt.move(-127); 
    pros::delay(450);
    left_dt.move(0);
    right_dt.move(0); 
    scoringBar.set_value(false);
    chassis.turnToHeading(190,400);
    chassis.moveToPoint(-11,1,1200,{.maxSpeed=60});
    chassis.turnToHeading(180,500);
    chassis.moveToPoint(-10,-27,1200,{.maxSpeed=67});
    pros::delay(100);
    chassis.moveToPoint(-10,-34.5,1200,{.maxSpeed=50});

    chassis.turnToHeading(132.5,500);
    chassis.moveToPoint(-20,-24,1000,{.forwards=false},false);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    frontIntake.move(-127);
    pros::delay(100);
    middleRollers.move(127);   
    frontIntake.move(127); 
    pros::delay(450);
    middleRollers.move(-127);
    pros::delay(100);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(10);
    chassis.moveToPoint(17,-59,1200);
    chassis.turnToHeading(90,500);
    chassis.moveToPoint(-18,-59,1000,{.forwards=false});
    pros::delay(500);
    scoringBar.set_value(true);
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
    //chassis.moveToPoint(-10, 30, 2000,{.maxSpeed=60});
    chassis.moveToPoint(-8, 28, 2000,{.maxSpeed=70});
    pros::delay(600);
    loaderMech.set_value(true);
    pros::delay(600);
    chassis.turnToPoint(3,34,1500,{.forwards=false,.maxSpeed=70});
    loaderMech.set_value(false);
    chassis.moveToPoint(3.5,34,1000,{.forwards=false,.maxSpeed=80},false);
    pros::delay(400);
    scoringRoller.move(-50);
    middleRollers.move(-127);
    pros::delay(125);
    middleRollers.move(127);
    pros::delay(1000);
   //back out and turn towards 3 stack
    chassis.moveToPoint(-1, 25, 2000, {.minSpeed = 40, .earlyExitRange = 2});
    chassis.turnToHeading(91,400,{.maxSpeed = 90});
    chassis.moveToPoint(40, 27, 2300, {.maxSpeed = 80,.minSpeed = 40});
    scoringRoller.move(127);
    pros::delay(1300);
    loaderMech.set_value(true);
    pros::delay(800);
    chassis.turnToHeading(90,500);
    chassis.turnToHeading(-45,700);
    loaderMech.set_value(false);
    chassis.moveToPoint(25.2,40,1200);
    pros::delay(1100);
    frontIntake.move(-75);
    middleRollers.move(-127);
    scoringRoller.move(-127);


    // pros::delay(1000);
    // frontIntake.move(127);
    // middleRollers.move(127);
    // scoringRoller.move(127);
    // chassis.moveToPoint(27,20,1000,{.forwards=false,.earlyExitRange=10});
    // chassis.moveToPoint(34,-4,2500,{.maxSpeed=80},false);
    // chassis.turnToHeading(180,1000,{},false);
    // loaderMech.set_value(true);
    // chassis.moveToPoint(33,-25,4000,{.maxSpeed= 80},false);
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