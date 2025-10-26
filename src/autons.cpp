#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "op_control.hpp"

void autonSkills() {
    //SETUP
    chassis.setPose(0,0,90);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    //Q1
    chassis.moveToPoint(33.25,0,1400,{.maxSpeed=75});
    pros::delay(1400);
    chassis.turnToHeading(180,800,{.maxSpeed=70});
    loaderMech.set_value(true);
    chassis.moveToPoint(33.25,-15,3000,{.maxSpeed=100},false);
    pros::delay(1000);
    chassis.turnToHeading(180,500,{.maxSpeed=80});
    loaderMech.set_value(false);
    chassis.moveToPoint(33.25,30,2000,{.forwards=false,.maxSpeed=80});
    pros::delay(900);
    scoringBar.set_value(true);
    pros::delay(2500);
    //Q2
    chassis.moveToPoint(35,7,2000,{.maxSpeed=85});
    pros::delay(200);
    scoringBar.set_value(false);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(10);
    chassis.moveToPoint(-61,5,4000,{.maxSpeed=70});
    chassis.turnToHeading(180,500);
    loaderMech.set_value(true);
    chassis.moveToPoint(-61,-20, 3000,{.maxSpeed= 90},false);
    chassis.moveToPoint(-61,20,3000,{.forwards = false, .maxSpeed= 85});
    pros::delay(650);
    scoringBar.set_value(true);
    pros::delay(2000);
    chassis.moveToPoint(-61,6,1000,{.maxSpeed= 85});
    chassis.turnToPoint(-43,0,1500,{.minSpeed=80});
    scoringBar.set_value(false);
    //Q3
    chassis.moveToPoint(-43,0,1000,{.maxSpeed=70});
    chassis.turnToHeading(0,1500);
    loaderMech.set_value(false);
    chassis.moveToPoint(-43, 75, 3000,{});
    chassis.turnToPoint(-60,100,1500,{.maxSpeed=80});
    chassis.moveToPoint(-60,100,1500,{.maxSpeed=70});
    chassis.turnToHeading(0,1500);
    loaderMech.set_value(true);
    chassis.moveToPoint(-60,115, 4000,{.maxSpeed=70});
    chassis.moveToPoint(-60.5,75,3000,{.forwards=false,.maxSpeed=90});
    loaderMech.set_value(false);
    pros::delay(900);
    scoringRoller.move(90);
    scoringBar.set_value(true);
    pros::delay(4000);
    chassis.moveToPoint(-60.5,90,2000,{.maxSpeed=85});
    pros::delay(200);
    scoringBar.set_value(false);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(10);
    //Q4
    chassis.moveToPoint(34, 90,5000,{.maxSpeed=80});
    chassis.turnToHeading(0,1000);
    loaderMech.set_value(true);
    chassis.moveToPoint(34, 120,5000,{});
    chassis.moveToPoint(34.5, 75,5000,{.forwards=false,.maxSpeed=90});
    pros::delay(650);
    scoringBar.set_value(true);
    pros::delay(3000);
    //park
    chassis.moveToPoint(34.5,100,2000,{.maxSpeed=70});
    loaderMech.set_value(false);
    chassis.turnToPoint(17.5,100,1000);
    chassis.moveToPoint(17.5,100,1500);
    chassis.turnToHeading(180,1000);
    chassis.moveToPoint(17.5,-15,1500);
    chassis.turnToHeading(-90,1000);
    chassis.moveToPoint(-5,-15,1500);
    //chassis.moveToPose(-15,120,90,2000);
    /*
    chassis.turnToPoint(0,110,1000);
    loaderMech.set_value(false);
    chassis.moveToPoint(0,110,2000,{.maxSpeed=70});
    chassis.turnToHeading(90,1000);
    frontIntake.move(-127);
    chassis.moveToPoint(-15,120,2000,{.forwards = false, .minSpeed=100});
    */
    /*
    chassis.turnToHeading(280,400);
    chassis.moveToPoint(1,11,1200,{.maxSpeed=60});
    pros::delay(200);
    chassis.turnToHeading(270,500);
    chassis.moveToPoint(-27,10,1200,{.maxSpeed=67});
    pros::delay(200);
    pros::delay(900);
    loaderMech.set_value(true);
    chassis.moveToPoint(-34.5,10,1200,{.maxSpeed=50});
    pros::delay(400);
    loaderMech.set_value(false);
    chassis.turnToPoint(-21.5,23,1000,{.forwards=false},false);
    chassis.moveToPoint(-21.5,23,1300,{.forwards=false},false);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    frontIntake.move(-127);
    pros::delay(100);
    middleRollers.move(50);   
    frontIntake.move(127); 
    pros::delay(1500);
    middleRollers.move(-127);
    pros::delay(100);
    */

    /*
    chassis.turnToPoint(-43,0,1500,{.minSpeed=80});
    chassis.moveToPoint(-43,0,1500,{.maxSpeed=70});
    chassis.turnToHeading(0,1500);
    loaderMech.set_value(false);
    chassis.moveToPoint(-43, 75, 3000,{.maxSpeed=70});
    /*
    chassis.turnToPoint(-63, 82,1600);
    chassis.moveToPoint(-63, 82,1600);
    chassis.turnToHeading(180,500);
    loaderMech.set_value(true);
    chassis.moveToPoint(-63,105,3000,{.maxSpeed= 70},false);
    chassis.moveToPoint(-63,62,3000,{.forwards = false, .maxSpeed= 65});
    pros::delay(700);
    scoringBar.set_value(true);
    pros::delay(2000);
    scoringRoller.move(0);
    */

}

