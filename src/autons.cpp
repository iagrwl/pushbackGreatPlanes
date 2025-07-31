#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "setup.hpp"

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