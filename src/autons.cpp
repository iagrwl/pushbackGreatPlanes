#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "op_control.hpp"
/*
float wallDistance(bool shouldPrint = false) {
    //This accounts for the sensor turning off of the center of the bot
    //X means offset from the center along the width of the bot, Y means along the length
    float offsetX = 2; 
    float offsetY = 0; 

    float distancemm = sideDistance.get();
    float distanceIn = distancemm / 25.4 + offsetX;

    float angDeg = chassis.getPose().theta;
    float angRad = angDeg * M_PI / 180.0;

    //It was buggy so now if the angle is like 400 it'll turn to 40
    float angle = fmod(angDeg, 360.0);
    //Mod doesn't work on negatives for some reason
    if (angle < 0) angle += 360.0;

    float rotatedX = offsetX * cos(angRad) - offsetY * sin(angRad);
    float rotatedY = offsetX * sin(angRad) + offsetY * cos(angRad);

    float correctedDist = 0;
    float finalPos = 0;
    //Left Wall
    if (angle >= 315 || angle < 45) {
        correctedDist = distanceIn * cos(angRad) + rotatedX;
        finalPos = correctedDist -71;
    //Back Wall
    } else if (angle >= 45 && angle < 135) {
        correctedDist = distanceIn * sin(angRad) + rotatedY;
        finalPos = 71 -correctedDist ;
    //Right Wall
    } else if (angle >= 135 && angle < 225) {
        correctedDist = -distanceIn * cos(angRad) - rotatedX;
        finalPos = 71 - correctedDist ;
    //Close Wall
    } else {
        correctedDist = -distanceIn * sin(angRad) - rotatedY;
        finalPos =  correctedDist  - 71;
    }

    if (shouldPrint) {
        
         pros::lcd::print(5, "Distance: %f", distanceIn);
         pros::lcd::print(6, "Corrected: %f", correctedDist);
         pros::lcd::print(7, "Final Pos: %f", finalPos);
    }

    return finalPos;
}
*/

