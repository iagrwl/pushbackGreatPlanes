#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "op_control.hpp"




/*
Pose wallDistance(bool shouldPrint = false, bool updatePose = true) {
    float robotX = chassis.getPose().x;
    float robotY = chassis.getPose().y;
    float angDeg = chassis.getPose().theta;
    float angRad = angDeg * M_PI / 180.0;

    float rightOffsetX = 4.5, rightOffsetY = 0.0;
    float leftOffsetX  = 4.5, leftOffsetY  = 1.0;

    auto getSensorCoords = [&](float offsetX, float offsetY) {
        return std::pair<float,float>(
            robotX + offsetX * cos(angRad) - offsetY * sin(angRad),
            robotY + offsetX * sin(angRad) + offsetY * cos(angRad)
        );
    };
    auto [rightSensorX, rightSensorY] = getSensorCoords(rightOffsetX, rightOffsetY);
    auto [leftSensorX,  leftSensorY ] = getSensorCoords(leftOffsetX,  leftOffsetY);

    float fwdX = cos(angRad);
    float fwdY = sin(angRad);

    auto rayHit = [&](float sx, float sy) {
        float bestT = INFINITY;
        float hx = sx, hy = sy;

        if (fabs(fwdX) > 1e-6) {
            float tLeft  = (-FIELD_HALF - sx) / fwdX;
            float tRight = ( FIELD_HALF - sx) / fwdX;
            if (tLeft  > 0 && tLeft  < bestT) bestT = tLeft;
            if (tRight > 0 && tRight < bestT) bestT = tRight;
        }
        if (fabs(fwdY) > 1e-6) {
            float tBack  = (-FIELD_HALF - sy) / fwdY;
            float tFront = ( FIELD_HALF - sy) / fwdY;
            if (tBack  > 0 && tBack  < bestT) bestT = tBack;
            if (tFront > 0 && tFront < bestT) bestT = tFront;
        }

        if (bestT < INFINITY) {
            hx = sx + bestT * fwdX;
            hy = sy + bestT * fwdY;
        }
        return std::pair<float,float>(hx, hy);
    };

    auto [hitRX, hitRY] = rayHit(rightSensorX, rightSensorY);
    auto [hitLX, hitLY] = rayHit(leftSensorX,  leftSensorY);

    float distR = hypot(hitRX - rightSensorX, hitRY - rightSensorY);
    float distL = hypot(hitLX - leftSensorX,  hitLY - leftSensorY);

    bool useRight = (distR < distL);
    float hitX = useRight ? hitRX : hitLX;
    float hitY = useRight ? hitRY : hitLY;

    float correctedX = robotX;
    float correctedY = robotY;
    if (fabs(fabs(hitX) - FIELD_HALF) < ERROR_MARGIN) correctedX = hitX;
    if (fabs(fabs(hitY) - FIELD_HALF) < ERROR_MARGIN) correctedY = hitY;

    Pose rayPose{correctedX, correctedY, angDeg};
    Pose odoPose{robotX, robotY, angDeg};

    float dx = rayPose.x - odoPose.x;
    float dy = rayPose.y - odoPose.y;
    float dTheta = rayPose.theta - odoPose.theta;
    float distError = hypot(dx, dy);

    if (shouldPrint) {
        pros::lcd::print(0, "Odo Pose: (%.2f, %.2f, %.2f)", odoPose.x, odoPose.y, odoPose.theta);
        pros::lcd::print(1, "Ray Pose: (%.2f, %.2f, %.2f)", rayPose.x, rayPose.y, rayPose.theta);
        pros::lcd::print(2, "Error: %.2f in, %.2f deg", distError, dTheta);
        pros::lcd::print(3, "Sensor Used: %s", useRight ? "Right" : "Left");
    }

    if (updatePose && distError > CORRECTION_THRESHOLD) {
        chassis.setPose(rayPose);
    }

    return rayPose;
}
*/
void autonSkills() { 
    //SETUP
    chassis.setPose(15,-48,90);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    left_dt.set_brake_mode(pros::MotorBrake::brake);
    right_dt.set_brake_mode(pros::MotorBrake::brake);
    //Q1
    chassis.moveToPoint(48,-48,1400,{.minSpeed=60,.earlyExitRange=8});
    chassis.turnToHeading(180,2000,{.maxSpeed=50},false);
    loaderMech.set_value(true);
    pros::delay(100);
    chassis.moveToPoint(47.5,-65,2500,{.maxSpeed=60},false);
    chassis.turnToHeading(180,500,{.maxSpeed=80});
    loaderMech.set_value(false);
    chassis.moveToPoint(48,-22,2000,{.forwards=false,.minSpeed=80});
    pros::delay(900);
    scoringBar.set_value(true);
    pros::delay(800);
    frontIntake.move(0);
    middleRollers.move(0);
    scoringRoller.move(0);
    pros::delay(200);
    scoringBar.set_value(false);
    chassis.setPose(wallDistance(false,false), -30, chassis.getPose().theta);

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
    chassis.turnToPoint(45,48,1500,{.minSpeed=60,.earlyExitRange=3});
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
    chassis.moveToPose(18,63,-90,2500,{.minSpeed=70,.earlyExitRange=5});
    chassis.turnToHeading(-85,500,{.earlyExitRange=3},false);
    scoringBar.set_value(false); 
    right_dt.move(90);
    left_dt.move(90);
    loaderMech.set_value(true);
    pros::delay(1900);
    loaderMech.set_value(false);
    left_dt.move(0);
    right_dt.move(0);
    chassis.turnToHeading(-105,1500,{.earlyExitRange=5},false);
    right_dt.move(-35);
    left_dt.move(-35);
    pros::delay(500);
    left_dt.move(0);
    right_dt.move(0);

    chassis.turnToHeading(-90,1500,{},false);
    chassis.setPose(-17,wallDistance(false,true), chassis.getPose().theta);
    pros::delay(200);
    chassis.moveToPose(-48,48,-135,3000,{.lead=-0.6,.minSpeed=70});
    chassis.turnToHeading(0,1000,{},false);
    chassis.setPose(wallDistance(false,false), chassis.getPose().y, chassis.getPose().theta);
    chassis.moveToPoint(-48,18,3000,{.forwards=false,.maxSpeed=60});
    pros::delay(500);
    scoringBar.set_value(true);
    loaderMech.set_value(true);
    pros::delay(1200);
    chassis.setPose(wallDistance(false,false), 30, chassis.getPose().theta);
    scoringBar.set_value(false);
    chassis.moveToPoint(-48,70,3000,{.maxSpeed=60});
    pros::delay(1000);
    chassis.moveToPoint(-48,22,2500,{.forwards=false,.maxSpeed=90});
    pros::delay(1300);
    scoringBar.set_value(true);
    loaderMech.set_value(false);
    pros::delay(2000);
    chassis.setPose(chassis.getPose().x, 30, chassis.getPose().theta);
    scoringBar.set_value(false); 
    chassis.moveToPoint(-48,36,1000,{.maxSpeed=85});
    pros::delay(200);
    wingMech.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    scoringBar.set_value(false);
    chassis.turnToPoint(-60,26,1500,{.maxSpeed=60});
    chassis.moveToPoint(-60,26,1500,{.minSpeed=60,.earlyExitRange=2});
    chassis.turnToHeading(180,1500);
    chassis.moveToPoint(-60,-36,3000,{.minSpeed=60,.earlyExitRange=8});
    chassis.turnToPoint(-45,-48,1500,{.minSpeed=60,.earlyExitRange=3});
    chassis.moveToPose(-45,-48,180,2000,{.maxSpeed=60});
    chassis.turnToHeading(180,1500,{.maxSpeed=80},false);
    pros::delay(300);
    loaderMech.set_value(true);
    pros::delay(300);
    chassis.setPose(wallDistance(false, true), chassis.getPose().y, chassis.getPose().theta);
    //pros::lcd::print(5, "Wall Dist: %.2f", wallDistance(false, true));
    pros::lcd::print(6, "Chassis Y: %.2f", chassis.getPose().y);
    pros::lcd::print(7, "Chassis X: %.2f", chassis.getPose().x);
    chassis.moveToPoint(-46,-70,3000,{.maxSpeed=60});
    pros::delay(1000);
    chassis.moveToPoint(-46,-22,2500,{.forwards=false,.minSpeed=80});
    pros::delay(1300);
    scoringBar.set_value(true);
    loaderMech.set_value(false);
    pros::delay(2000);
    //chassis.setPose(chassis.getPose().x, -30, chassis.getPose().theta);
    scoringBar.set_value(false);
    wingMech.set_value(true);
    chassis.moveToPose(-18,-63,90,3000,{.lead=0.5,.minSpeed=80,.earlyExitRange=3});
    chassis.turnToHeading(95,500,{.earlyExitRange=5},false);
    loaderMech.set_value(true);
    right_dt.move(127);
    left_dt.move(127);
    pros::delay(1200);
    left_dt.move(-25);
    right_dt.move(-25);
    
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



void solo_awp(){
    scoringBar.set_value(true);
    chassis.setPose(16.5,-48,90);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    left_dt.set_brake_mode(pros::MotorBrake::brake);
    right_dt.set_brake_mode(pros::MotorBrake::brake);
    //Q1    
    chassis.moveToPoint(46,-48,1400,{.minSpeed=60,.earlyExitRange=3});
    loaderMech.set_value(true);
    chassis.turnToHeading(180,700,{.minSpeed=50},false);
    chassis.setPose(wallDistance(true,false), chassis.getPose().y, chassis.getPose().theta);
    chassis.moveToPoint(48,-65,1300,{.maxSpeed=70});
    pros::delay(700);
    loaderMech.set_value(false);
    chassis.moveToPoint(48,-32,2000,{.forwards=false,.minSpeed=50});
    pros::delay(800);
    scoringBar.set_value(false);
    pros::delay(800);
    frontIntake.move(0);
    middleRollers.move(0);
    scoringRoller.move(0);
    scoringBar.set_value(true);
    chassis.moveToPoint(48,-44,2000,{.minSpeed=80,.earlyExitRange=2});
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(20);
    chassis.turnToPoint(24,-24,500,{.earlyExitRange=5});
    chassis.moveToPoint(24,-24,1500,{.minSpeed=60,.earlyExitRange=5});
    pros::delay(750);
    loaderMech.set_value(true);
    chassis.turnToHeading(-90,500,{.earlyExitRange=5},false);
    loaderMech.set_value(false);
    //chassis.setPose(chassis.getPose().x, wallDistance(true,false), chassis.getPose().theta);
    chassis.moveToPose(-19,-24.5,-90,5000,{.lead=0.3});
    pros::delay(950);
    loaderMech.set_value(true);

    chassis.turnToPoint(-3,-2,300,{.forwards=false});
    chassis.moveToPoint(-5,-6.5,1500,{.forwards=false,.maxSpeed=40});

    pros::delay(400);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    frontIntake.move(-127);
    pros::delay(170);
    scoringRoller.move(-100);
    middleRollers.move(100);
    frontIntake.move(127);
    pros::delay(1000);
    middleRollers.move(127);
    scoringRoller.move(127);
    frontIntake.move(127);

    chassis.moveToPose(-44.5,-67,180,2200,{.lead=0.4},false);
    chassis.setPose(wallDistance(true,true), chassis.getPose().y, chassis.getPose().theta);
    loaderMech.set_value(false);
    chassis.moveToPoint(-49,-20,1500,{.forwards = false,.minSpeed=70});
    pros::delay(1000);  
    scoringBar.set_value(false);
    /*
    chassis.turnToPoint(0,0,1000,{.earlyExitRange=5});
    chassis.moveToPoint(0,0,3000,{.forwards = false, .maxSpeed=50});

    chassis.moveToPose(-48,-64,180,4000,{.lead=0.3});
    loaderMech.set_value(true);
    pros::delay(300);
    chassis.moveToPoint(-48,-20,1500,{.forwards = false});
    pros::delay(1000);  
    */
}
void two_goal_LEFT() {
    // start intake
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(20);
    wingMech.set_value(true);

    chassis.moveToPoint(-16, -44, 500);

    chassis.turnToPoint(-24, -24, 500, {});
    chassis.moveToPoint(-24, -24, 3000, {.maxSpeed = 80, .minSpeed = 40});

    pros::delay(400);
    loaderMech.set_value(true);

    chassis.turnToPoint(-48, -45, 800);
    chassis.moveToPose(-48, -64, 180, 3000, {.lead = 0.35});

    pros::delay(200);

    scoringBar.set_value(true);
    chassis.moveToPoint(-48, -20, 1500, {.forwards = false});
    pros::delay(1000);

    colorsortOn = false;
    scoringRoller.move(127);
    scoringBar.set_value(false);

    chassis.moveToPoint(-48, -20, 2000, {.forwards = false});
    pros::delay(1200);

    scoringBar.set_value(true);
    scoringRoller.move(0);
    middleRollers.move(0);
    colorsortOn = true;
    frontIntake.move(0);

    chassis.moveToPoint(-48, -50, 1000);
    chassis.moveToPose(-38, -8, 180, 2500, {.forwards = false});

    chassis.setPose(16, -48, 0);
    frontIntake.move(127);
    colorSortRoller.move(127);
    middleRollers.move(127);
    scoringRoller.move(20);
    wingMech.set_value(true);

    chassis.moveToPoint(16, -44, 500);
    chassis.turnToPoint(24, -24, 500, {});
    chassis.moveToPoint(24, -24, 3000, {.maxSpeed = 80, .minSpeed = 40});
    pros::delay(400);
    loaderMech.set_value(true);
    chassis.turnToPoint(0, 0, 800,{.forwards=false});
    chassis.moveToPoint(0, 0, 2000,{.forwards=false,.maxSpeed=60});
    
    chassis.moveToPose(48, -64, 180, 4000, {.lead=0.3});

    pros::delay(200);

    scoringBar.set_value(true);
    chassis.moveToPoint(48, -20, 1500, {.forwards = false});
    pros::delay(1000);

    colorsortOn = false;
    scoringRoller.move(127);
    scoringBar.set_value(false);

    // chassis.moveToPoint(-48, -20, 2000, {.forwards = false});
    // pros::delay(1200);

    scoringBar.set_value(true);
    scoringRoller.move(0);
    middleRollers.move(0);
    colorsortOn = true;
    frontIntake.move(0);

    // chassis.moveToPoint(-48, -50, 1000);
    // chassis.moveToPose(-38, -8, 180, 2500, {.forwards = false});

    // chassis.setPose(16, -48, 0);
    // frontIntake.move(127);
    // colorSortRoller.move(127);
    // middleRollers.move(127);
    // scoringRoller.move(20);
    // wingMech.set_value(true);

    // chassis.moveToPoint(16, -44, 500);
    // chassis.turnToPoint(24, -24, 500, {});
    // chassis.moveToPoint(24, -24, 3000, {.maxSpeed = 80, .minSpeed = 40});
    // pros::delay(400);
    // loaderMech.set_value(true);
    // chassis.turnToPoint(0, 0, 800,{.forwards=false});
    // chassis.moveToPoint(0, 0, 2000,{.forwards=false,.maxSpeed=60});
    
    // chassis.moveToPose(48, -64, 180, 4000, {.lead=0.3});

    // pros::delay(200);

    // scoringBar.set_value(false);
    // chassis.moveToPoint(48, -20, 1500, {.forwards = false});
    // pros::delay(1000);

    // colorsortOn = false;
    // scoringRoller.move(127);
    // scoringBar.set_value(true);

    // chassis.moveToPoint(48, -20, 2000, {.forwards = false});
    // pros::delay(1200);

    // scoringBar.set_value(false);
    // scoringRoller.move(0);
    // middleRollers.move(0);
    // colorsortOn = true;
    // frontIntake.move(0);

    // chassis.moveToPoint(48, -50, 1000);
    // chassis.moveToPose(58, -8, 180, 2500, {.forwards = false});
} 

void two_goal_RIGHT(){
    //nothing here


};

void one_goal_left() {
    chassis.setPose(-16.5, -48, 0);

    scoringBar.set_value(true);
    frontIntake.move(127);
    colorSortRoller.move(127);
    middleRollers.move(127);
    scoringRoller.move(20);
    wingMech.set_value(false);

    chassis.moveToPose(-24, -24, -15, 3000, {.maxSpeed = 80, .minSpeed = 40});
    pros::delay(600);

    loaderMech.set_value(true);

    chassis.turnToPoint(-48, -45, 800);

    chassis.moveToPose(-47, -48, 180, 1500, {.lead = 0.3, .minSpeed = 60, .earlyExitRange = 5});

    chassis.moveToPoint(-47, -64, 1400, {.minSpeed = 60});
    pros::delay(150);

    scoringBar.set_value(true);

    chassis.moveToPoint(-48, -24, 1500, {.forwards = false});
    pros::delay(1000);

    colorsortOn = false;
    scoringRoller.move(127);
    scoringBar.set_value(false);
    pros::delay(1400);

    scoringBar.set_value(true);
    scoringRoller.move(0);
    middleRollers.move(0);
    colorsortOn = true;
    frontIntake.move(0);

    chassis.moveToPoint(-48, -50, 1000);

    chassis.moveToPose(-36, -8, 0, 2500, {.forwards = false,.lead=-0.6}, false);

    while (chassis.getPose().y < -10) {
        chassis.moveToPose(-36.5, -8, 180, 2500, {.forwards = false,.lead=-0.6});
    }
} 

void one_goal_right() {
    chassis.setPose(16.5, -48, 0);
    scoringBar.set_value(true);
    frontIntake.move(127);
    colorSortRoller.move(127);
    middleRollers.move(127);
    scoringRoller.move(20);
    wingMech.set_value(false);
    chassis.moveToPose(24, -24, 15, 3000, {.maxSpeed = 80, .minSpeed = 40});
    pros::delay(800);
    loaderMech.set_value(true);
    chassis.turnToPoint(48, -45, 800);
    chassis.moveToPose(47, -48, 180, 1500, {.lead=0.3,.minSpeed=60,.earlyExitRange=5});
    chassis.moveToPoint(45.5, -64, 1000, {.minSpeed=55});
    scoringBar.set_value(true);
    chassis.moveToPoint(47, -24, 1500, {.forwards = false});
    pros::delay(1000);
    colorsortOn = false;
    scoringRoller.move(127);
    scoringBar.set_value(false);
    pros::delay(1400);

    scoringBar.set_value(true);
    scoringRoller.move(0);
    middleRollers.move(0);
    colorsortOn = true;
    frontIntake.move(0);

    chassis.moveToPoint(48, -50, 1000);
    chassis.moveToPose(57, -8, 180, 2500, {.forwards = false},false);
    while (chassis.getPose().y < -10) {
        chassis.moveToPose(57, -8, 180, 2500, {.forwards = false});
    }
}


void turnTesting(bool isCW) {

    const int SIZE = 8;
    //int turns[SIZE] = {15, 30, 45, 60, 90, 120, 150, 180};
    int turns[SIZE] = { 30,  60, 90, 120, 180};
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
