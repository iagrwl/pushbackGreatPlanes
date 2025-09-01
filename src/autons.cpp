#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"


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

/*
void solo_awp(){
    intake.move(100);
    outtake.move(100);

    chassis.moveToPoint(0, 15, 1000, {.minSpeed = 40, .earlyExitRange = 2});
    chassis.swingToHeading(-50, lemlib::DriveSide::LEFT, 1000, {.maxSpeed = 80});
    pros::delay(100);
    outtake.move(50);
    chassis.moveToPoint(-9.11, 28.21, 1000);
    intake.move(50);
    //pros::delay(250);
    //loaderMech.set_value(true);

    chassis.turnToPoint(3.26, 38.26, 750);
    intake.move(0);
    outtake.move(0);
    loaderMech.set_value(false);
    chassis.moveToPose(3.26, 38.26, 45.07, 1500, {.minSpeed = 50});
    pros::delay(100);
    intake.move(-85);
    outtake.move(-85);
    pros::delay(1000);
    intake.move(127);
    outtake.move(127);
    chassis.moveToPoint(-5.04, 28.77, 1000, {.forwards = false});
    chassis.turnToPoint(40, 28.58, 800, {.minSpeed = 30, .earlyExitRange = 20});
    chassis.moveToPoint(40, 28.58, 3000);
    chassis.turnToPoint(28.66, 38.5, 800, {.forwards = false});
    chassis.moveToPoint(28.66, 38.5, 1500, {.forwards = false}, false);
    left_dt.move(-127);
    right_dt.move(-127);
    indexer.move(127);
    outtake.move(-127);
    pros::delay(700);
    indexer.move(-127);
    outtake.move(127);
    left_dt.move(0);
    right_dt.move(0);

    //intake.move(0);
    //outtake.move(0);


    
}
*/

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

        pros::lcd::print(i+2, "%d: %.2f", currDist, chassis.getPose().y);

        chassis.moveToPoint(0, 0, 3000, {.forwards = false});
        
        

    }
}