void wallDistance(bool shouldPrint = false) {
    float robotX = chassis.getPosition().x;
    float robotY = chassis.getPosition().y;
    float angDeg = chassis.getPose().theta;
    float angRad = angDeg * M_PI / 180.0;

    // Sensor offsets
    float rightOffsetX = 1.0, rightOffsetY = 2.0;
    float leftOffsetX  = 2.0, leftOffsetY  = 0.0;

    //Finds the sensor's coordinates using fancy math
    //Basically we measure the robot's coordinate's from it's center but the distance sensors are offset from the center of the robot
    //We take the robot's coordinates and angle and the distance sensor's offset and find out where the distance sensors are in the field
    //If you want me to like fully explain it call me
    auto getSensorCoords = [&](float offsetX, float offsetY) {
        return std::pair<float,float>(
            robotX + offsetX * cos(angRad) - offsetY * sin(angRad),
            robotY + offsetX * sin(angRad) + offsetY * cos(angRad)
        );
    };
    auto [rightSensorX, rightSensorY] = getSensorCoords(rightOffsetX, rightOffsetY);
    auto [leftSensorX,  leftSensorY ] = getSensorCoords(leftOffsetX,  leftOffsetY);

    //So like before we had these ranges in degrees that measured the robot's angle to determine which wall it was facing
    //smth like if (angle >= 315 || angle < 45) {
    //But I realized that was dumb since we already use radians for other stuff 
    //So now we use vectors and all thats important is the sign of the numbers
    //So like if the x is positive and the y is 0 we know its facing the right wall
    //Basically all you need to know is that plugging in the angle gets you a coordinate that points in the direction the sensor is facing
    //If you want me to like fully explain it call me
    float rightVecX =  cos(angRad), rightVecY =  sin(angRad);
    float leftVecX  = -cos(angRad), leftVecY  = -sin(angRad);

    //I decided to use the ray formula for this just because theres a formula for it and I didn't know how to do it with trig
    //The formula Position(t) = Start + t * Direction
    //t just tells you far along the ray you are so like t=0 is the start and t=1 is one unit along the ray etc
    //sx and sy are the sensor's position and dx and dy are the sensor direction vectors
    //The 71 are the walls x and y coordinates
    //Basically we solve for the t where the ray intersects each wall and take the smallest positive t to find the closest wall
    //It seems kinda complicated but its actually simple and this is lowkey what frc does 
    //We probably didn't need to all ts but like if it's good we can reset our position without lining up
    auto getWallDistance = [&](float sx, float sy, float dx, float dy) {
        float t = INFINITY;
        float toLeft  = (-71 - sx) / dx;
        float toRight = ( 71 - sx) / dx;
        float toBack  = (-71 - sy) / dy;
        float toFront = ( 71 - sy) / dy;
        if (toLeft  > 0) t = fmin(t, toLeft);
        if (toRight > 0) t = fmin(t, toRight);
        if (toBack  > 0) t = fmin(t, toBack);
        if (toFront > 0) t = fmin(t, toFront);
        return t;
    };

    //ts just calls the function
    float rightDist = getWallDistance(rightSensorX, rightSensorY, rightVecX, rightVecY);
    float leftDist  = getWallDistance(leftSensorX,  leftSensorY,  leftVecX,  leftVecY);

    //ts js picks the sensor with the closest wall
    //it uses the right sensor if the right t is smaller than the left t
    bool useRight = (rightDist < leftDist);
    float chosenDist = useRight ? rightDist : leftDist;
    float sensorX = useRight ? rightSensorX : leftSensorX;
    float sensorY = useRight ? rightSensorY : leftSensorY;
    float vecX    = useRight ? rightVecX : leftVecX;
    float vecY    = useRight ? rightVecY : leftVecY;

    //Ts just like the distance it hits at
    float hitX = sensorX + chosenDist * vecX;
    float hitY = sensorY + chosenDist * vecY;

    //sets the pose but only updates the coordinate that was corrected
    //it takes the absolute value of wherever the sensor hit the wall and checks if it's 71
    float correctedX = robotX;
    float correctedY = robotY;
    float errorMargin = 1.0; 
    if (fabs(fabs(hitX) - 71) < errorMargin) correctedX = hitX;
    if (fabs(fabs(hitY) - 71) < errorMargin) correctedY = hitY;

    if (shouldPrint) {
        pros::lcd::print(5, "Chosen Sensor: %s", useRight ? "Right" : "Left");
        pros::lcd::print(6, "Robot Pos: (%.2f, %.2f)", robotX, robotY);
        pros::lcd::print(7, "Hit Pos:   (%.2f, %.2f)", hitX, hitY);
        pros::lcd::print(8, "Corrected: (%.2f, %.2f, %.2f)", correctedX, correctedY, angDeg);
    }
    //I haven't tested if it'll let you call it and it just sets it or if I needa return something
    chassis.setPose({correctedX, correctedY, angDeg});
}

