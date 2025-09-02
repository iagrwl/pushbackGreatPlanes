#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "setup.hpp"
#include "util.hpp"

// states
bool isOuttakeToggled = false;
bool OuttakeOverride = false;
bool isIntakeForward = false;
bool isHighSpeed = false;
bool isScoringBarUp = false;
bool isBlockDetected = true;


// constants

int toggle_power = 60;

// amp and rpm for stalling
double colorSortRoller_rpm = 0.0, colorSortRoller_current = 0.0;
double frontIntake_rpm = 0.0, frontIntake_current = 0.0;
double middleRollers_rpm = 0.0, middleRollers_current = 0.0;
double scoringRoller_rpm = 0.0, scoringRoller_current = 0.0;

//threshold vals
double amp_threshold = 2000;
double rpm_threshold = 70.0;

//stall states
bool frontIntakeStall = false;
bool colorSortRollerStall = false;
bool middleRollersStall = false;
bool scoringRollerStall = false;



// dynamic switching vars
bool DriveMode = true;                   // true = arcade, false = tank
int DynamicDriveSwitchClickCount = 0;    // tracks how many times toggle combo clicked
uint32_t lastDynamicSwitchClickTime = 0; // stores last time the combo was pressed



// drive mode handler
void handleDriveMode(bool isArcade) {
  isArcade ? handleArcade() : handleTank();
}

void handleArcade() {
  int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
  chassis.arcade(leftY, rightX); // move the robot
}

void handleTank() {
  int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  chassis.tank(leftY, rightY); // move the robot
}

// lets driver switch drive modes (x + right arrow 3x in 1 sec)
void handleDynamicDriveMode() {
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) &&
      controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
    
    uint32_t now = pros::millis(); // current prog time
    if (now - lastDynamicSwitchClickTime <= 1000) {
      DynamicDriveSwitchClickCount++; // add to combo count
    } else {
      DynamicDriveSwitchClickCount = 1; // reset combo
    }

    lastDynamicSwitchClickTime = now;

    if (DynamicDriveSwitchClickCount >= 3) {
      DriveMode = !DriveMode;              // flip drive mode
      DynamicDriveSwitchClickCount = 0;    // reset combo count
      controller.rumble(".");              // notify driver
      DriveMode ? handleArcade() : handleTank();
    }
  }
}

// scoring bar toggle
void toggleScoringBar() {
  isScoringBarUp = !isScoringBarUp;
  scoringBar.set_value(isScoringBarUp);
}

// block detection helper

void spinIntake() {
  if (!IsColorSortEngaged) frontIntake.move(127);
  middleRollers.move(127);
  if (!IsColorSortEngaged) colorSortRoller.move(80);
  scoringRoller.move(127);
  pros::delay(50);
  while (!isBlockThere(bottomDistance)) {
    if (isBlockThere(topDistance) && !isBlockThere(middleDistance)) {
      scoringRoller.move(50);
    }
    if (isBlockThere(middleDistance) && isBlockThere(topDistance)) {
      middleRollers.move(0);
      scoringRoller.move(0);
    }
    if(colorSortRoller.get_actual_velocity() < 5 && isBlockThere(middleDistance)) {
      colorSortRoller.move(0);
    }
    pros::lcd::print(3, "no bottom block");
    pros::delay(10);
  }
  if (!IsColorSortEngaged) frontIntake.move(0);
  pros::lcd::print(4, "bottom block");
}

pros::Task* intakeOn = nullptr;
// intake control (L1 toggle)
void handleIntakeCommands() {
  /*if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
    isIntakeForward = !isIntakeForward;
    // Reset stall flags on toggle
    frontIntakeStall = false;
    colorSortRollerStall = false;
    middleRollersStall = false;
    scoringRollerStall = false;
  }
  if (isIntakeForward) {
    if (!IsColorSortEngaged) frontIntake.move(80);
    middleRollers.move(127);
    scoringRoller.move(127);
    if (!IsColorSortEngaged) colorSortRoller.move(127);
  } else {
    frontIntake.move(0);
    middleRollers.move(0);
    scoringRoller.move(0);
    colorSortRoller.move(0);
  }
  if (frontIntakeStall){
    frontIntake.move(0);
  }
  if (colorSortRollerStall){
    colorSortRoller.move(0);
  }
  if (middleRollersStall){
    middleRollers.move(0);
  }
  if (scoringRollerStall){
    scoringRoller.move(0);
  }*/
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) { // checks for new press from the left top trigger buttons 
    if (!isIntakeForward) {
      intakeOn = new pros::Task(&spinIntake);
      isIntakeForward = true;
    } else {
      isIntakeForward = false;
      frontIntake.move(0);
      middleRollers.move(0);
      scoringRoller.move(0);
      colorSortRoller.move(0);
      pros::lcd::print(5, "stop");
    }
  }
}

// outtake control (R1 / R2)
void handleOuttakeCommands() {
  

  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { // R1 = score forward
    OuttakeOverride = true;
    scoringBar.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    colorSortRoller.move(127);
    scoringRoller.move(127);
    
  } 

  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { // R2 = reverse score
    OuttakeOverride = true;
    scoringBar.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    colorSortRoller.move(127);
    scoringRoller.move(-127);
    
  } 
  
  else if (!isIntakeForward) { // when neither is pressed
    OuttakeOverride = false;
    scoringBar.set_value(false);
    frontIntake.move(0);
    middleRollers.move(0);
    colorSortRoller.move(0);
    scoringRoller.move(0); 
  }
}


void stall_checker() {
  colorSortRoller_rpm = colorSortRoller.get_actual_velocity();
  colorSortRoller_current = colorSortRoller.get_current_draw();
  frontIntake_rpm = frontIntake.get_actual_velocity();
  frontIntake_current = frontIntake.get_current_draw();
  middleRollers_rpm = middleRollers.get_actual_velocity();
  middleRollers_current = middleRollers.get_current_draw();
  scoringRoller_rpm = scoringRoller.get_actual_velocity();
  scoringRoller_current = scoringRoller.get_current_draw();
  
  if (OuttakeOverride == false){
    if (!frontIntakeStall)
    frontIntakeStall = (frontIntake_current > 2500 && frontIntake_rpm < 220);
    if (!colorSortRollerStall)
      colorSortRollerStall = (colorSortRoller_current > amp_threshold && colorSortRoller_rpm < 175);
    if (!middleRollersStall)
      middleRollersStall = (middleRollers_current > amp_threshold && middleRollers_rpm < rpm_threshold);
    if (!scoringRollerStall)
      scoringRollerStall = (scoringRoller_current > 1000 && scoringRoller_rpm < 160);
  }
  

  
  pros::lcd::print(4, "RPM: %.2f, A: %.2f%s", frontIntake_rpm, frontIntake_current,
    frontIntakeStall ? "FRONT FULL" : "");
  pros::lcd::print(5, "RPM: %.2f, A: %.2f%s", colorSortRoller_rpm, colorSortRoller_current,
    colorSortRollerStall ? "LOWER FULL" : "");
  pros::lcd::print(6, "RPM: %.2f, A: %.2f%s", middleRollers_rpm, middleRollers_current,
    middleRollersStall ? "MIDDLE FULL" : "");
  pros::lcd::print(7, "RPM: %.2f, A: %.2f%s", scoringRoller_rpm, scoringRoller_current,
    scoringRollerStall ? "TOP FULL" : "");
}