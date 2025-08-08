#include "main.h"
#include "pros/misc.h"
#include "setup.hpp"

bool isIndexerOn = false;
bool isFirstTimePressed = true;
bool isOuttakeToggled = false;
bool OuttakeOverride = false;
bool isIntakeForward = true;


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


void handleIntakeCommands () {
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
    isOuttakeToggled = !isOuttakeToggled;

    if (isOuttakeToggled) {
      intake.move(127);
      if (!OuttakeOverride) outtake.move(127);
      isIntakeForward = true;
    } else {
      intake.move(0);
      if (!OuttakeOverride) outtake.move(0);
      isIntakeForward = false;
    }
  }
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
    isOuttakeToggled = !isOuttakeToggled;
    isIndexerOn = false;
    indexer.move(-127);
    outtake.move(-80);
    intake.move(-80);
    isIntakeForward = false;
  } else if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && !isIntakeForward) {
    isIndexerOn = true;
    intake.move(0);
  }

}

void handleOuttakeCommands() {
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
    indexer.move(127);
    isIndexerOn = true;
    outtake.move(127);
    OuttakeOverride = true;
  } 
  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    indexer.move(127);
    isIndexerOn = true;
    outtake.move(-127);
    OuttakeOverride = true;
  } 
  else {

    if (isIndexerOn) indexer.move(0);
    isIndexerOn = false;

    if (isOuttakeToggled) {
      outtake.move(127);
    } else {
      outtake.move(0);
    }

    OuttakeOverride = false;
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