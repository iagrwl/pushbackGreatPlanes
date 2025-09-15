#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "op_control.hpp"

void two_goal_LEFT() {
    chassis.setPose(0,0,30);
    
}

/*pros::Distance* currSensor;

int currCount = 0;
int direction = 1;
void scoreBlocks(int count, bool isTop, int speed) {
    isTop ? currSensor = &topCounterDistance : currSensor = &topCounterDistance; // change else to midCounterDistance
    isTop ? direction = 1 : direction = -1;

    indexer.move(80);
    outtake.move(direction * speed);
    while (currCount <= count) {
        if (topCounterDistance.get_distance() < 80) {
            while (topCounterDistance.get_distance() < 80) {
            }
            currCount++;
            pros::lcd::print(4, "Count: %d", currCount);
        }
    }
    pros::delay(500);

    indexer.move(0);
    outtake.move(127);
}
*/


/*
void two_goal_RIGHT(){
    // setup
    intake.move(127); // switches intake on max speed
    outtake.move(127); // switches outtake on max speed to assist intaking bhna
    // move to loader
    chassis.moveToPoint(0,30,1000); // moves laterally in front of loader
    chassis.turnToHeading(90,750); // turns right into loader
    pros::delay(100); // waits for turn to completely finish
    // loader pick up
    loaderMech.set_value(true); // extends the loader mech
    chassis.moveToPoint(12,30.5,1100, {.maxSpeed=50}, false); // ramming into the loader
    pros::delay(115); // waits for blocks to come down into intake
    chassis.moveToPoint(-2,31.5,1100,{.forwards=false}); // moves back to mid position between goal and loader
    loaderMech.set_value(false); // retracts loader mech
    // scoring into long goal
    chassis.moveToPoint(-23,30.8,1300,{.forwards=false, .maxSpeed = 45}, false); // drives reverse into long goal
    indexer.move(60); // switches indexer on optimal scoring speed
    outtake.move(60); // switches outtake on optimal scoring speed
    pros::delay(1800); // waits for blocks to go into long goal
    // push blocks into control zone
    chassis.moveToPoint(-8,31,800); // moves a bit forward 
    descoreMech.set_value(true); // flips up descore mech
    chassis.moveToPoint(-24,31,1000,{.forwards=false,.minSpeed=60}, false); // rams into goal to push into control zone
    pros::delay(300); // waits for balls to settle
    // movement to 3 ball stack
    chassis.moveToPoint(-2,30,1000); // moves forward to prepare for turning in 3 balls
    descoreMech.set_value(false); // sets descore mech to retract
    outtake.move(127); // sets outtake to help intake balls up
    indexer.move(0); // turns indexer off to help keep balls in
    chassis.turnToPoint(-30.27,2.3,750, {.maxSpeed = 65,.minSpeed = 30, .earlyExitRange = 10}); // turns toward point and EER allows for quick transition into the movement to it
    pros::delay(200); // delay for turning bc async off
    chassis.moveToPoint(-30.27,2.3,1000, {.maxSpeed = 80,.minSpeed = 40}, false); // moves forward to point to intake
    chassis.turnToPoint(-34, -6, 800, {.forwards = false}); // aligns with blocks
    chassis.moveToPose(-35.7,-5.5,406.5,1300,{.forwards=false}, false); // turns around with a quick swing with async off to let swing/turn settle
    //pros::delay(1000);
    outtake.move(-50); //optimal scoring speed for mid goal
    indexer.move(50); //^^
}
*/

/*
void two_goal_LEFT(){
    
    // setup
    intake.move(127); // switches intake on max speed
    outtake.move(127); // switches outtake on max speed to assist intaking bhna
    // move to loader
    chassis.moveToPoint(0,30,1000); // moves laterally in front of loader
    chassis.turnToHeading(-90,750); // turns right into loader
    pros::delay(100); // waits for turn to completely finish
    // loader pick up
    loaderMech.set_value(true); // extends the loader mech
    chassis.moveToPoint(-12,30.5,1100, {.maxSpeed=50}, false); // ramming into the loader
    pros::delay(120); // waits for blocks to come down into intake
    chassis.moveToPoint(2,30.5,1200,{.forwards=false}); // moves back to mid position between goal and loader
    loaderMech.set_value(false); // retracts loader mech
    // scoring into long goal
    chassis.moveToPoint(23,30.6,1300,{.forwards=false, .maxSpeed = 40}, false); // drives reverse into long goal
    indexer.move(60); // switches indexer on optimal scoring speed
    outtake.move(60); // switches outtake on optimal scoring speed
    pros::delay(1800); // waits for blocks to go into long goal
    // push blocks into control zone
    chassis.moveToPoint(8,30.6,800); // moves a bit forward 
    descoreMech.set_value(true); // flips up descore mech
    chassis.moveToPoint(24,30.6,1000,{.forwards=false,.minSpeed=60}, false); // rams into goal to push into control zone
    pros::delay(300); // waits for balls to settle
    // movement to 3 ball stack
    chassis.moveToPoint(2,29.5,1000); // moves forward to prepare for turning in 3 balls
    descoreMech.set_value(false); // sets descore mech to retract
    outtake.move(127); // sets outtake to help intake balls up
    indexer.move(0); // turns indexer off to help keep balls in
    chassis.turnToPoint(32,1,750, {.maxSpeed = 65,.minSpeed = 30, .earlyExitRange = 10}); // turns toward point and EER allows for quick transition into the movement to it
    pros::delay(200); // delay for turning bc async off
    chassis.moveToPose(38.5,-4,130,1400, {.maxSpeed = 70,.minSpeed = 40}, false); // moves forward to point to intake
    pros::delay(500);
    intake.move(-80);
    outtake.move(-127);
    indexer.move(-127);
}
*/


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

