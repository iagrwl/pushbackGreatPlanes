#include "main.h"
#include "pros/misc.h"

// write every op control task as its own function here.

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
    if (intake.get_actual_velocity() <=  0) {
      intake.move(127);
    } else {
      intake.move(0);
    }
    
  } 
}

void handleOuttakeCommands() {
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) || 
        controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2) ) 
    {
      outtake.move(0);
    } 
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) 
    {
      outtake.move(127);
    } 
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) 
    {
      outtake.move(127);
    }
}

void handleIndexerCommands() {
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) {
    if (indexer.get_actual_velocity() <=  0) {
      indexer.move(127);
    } else {
      indexer.move(0);
    }
  }
}

void rumble() {
  for (int i = 60; i > 0; i--) {
    if (i == 10) {
      controller.rumble("--");
    }
    pros::delay (1000);
  }
}