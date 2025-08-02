#include "main.h"
#include "pros/misc.h"
#include "setup.hpp"

bool isIndexerOn = false;
bool isFirstTimePressed = true;
bool outtakespin = false;
bool isOuttakeToggled = false; // toggle variable for L1

// write every driver control task as its own function here.

void handleArcade() {
  int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
  // move the robot
  chassis.arcade(leftY, rightX);
}

void handleTank() {
  int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
  // move the robot
  chassis.tank(leftY, rightY);
}

void handleDriveMode(bool isArcade) {
  isArcade ? handleArcade() : handleTank();
}

void handleIntakeCommands() {
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
    isOuttakeToggled = !isOuttakeToggled;

    if (isOuttakeToggled) {
      intake.move(127);
      outtake.move(127);
    } else {
      intake.move(0);
      outtake.move(0);
    }
  }
}

void handleOuttakeCommands() {
  bool r1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
  bool r2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

  if (!r1 && !r2 && !isOuttakeToggled) {
    outtake.move(0);
    indexer.move(0);
    isIndexerOn = false;
  } 
  else if (r1) {
    outtake.move(127);
    indexer.move(127);
    isIndexerOn = true;
  } 
  else if (r2) {
    outtake.move(-127);
    indexer.move(127);
    isIndexerOn = true;
  }
}

bool isLoaderExtended = false;
void handleLoaderMechCommands() {
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
    !isLoaderExtended ? isLoaderExtended = true : isLoaderExtended = false;
    loaderMech.set_value(isLoaderExtended);
  }
}

void rumble() {
  for (int i = 60; i > 0; i--) {
    if (i == 10) {
      controller.rumble("--");
    }
    pros::delay(1000);
  }
}