/*
void one_goal_left() {
    intake.move(127);
    outtake.move(127);

    chassis.moveToPoint(0, 15, 1000, {.minSpeed = 40, .earlyExitRange = 2});
    chassis.swingToHeading(-50, lemlib::DriveSide::LEFT, 1000, {.maxSpeed = 80});
    
    chassis.moveToPoint(-9.11, 28.21, 1000);
    pros::delay(250);
    loaderMech.set_value(true);
       
    chassis.turnToPoint(-30.73, -1.12, 800);
    chassis.moveToPoint(-30.73, -1.12, 1000);
    chassis.turnToPoint(-30.5, -10, 800, {});
    
    chassis.moveToPoint(-30.5, -15, 1000, {/*.forwards = false*//*});
    pros::delay(100);
    intake.move(127);
    pros::delay(300);
    chassis.moveToPoint(-31, 25, 1500, {.forwards = false, .maxSpeed = 60});
    pros::delay(100);
    while (left_dt.get_actual_velocity() < -5 || right_dt.get_actual_velocity() < -5) {
    }

    left_dt.move(-127);
    right_dt.move(-127);
    indexer.move(127);
    pros::delay(2000);
    chassis.moveToPoint(-32, 6, 1000);
    chassis.turnToHeading(-90, 800, {.minSpeed = 30, .earlyExitRange = 15});
    chassis.moveToPoint(-22, 6, 1000, {.forwards = false, .minSpeed = 50, .earlyExitRange = 2});
    wingMech.set_value(true);
    chassis.turnToHeading(-180, 800, {.minSpeed = 30, .earlyExitRange = 15});
    chassis.moveToPoint(-22, 35, 2000, {.forwards = false, .maxSpeed = 80, .minSpeed = 30});
}

void one_goal_right(){
    intake.move(127);
    outtake.move(127);

    chassis.moveToPoint(0, 15, 1000, {.minSpeed = 40, .earlyExitRange = 2});
    chassis.swingToHeading(-50, lemlib::DriveSide::RIGHT, 1000, {.maxSpeed = 80});
    
    chassis.moveToPoint(9.11, 28.21, 1000);
    pros::delay(250);
    loaderMech.set_value(true);
       
    chassis.turnToPoint(30.73, -1.12, 800);
    chassis.moveToPoint(30.73, -1.12, 1000);
    chassis.turnToPoint(30.5, -10, 800, {});
    
    chassis.moveToPoint(30.5, -15, 1000, {/*.forwards = false*//*});
    pros::delay(100);
    intake.move(127);
    pros::delay(300);
    chassis.moveToPoint(31, 25, 1500, {.forwards = false, .maxSpeed = 60});
    pros::delay(100);
    while (left_dt.get_actual_velocity() < -5 || right_dt.get_actual_velocity() < -5) {
    }

    left_dt.move(-127);
    right_dt.move(-127);
    indexer.move(127);
    pros::delay(2000);
    chassis.moveToPoint(32, 6, 1000);
    chassis.turnToHeading(90, 800, {.minSpeed = 30, .earlyExitRange = 15});
    chassis.moveToPoint(22, 6, 1000, {.forwards = false, .minSpeed = 50, .earlyExitRange = 2});
    wingMech.set_value(true);
    chassis.turnToHeading(180, 800, {.minSpeed = 30, .earlyExitRange = 15});
    chassis.moveToPoint(22, 35, 2000, {.forwards = false, .maxSpeed = 80, .minSpeed = 30});
}
*/


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