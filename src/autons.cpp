#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "op_control.hpp"

void autonSkills() {
 //turn on intake
    chassis.setPose(0,0,90);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);


    chassis.moveToPoint(31.5,0,1400,{.maxSpeed=85});
    chassis.turnToHeading(180,800,{.maxSpeed=70});
    loaderMech.set_value(true);

    chassis.moveToPoint(34.25,-15,2000,{.maxSpeed=100},false);

    //chassis.moveToPoint(0,34.25,500,{.forwards=false,.maxSpeed=85});
    chassis.turnToHeading(180,500,{.maxSpeed=80});
    loaderMech.set_value(false);
    chassis.moveToPoint(35,25,2000,{.forwards=false});
    pros::delay(600);
    scoringBar.set_value(true);
    pros::delay(1600);
    
    left_dt.move(127);
    right_dt.move(-127); 
    pros::delay(450);
    left_dt.move(0);
    right_dt.move(0); 
    scoringBar.set_value(false);
    chassis.turnToHeading(280,400);
    chassis.moveToPoint(1,11,1200,{.maxSpeed=60});
    pros::delay(200);
    loaderMech.set_value(true);
    chassis.turnToHeading(270,500);
    chassis.moveToPoint(-27,10,1200,{.maxSpeed=67});
    pros::delay(200);
    loaderMech.set_value(false);
    pros::delay(800);
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
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(10);
    chassis.moveToPoint(-57,-17,1600);
    chassis.turnToHeading(180,500);
    loaderMech.set_value(true);
    chassis.moveToPoint(-57,-30,3000,{.maxSpeed= 70},false);
    chassis.moveToPoint(-57,20,3000,{.forwards = false, .minSpeed= 80});
    pros::delay(500);
    scoringBar.set_value(true);
    pros::delay(2000);
    scoringRoller.move(0);
    scoringBar.set_value(false);
    chassis.moveToPoint(-62,0,1500);
    chassis.turnToHeading(180,1500);
    chassis.moveToPoint(-62, 130, 2000);
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
void solo_awp(){
   //turn on intake 
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    //go perpendicular to loader
    chassis.moveToPoint(0,31.5,1400,{.maxSpeed=85});
    chassis.turnToHeading(90,800,{.maxSpeed=70});
    //drop loader mech
    loaderMech.set_value(true);
    //ram loader 
    chassis.moveToPoint(15,33.25,1100,{.maxSpeed=100},false);
    //fix lat alignment
    chassis.turnToHeading(90,500,{.maxSpeed=80});
    //retract loader mech
    loaderMech.set_value(false);
    //go to long goal
    chassis.moveToPoint(-20,34,1000,{.forwards=false},false);
    //let balls score
    scoringBar.set_value(true);
    //wait for blocks to be scored
    pros::delay(1100);
    //swing w 450ms turn
    left_dt.move(127);
    right_dt.move(-127); 
    pros::delay(450);
    left_dt.move(0);
    right_dt.move(0); 
    //retract bar once swung
    scoringBar.set_value(false);
    //correctional swing turn
    chassis.turnToHeading(190,400);
    //go to first 3 stack
    chassis.moveToPoint(-11,1,1200,{.maxSpeed=60});
    //correctional turn
    chassis.turnToHeading(180,500);
    //go to second 3 stack
    chassis.moveToPoint(-10,-27,1200,{.maxSpeed=67});
    //give initial delay before slow entry
    pros::delay(100);
    //slow entry into 3 stack without loader mech for psi retention
    chassis.moveToPoint(-10,-34.5,1200,{.maxSpeed=50});
    //turn opposite of mid goal
    chassis.turnToHeading(133,500);
    //ram mid goal
    chassis.moveToPoint(-24,-21.5,1200,{.forwards=false},false);
    //reverse 150ms then push forward to prevent clogging
    middleRollers.move(-127);
    scoringRoller.move(-127);
    frontIntake.move(-127);
    pros::delay(150);
    middleRollers.move(127);   
    frontIntake.move(127); 
    pros::delay(450);
    //scoring recovery 
    middleRollers.move(-127);
    pros::delay(100);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(10);
    //moves parallel to long goal
    chassis.moveToPoint(17,-59,1200);
    //correctional parallel with goal
    chassis.turnToHeading(90,500);
    //rams goal
    chassis.moveToPoint(-18,-59,1000,{.forwards=false});
    //lets pid settle
    pros::delay(500);
    //lets blocks score
    scoringBar.set_value(true);
}
void one_goal_left() {
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
    pros::delay(100);
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
    //pros::delay(100);
    chassis.moveToPoint(-31.51, 22.44, 1500, {.forwards = false});
    pros::delay(1000);
    scoringBar.set_value(true);
    pros::delay(700);
    chassis.moveToPoint(-31.51, 13.44, 1000, {});
    scoringBar.set_value(false);
    chassis.moveToPoint(-31.51, 30.44, 2000, {.forwards = false});
}

void one_goal_right() {
    frontIntake.move(127);
    colorSortRoller.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
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
    chassis.turnToPoint(34.51, 26.44, 800, {.forwards = false});
    chassis.moveToPoint(34.51, 26.44, 1500, {.forwards = false, .minSpeed = 30, .earlyExitRange = 5});
    //chassis.turnToHeading(180, 800);
    pros::delay(700);
    scoringBar.set_value(true);
    pros::delay(1300);
    chassis.moveToPoint(34.51, -12.41, 2000, {.minSpeed = 40});
    pros::delay(200);
    scoringBar.set_value(false);
    chassis.moveToPoint(34.51, -10.41, 2000, {.forwards = false}, false);
    //pros::delay(100);
    chassis.moveToPoint(34.51, 26.44, 1500, {.forwards = false});
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