void Q1() {
    chassis.setPose(0,0,90);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    chassis.moveToPoint(31.5,0,1400,{.maxSpeed=85});
    chassis.turnToHeading(180,800,{.maxSpeed=70});
    loaderMech.set_value(true);
    chassis.moveToPoint(33.25,-15,4000,{.maxSpeed=90},false);
    chassis.turnToHeading(180,500,{.maxSpeed=80});
    loaderMech.set_value(false);
    chassis.moveToPoint(35,30,2000,{.forwards=false,.maxSpeed=80});
    pros::delay(900);
    scoringBar.set_value(true);
    pros::delay(2500);
    chassis.moveToPoint(35,7,2000,{.maxSpeed=85});
}
void Q2() {
    chassis.setPose(0,0,90);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    chassis.moveToPoint(35,7,2000,{.maxSpeed=85});
    pros::delay(200);
    scoringBar.set_value(false);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(10);
    chassis.moveToPoint(-61,7,5000,{.maxSpeed=80});
    chassis.turnToHeading(180,500);
    loaderMech.set_value(true);
    chassis.moveToPose(-61,-20, 180, 4000,{.maxSpeed= 90},false);
    chassis.moveToPoint(-61,20,3000,{.forwards = false, .maxSpeed= 85});
    pros::delay(650);
    scoringBar.set_value(true);
    pros::delay(2000);
    chassis.moveToPoint(-61,6,1000,{.maxSpeed= 85});
    chassis.turnToPoint(-43,0,1500,{.minSpeed=80});
    scoringBar.set_value(false);

}
void Q3() {
    //SETUP
    chassis.setPose(0,0,90);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    chassis.moveToPoint(-43,0,1000,{.maxSpeed=70});
    chassis.turnToHeading(0,1500);
    loaderMech.set_value(false);
    chassis.moveToPoint(-43, 75, 3000,{.maxSpeed=70});
    chassis.turnToPoint(-60,100,1500,{.maxSpeed=80});
    chassis.moveToPoint(-60,100,1500,{.maxSpeed=70});
    chassis.turnToHeading(0,1500);
    loaderMech.set_value(true);
    chassis.moveToPose(-60,115, 0, 4000,{.maxSpeed=70});
    chassis.moveToPoint(-60.5,75,3000,{.forwards=false,.maxSpeed=90});
    loaderMech.set_value(false);
    pros::delay(900);
    scoringRoller.move(90);
    scoringBar.set_value(true);
    pros::delay(4000);
    chassis.moveToPoint(-60.5,90,2000,{.maxSpeed=85});
    pros::delay(200);
    scoringBar.set_value(false);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(10);
}
void Q4() {
    //SETUP
    chassis.setPose(0,0,90);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);   
    chassis.moveToPoint(34, 90,5000,{.maxSpeed=80});
    chassis.turnToHeading(0,1000);
    loaderMech.set_value(true);
    chassis.moveToPose(34, 120, 0,5000,{.maxSpeed=90});
    chassis.moveToPoint(34.5, 75,5000,{.forwards=false,.maxSpeed=90});
    pros::delay(650);
    scoringBar.set_value(true);
    pros::delay(3000);
    //park
    chassis.moveToPoint(34.5,100,2000,{.maxSpeed=70});
    loaderMech.set_value(false);
    chassis.moveToPose(-15,120,90,2000);
}