void autonSkills() {
    
    //SETUP
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    left_dt.set_brake_mode(pros::MotorBrake::brake);
    right_dt.set_brake_mode(pros::MotorBrake::brake);
    /*
    //Q1
    chassis.setPose(15,-48,90);
    chassis.moveToPoint(47,-48,1400,{.minSpeed=60,.earlyExitRange=8});
    chassis.turnToHeading(180,2000,{.maxSpeed=50},false);
    loaderMech.set_value(true);
    pros::delay(100);
    chassis.moveToPoint(48,-65,2500,{.maxSpeed=60},false);
    chassis.turnToHeading(180,500,{.maxSpeed=80});
    loaderMech.set_value(false);
    chassis.moveToPoint(48,-22,2000,{.forwards=false,.minSpeed=80});
    pros::delay(900);
    scoringBar.set_value(true);
    pros::delay(600);
    frontIntake.move(0);
    middleRollers.move(0);
    scoringRoller.move(0);
    pros::delay(200);
    scoringBar.set_value(false);
    float correctedPos = wallDistance(true);
    chassis.setPose(correctedPos, -30, chassis.getPose().theta);

    chassis.moveToPoint(48,-36,2000,{.maxSpeed=85});
    pros::delay(200);
    wingMech.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringBar.set_value(false);
    chassis.turnToPoint(60,-26,1500,{.maxSpeed=60});
    chassis.moveToPoint(60,-26,1500,{.minSpeed=60,.earlyExitRange=2});
    chassis.turnToHeading(0,1500);
    chassis.moveToPoint(60,36,3000,{.minSpeed=60,.earlyExitRange=8});
    chassis.turnToPoint(45,48,1500,{.maxSpeed=60,.earlyExitRange=2});
    chassis.moveToPose(45,48,0,2000,{.maxSpeed=60});
    chassis.turnToHeading(0,1500,{.maxSpeed=80});
    pros::delay(300);
    loaderMech.set_value(true);
    pros::delay(300);
    chassis.moveToPoint(46,70,3000,{.maxSpeed=60});
    pros::delay(1000);
    chassis.moveToPoint(46,22,2500,{.forwards=false,.maxSpeed=80});
    pros::delay(1300);
    scoringBar.set_value(true);
    loaderMech.set_value(false);
    pros::delay(2000);
    chassis.setPose(chassis.getPose().x, 30, chassis.getPose().theta);
    scoringBar.set_value(false);   
    */
    chassis.setPose(48, 30, chassis.getPose().theta);
    chassis.moveToPose(18,63,-90,3000,{.minSpeed=70,.earlyExitRange=5});
    chassis.turnToHeading(-75,500,{.earlyExitRange=5},false);
    right_dt.move(90);
    left_dt.move(90);
    pros::delay(1600);
    left_dt.move(0);
    right_dt.move(0);
    chassis.turnToHeading(-105,1500,{.earlyExitRange=5},false);
    right_dt.move(-25);
    left_dt.move(-25);
    pros::delay(500);
    loaderMech.set_value(true);
    pros::delay(1200);
    loaderMech.set_value(false);
    left_dt.move(0);
    right_dt.move(0);
    chassis.turnToHeading(-90,1500);
    wallDistance(false);
    /*
        frontIntake.move(127);iop[poio]iu
    middleRollers.move(127);
    scoringRoller.move(127);
    left_dt.set_brake_mode(pros::MotorBrake::brake);
    right_dt.set_brake_mode(pros::MotorBrake::brake);
    //Q1
    chassis.moveToPoint(31.5,0,1400,{.maxSpeed=75});
    chassis.turnToHeading(180,2000,{.maxSpeed=50},false);
    loaderMech.set_value(true);
    pros::delay(500);
    chassis.moveToPoint(32,-18,2500,{.maxSpeed=60},false);
    chassis.turnToHeading(180,500,{.maxSpeed=80});
    loaderMech.set_value(false);
    chassis.moveToPoint(32,30,2000,{.forwards=false,.maxSpeed=80});
    pros::delay(900);
    scoringBar.set_value(true);
    pros::delay(600);
    frontIntake.move(0);
    middleRollers.move(0);
    scoringRoller.move(0);
    pros::delay(200);
    scoringBar.set_value(false);
    */
    /*
    //Q2
    chassis.moveToPoint(35,7,2000,{.maxSpeed=85});
    pros::delay(200);
    wingMech.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringBar.set_value(false);
    chassis.turnToPoint(44,30,1500,{.maxSpeed=60});
    chassis.moveToPoint(44,30,1500,{.maxSpeed=60});
    chassis.turnToHeading(0,1500);
    chassis.moveToPoint(43,93,3000,{.maxSpeed=85});
    chassis.turnToPoint(28.5,102,1500,{.maxSpeed=60});
    chassis.moveToPoint(28.5,102,2000,{.maxSpeed=60});
    chassis.turnToHeading(0,1500,{.maxSpeed=80});
    pros::delay(300);
    loaderMech.set_value(true);
    pros::delay(300);
    chassis.moveToPoint(26.75,123,3000,{.maxSpeed=60});
    pros::delay(1000);
    chassis.moveToPoint(28.5,85,2500,{.forwards=false,.maxSpeed=80});
    pros::delay(1300);
    scoringBar.set_value(true);
    pros::delay(2000);
    loaderMech.set_value(false);
    chassis.moveToPoint(28.5,96,3000,{.maxSpeed=60},false);
    scoringBar.set_value(false);
    chassis.moveToPoint(28.5,85,2500,{.forwards=false,.minSpeed=80});
    chassis.moveToPoint(28.5,100,3000,{.maxSpeed=60},false);
    chassis.turnToHeading(-90,1500);
    chassis.moveToPoint(-74.5,100,5000,{.maxSpeed=60},false);
    chassis.turnToHeading(0,1500);
    loaderMech.set_value(true);
    chassis.moveToPoint(-76,123,2500,{.maxSpeed=60});
    pros::delay(1000);
    chassis.moveToPoint(-77,85,2500,{.forwards=false,.maxSpeed=80});
    pros::delay(900);
    scoringBar.set_value(true);
    pros::delay(500);
    frontIntake.move(0);
    middleRollers.move(0);
    scoringRoller.move(0);
    pros::delay(200);
    scoringBar.set_value(false);
    pros::delay(200);
    loaderMech.set_value(false);
    chassis.moveToPoint(-77,102,3000,{.maxSpeed=60},false);
    chassis.turnToPoint(-92,83,1500); 
    chassis.moveToPoint(-92,83,1500,{.maxSpeed=60});
    chassis.turnToHeading(180,1500);
    chassis.moveToPoint(-90,15,3000,{.maxSpeed=60},false);
    chassis.turnToPoint(-76,0,1500); 
    chassis.moveToPoint(-76,0,2500,{.maxSpeed=60});
    chassis.turnToHeading(180,1500);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    loaderMech.set_value(true);
    chassis.moveToPoint(-74,-20,2500,{.maxSpeed=60},false);
    pros::delay(1000);
    chassis.moveToPoint(-75,35,2500,{.forwards=false,.maxSpeed=80});
    pros::delay(1300);
    scoringBar.set_value(true);
    pros::delay(2000);
    loaderMech.set_value(false);
    chassis.moveToPoint(-75,3,3000,{.maxSpeed=60},false);
    scoringBar.set_value(false);
    chassis.moveToPoint(-75,35,2500,{.forwards=false,.maxSpeed=80});
    chassis.moveToPoint(-75,20,3000,{.maxSpeed=60},false);
    chassis.turnToPoint(-27,-10,2500,{.maxSpeed=80});
    chassis.moveToPoint(-27,-10,2500,{.maxSpeed=80});
    chassis.turnToHeading(90,1500);
    loaderMech.set_value(true);
    chassis.moveToPoint(0,-10,5000,{.maxSpeed=80},false);
    /*
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
    /*
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
    /*wingMech.set_value(true);
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
    chassis.moveToPoint(15,33.25,1050,{.maxSpeed=100},false);
    //fix lat alignment
    chassis.turnToHeading(90,400,{.maxSpeed=80});
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
    chassis.moveToPoint(-11,1,1200,{.maxSpeed=55});
    //correctional turn
    chassis.turnToHeading(180,500);
    //go to second 3 stack
    chassis.moveToPoint(-10,-27,1200,{.maxSpeed=67});
    //give initial delay before slow entry
    pros::delay(100);
    //slow entry into 3 stack without loader mech for psi retention
    chassis.moveToPoint(-10,-35,1200,{.maxSpeed=50});
    //turn opposite of mid goal
    chassis.turnToHeading(133,500);
    //ram mid goal
    chassis.moveToPoint(-24,-21.5,1100,{.forwards=false},false);
    //reverse 150ms then push forward to prevent clogging
    middleRollers.move(-127);
    scoringRoller.move(-127);
    frontIntake.move(-127);
    pros::delay(150);
    middleRollers.move(127);   
    frontIntake.move(127); 
    pros::delay(460);
    //scoring recovery 
    middleRollers.move(-127);
    pros::delay(110);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(10);
    //moves parallel to long goal
    chassis.moveToPoint(17,-59,1300);
    //correctional parallel with goal
    chassis.turnToHeading(90,400);
    //rams goal
    chassis.moveToPoint(-18,-59,1000,{.forwards=false});
    //lets pid settle
    pros::delay(500);
    //lets blocks score
    scoringBar.set_value(true);
    wingMech.set_value(false);*/
    wingMech.set_value(true);
    //turn on intake 
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    chassis.moveToPoint(0,32, 1500, {.maxSpeed = 80});
    chassis.turnToPoint(12,39,800);
    loaderMech.set_value(true);
    chassis.moveToPoint(16,39,1000, {.minSpeed = 60});
    chassis.moveToPoint(-24,40,1800, {.forwards = false, .maxSpeed = 90});
    pros::delay(600);
    scoringBar.set_value(true);
    pros::delay(1200);
    loaderMech.set_value(false);
    scoringBar.set_value(false);
    chassis.turnToHeading(200, 800);
    chassis.moveToPoint(-6, 9, 1000, {.maxSpeed = 60, .minSpeed = 30, .earlyExitRange = 2});
    chassis.moveToPoint(-4, -32, 1500, {.maxSpeed = 90});
    chassis.turnToPoint(-16, -19.5, 800, {.forwards = false});
    chassis.moveToPoint(-16,-19.5, 1000, {.forwards = false, .maxSpeed = 80});
    middleRollers.move(-127);
    scoringRoller.move(-127);
    frontIntake.move(-127);
    pros::delay(150);
    middleRollers.move(100);   
    frontIntake.move(100); 
    pros::delay(460);

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
    chassis.moveToPoint(-33,-25,1200,{.maxSpeed= 60},false);
    chassis.moveToPoint(-33,20,1700,{.forwards = false, .maxSpeed= 70},false);
    scoringBar.set_value(true);
    pros::delay(700);
    chassis.moveToPoint(-33,-25,2000,{.maxSpeed=80},false);
    scoringBar.set_value(true);
    pros::delay (300);
    scoringBar.set_value(false);
    chassis.moveToPoint(-33,10,2000,{.forwards=false,.minSpeed=100},false);
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
    chassis.turnToPoint(-30.21, -3.95, 800);
    chassis.moveToPoint(-31.21, -3.95, 1500);
    chassis.turnToPoint(-31.51, 20.44, 800, {.forwards = false});
    chassis.moveToPoint(-31.51, 20.44, 1500, {.forwards = false});
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
    pros::delay(450);
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
    /*chassis.moveToPoint(33.51, 26.44, 1500, {.forwards = false});
    //chassis.turnToHeading(180, 800);
    pros::delay(700);
    scoringBar.set_value(true);
    pros::delay(1300);*/
    chassis.moveToPoint(34.51, -12.41, 1600, {.maxSpeed = 100});
    pros::delay(200);
    scoringBar.set_value(false);
    //chassis.moveToPoint(34.51, -10.41, 2000, {.forwards = false}, false);
    //pros::delay(100);
    chassis.moveToPoint(35.51, 26.44, 1500, {.forwards = false});
    pros::delay(200);
    loaderMech.set_value(false);
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pros::delay(200);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    pros::delay(600);
    scoringBar.set_value(true);
    pros::delay(2000);
    chassis.moveToPoint(34.51, 13.44, 1000, {});
    scoringBar.set_value(false);
    chassis.moveToPoint(34.51, 30.44, 2000, {.forwards = false});
}


void turnTesting(bool isCW) {

    const int SIZE = 8;
    int turns[SIZE] = {15, 30, 45, 60, 90, 120, 150, 180};
    int actualTurn[SIZE] = {};
    int currTurn;

    for (int i = 0; i < SIZE; i++) {
        isCW ? currTurn = turns[i] : currTurn = -turns[i];

        chassis.turnToHeading(currTurn,2000, {}, false);

        pros::delay(1000);

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