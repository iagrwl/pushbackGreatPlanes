#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "setup.hpp"

// states
bool isOuttakeToggled = false;
bool OuttakeOverride = false;
bool isIntakeForward = false;
bool isHighSpeed = false;
bool isScoringBarUp = false;

// constants
int block_dist = 80;
int bottom_block_dist = block_dist + 30;
int toggle_power = 60;

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
bool isBlockThere(pros::Distance& currDist) {
  if (currDist.get_distance() <= block_dist) {
    pros::delay(500);
    return currDist.get_distance() <= block_dist;
  }
  return false;
}

pros::Task* intakeOn = nullptr;

// intake spinnnner
void spinIntake() {
  frontIntake.move(127);
  middleRollers.move(127);
  colorSortRoller.move(127);
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
    pros::lcd::print(3, "no bottom block");
    pros::delay(10);
  }

  frontIntake.move(0);
  pros::lcd::print(4, "bottom block");
}

// intake control (L1 toggle)
void handleIntakeCommands() {
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
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
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    return; // avoid L2 interfering w intake
  }

  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { // R1 = score forward
    scoringBar.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    colorSortRoller.move(127);
    scoringRoller.move(127);
  } 

  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { // R2 = reverse score
    scoringBar.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    colorSortRoller.move(127);
    scoringRoller.move(-127);
  } 
  
  else { // when neither is pressed
    scoringBar.set_value(false);
    frontIntake.move(0);
    middleRollers.move(0);
    colorSortRoller.move(0);
    scoringRoller.move(0); 
  }
}