void solo_awp(){
   //turn on intake 
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    //go perpendicular to loader
    chassis.moveToPoint(0,31.5,1450,{.maxSpeed=90});
    chassis.turnToHeading(90,825,{.maxSpeed=70});
    //drop loader mech
    loaderMech.set_value(true);
    //ram loader 
    chassis.moveToPoint(17,34,1000,{.maxSpeed=110},false);
    //fix lat alignment
    chassis.turnToHeading(90,200,{.maxSpeed=80});
    //go to long goal
    chassis.moveToPoint(-20,37,1000,{.forwards=false},false);
    //let balls score
    scoringBar.set_value(true);
    //retract loader mech
    loaderMech.set_value(false);
    //wait for blocks to be scored
    pros::delay(1000);
    //swing w 450ms turn
    left_dt.move(127);
    right_dt.move(-127); 
    pros::delay(450);
    left_dt.move(0);
    right_dt.move(0); 
    //correctional swing turn
    chassis.turnToHeading(195,250);//300
    //retract bar once swung
    scoringBar.set_value(false);
    //go to first 3 stack
    chassis.moveToPoint(-8,1,1200,{.maxSpeed=55});
    pros::delay(300);//100
    loaderMech.set_value(true);
    //correctional turn
    chassis.turnToHeading(195,300);
    loaderMech.set_value(false);
    //go to second 3 stack
    chassis.moveToPoint(-7,-29,1200,{.maxSpeed=80});
    chassis.moveToPoint(-5,-40,800,{.maxSpeed=60});//1200s
    pros::delay(150);
    loaderMech.set_value(true);
    //turn opposite of mid goal
    chassis.turnToHeading(132,500);
    //ram mid goal
    chassis.moveToPoint(-20.75,-23,1100,{.forwards=false},false);
    loaderMech.set_value(false);
    //reverse 300ms then push forward to prevent clogging
    middleRollers.move(-127);
    scoringRoller.move(-60);
    frontIntake.move(-127);
    pros::delay(300);
    middleRollers.move(100);   
    frontIntake.move(127); 
    pros::delay(600);
    //scoring recovery 
    middleRollers.move(-127);
    pros::delay(100);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(10);
    //moves parallel to long goal
    chassis.moveToPoint(17,-60,1300);
    //correctional parallel with goal
    chassis.turnToHeading(90,400);
    //rams goal
    chassis.moveToPoint(-18,-62,1000,{.forwards=false,.maxSpeed=100});
    //lets pid settle
    pros::delay(500);
    //lets blocks score
    scoringBar.set_value(true);
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
    chassis.turnToHeading(180,1000,{});
    loaderMech.set_value(true);
    chassis.moveToPoint(-33,-25,1200,{.maxSpeed= 70},false);
    chassis.moveToPoint(-33,20,2000,{.forwards = false, .maxSpeed= 70},false);
    scoringBar.set_value(true);
    pros::delay(500);
    scoringRoller.move(0);
    scoringBar.set_value(false);
    pros::delay(200);
    chassis.moveToPoint(-33,10,2000,{},false);
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

void one_goal_left() {
    // start intake
    frontIntake.move(127);
    colorSortRoller.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    wingMech.set_value(true);
    // collect 3 clump
    chassis.moveToPoint(0,4,500);
    chassis.turnToHeading(-17.5,1000);
    // go slow to prevent blocks from scattering
    chassis.moveToPoint(-7, 26, 3000, {.maxSpeed = 80, .minSpeed = 40});
    pros::delay(600);
    // extend loader to prevent blocks from scattering
    loaderMech.set_value(true);
    // collect under goal
    chassis.turnToPoint(-25.82, 38.44, 800);
    chassis.moveToPoint(-25.82, 38.44, 1200);
    pros::delay(100);
    loaderMech.set_value(false);
    chassis.turnToHeading(-72, 800, {});
    pros::delay(50);
    // extend loader to prevent blocks from scattering
    loaderMech.set_value(true);
    // go to goal
    chassis.moveToPoint(-16.27, 27.05, 1500, 
    {.forwards = false, .minSpeed = 30, .earlyExitRange = 10});
    chassis.turnToPoint(-31.21, -3.95, 800);
    chassis.moveToPoint(-32.21, -3.95, 1500);
    chassis.turnToPoint(-32.51, 20.44, 800, {.forwards = false});
    chassis.moveToPoint(-32.51, 20.44, 1500, {.forwards = false});
    pros::delay(700);
    // score first set of blocks
    scoringBar.set_value(true);
    pros::delay(1300);
    // get blocks from loader
    chassis.moveToPoint(-31.51, -16.91, 2000, {.maxSpeed = 80});
    pros::delay(200);
    scoringBar.set_value(false);
    //chassis.moveToPoint(-31.51, -16.41, 2000, {}, false);
    //pros::delay(100);
    chassis.moveToPoint(-32.51, 22.44, 1500, {.forwards = false});
    pros::delay(1000);
    // score last set of blocks
    scoringBar.set_value(true);
    pros::delay(750);
    chassis.moveToPoint(-31.51, 13.44, 1000, {});
    scoringBar.set_value(false);
    chassis.moveToPoint(-31.51, 30.44, 2000, {.forwards = false});
}

void one_goal_right() {
    frontIntake.move(127);
    colorSortRoller.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    wingMech.set_value(true);
    chassis.moveToPoint(0,4,500);
    chassis.turnToHeading(17.5,1000);
    chassis.moveToPoint(8, 26, 3000, {.maxSpeed = 80, .minSpeed = 40});
    pros::delay(600);
    loaderMech.set_value(true);
    chassis.turnToPoint(25.32, 39.94, 800);
    chassis.moveToPoint(26.32, 39.94, 1200);
    pros::delay(50);
    loaderMech.set_value(false);
    chassis.turnToHeading(72, 800, {});
    pros::delay(100);
    loaderMech.set_value(true);
    chassis.moveToPoint(14.27, 27.05, 1500, {.forwards = false/*.minSpeed = 30, .earlyExitRange = 10*/});
    chassis.turnToPoint(33.21, 3, 800);
    chassis.moveToPoint(33.21, 3, 1500);
    chassis.turnToPoint(33.51, 26.44, 800, {.forwards = false});
    chassis.moveToPoint(33.51, 26.44, 1500, {.forwards = false});
    //chassis.turnToHeading(180, 800);
    pros::delay(700);
    scoringBar.set_value(true);
    pros::delay(1300);
    chassis.moveToPoint(34.51, -12.41, 2000, {.maxSpeed = 100});
    pros::delay(200);
    scoringBar.set_value(false);
    //chassis.moveToPoint(34.51, -10.41, 2000, {.forwards = false}, false);
    //pros::delay(100);
    chassis.moveToPoint(35.51, 26.44, 1500, {.forwards = false});
    pros::delay(1000);
    scoringBar.set_value(true);
    pros::delay(600);
    chassis.moveToPoint(34.51, 13.44, 1000, {});
    scoringBar.set_value(false);
    chassis.moveToPoint(34.51, 30.44, 2000, {.forwards = false});
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