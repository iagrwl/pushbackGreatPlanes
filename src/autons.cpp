#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "setup.hpp"


void two_goal(){
    /*chassis.moveToPose(0,50,0,2000);
    chassis.turnToPoint(-17,50,500);
    chassis.moveToPose(-11,48,-90,1500);
    
    //pros::delay(4000);
    
    chassis.moveToPose(17.5, 47,-90, 2000, {.forwards = false});*/
   
    chassis.moveToPoint(0, 40, 1500);
    chassis.turnToPoint(-15, 40, 800);
    intake.move(127);
    chassis.moveToPoint(-15, 40, 1000, {}, false);
    pros::delay(3000);
    chassis.moveToPoint(15, 49, 2000, {.forwards = false}, false);
    outtake.move(127);
    indexer.move(127);   

   
   
   
    //if (backDistance.get_distance()>)

    /*
    pros::delay(1400);
    outtake.move(127);
    indexer.move(127);
    intake.move(127);
    pros::delay(2700);
    outtake.move(0);
    indexer.move(0);
    chassis.swingToHeading(-220,lemlib::DriveSide::LEFT,1000);
    */

}
// to manipulate intake, intake.move(127 or 0);
// to give delay pros::delay(delay in ms);

/*
// make each auton route it's own function and write them here
void one_goal() {
    chassis.turnToPoint(); //point towards 3 stack 
    //start intake 
    chassis.moveToPoint();  //move towards 3 stack and collect
    //collection delay
    chassis.moveToPose(); //move in front of match loader 
    chassis.turnToPoint(); //turn in match loader direction
    chassis.moveToPoint(); //move into match loader and collect
    chassis.moveToPose(); //back up into goal
    //stop intake to allocate more current to outtake
    //start outtake
    //dump delay

    //baaaam
}

void two_goal(){
    chassis.turnToPoint(); //face in direction of line-up point
    chassis.moveToPoint(); //move downwards into line-up point
    chassis.turnToPoint(); //line-up with match loader
    //start intake
    chassis.moveToPoint(); //move into match loader and collect
    //collection delay
    chassis.moveToPose();  //back up into goal
    //stop intake to allocate more current to outtake
    //start outtake
    //dump delay
    //stop outtake 
    //start intake
    chassis.swingToPoint(); //lock right dt to swing pointing towards 3 stack
    chassis.moveToPoint(); //move upwards into 3 stack and collect
    //collection delay
    chassis.turnToPoint(); //point robot inverse to low goal
    chassis.moveToPoint(); //back up into goal
    //stop intake to allocate more current to outtake
    //start outtake
    //dump delay
    //baaamamamammmm
}

void solo_awp(){
    chassis.turnToPoint(); //face in direction of line-up point
    chassis.moveToPoint(); //move downwards into line-up point
    chassis.turnToPoint(); //line-up with match loader
    //start intake
    chassis.moveToPoint(); //move into match loader
    //collection delay
    chassis.moveToPose();  //back up into goal
    //stop intake to allocate more current to outtake
    //start outtake
    //dump delay
    //stop outtake 
    //start intake
    chassis.swingToPoint(); //lock right dt to swing pointing towards 3 stack
    chassis.moveToPoint(); //move upwards into 3 stack and collect
    //collection delay
    chassis.turnToPoint(); //point robot inverse to low goal
    chassis.moveToPoint(); //back up into goal
    //stop intake to allocate more current to outtake
    //start outtake
    //dump delay
    //stop outtake 
    //start intake
    chassis.swingToPoint(); //lock right dt and face second 3 stack
    chassis.moveToPoint(); //move forwards towards 3 stack and collect
    //collection delay
    chassis.turnToPoint(); //face inverse of high-goal
    chassis.moveToPoint(); //back up into goal
    //stop intake to allocate more current to outtake
    //start outtake
    //dump delay

    //biggtly baaaaam
}
    */


void one_goal() {
    intake.move(127);
    outtake.move(127);

    chassis.moveToPoint(0, 15, 1000);
    chassis.swingToHeading(-50, lemlib::DriveSide::LEFT, 1000, {.maxSpeed = 80});
    chassis.moveToPoint(-17, 38, 1000);
    loaderMech.set_value(true);
    pros::delay(250);
    loaderMech.set_value(false);
    pros::delay(200);
    chassis.moveToPoint(-30.35, 38.82, 1000, {.minSpeed = 60});
    intake.move(0);
    pros::delay(250);
    loaderMech.set_value(true);
    pros::delay(300);
    chassis.moveToPoint(-10.95, 28.24, 1000, {.forwards = false});
    pros::delay(100);
    intake.move(127);
    chassis.moveToPoint(-10.95, 28.24, 1000, {.forwards = false});
    pros::delay(100);
    loaderMech.set_value(false);
    chassis.turnToPoint(-30.73, -1.12, 800);
    chassis.moveToPoint(-32.73, -1.12, 1000);
    chassis.turnToPoint(-32.5, 18, 800, {.forwards = false});
    chassis.moveToPoint(-32.5, 25, 2000, {.forwards = false});
    pros::delay(50);
    while (left_dt.get_actual_velocity() < -5 && right_dt.get_actual_velocity() < -5) {
    }
    indexer.move(127);
    
    /*chassis.swingToHeading(-90, lemlib::DriveSide::LEFT, 800);
    pros::delay(300);
    
    loaderMech.set_value(true);
    intake.move(-127);
    //chassis.swingToHeading(-20, lemlib::DriveSide::LEFT, 800);
    chassis.swingToPoint(-10.95, 28.24, lemlib::DriveSide::LEFT, 800, {.forwards = false});
    intake.move(127);
    */
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

        pros::lcd::print(i+2, "%d: %.2f", currDist, chassis.getPose().y);

        chassis.moveToPoint(0, 0, 3000, {.forwards = false});
        
        

    }
}