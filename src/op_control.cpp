#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "setup.hpp"

#include <fstream>
#include <string>

//STATES
//extensions
bool isScoringBarUp = false;
bool isLoaderExtended = false;
bool isWingsOut = false;

//core func
bool isIntakeOn = false;

// drive mode handler
void handleDriveMode(bool driveMode) {
  driveMode ? handleArcade() : handleTank();
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


// the return; cmd exits the loop 
void handleIOCommands() { 
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) { // if L1 is clicked then system is toggled on or off
    isIntakeOn = !isIntakeOn;
  }

  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { // when L2 is held the system reverses when let go it returns to the state of L1 toggle
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    return; // return bc its a hold
  }

  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { // when R1 is held the system runs forward with scoring bar deployed when let go returns to the state of L1 toggle
    scoringBar.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    return; // return bc its a hold
  } else { // what happens when the R1 is let go off
    scoringBar.set_value(false);
  }

  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { // when R2 is held the system runs forward with scoring roller reversed for mid scoring and when let go returns to the state of L1 toggle
    scoringBar.set_value(false);
    frontIntake.move(127);
    middleRollers.move(100);
    scoringRoller.move(-50);
    return; // return bc its a hold
  }

  if (isIntakeOn) { // if the L1 is toggled on then this passes
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
  } else { // if the L1 is toggled off then this passes
    frontIntake.move(0);
    middleRollers.move(0);
    scoringRoller.move(0);
  }
}

void telemetry() {
  std::ofstream file("/usd/log.csv", std::ios::app);
  if (!file.is_open()) return;

  // write header if file empty
  if (file.tellp() == 0)
      file << "time,x,y,theta,psi,descore?,loader?,wings?\n";

  // write one row of data
  file  << pros::millis() << ","
        << chassis.getPose().x << ","
        << chassis.getPose().y << ","
        << chassis.getPose().theta << ","
        << isScoringBarUp << ","
        << isLoaderExtended << ","
        << isWingsOut << "\n";
  file.close();
}


void handleLoaderMechCommands() { //toggle button for loader mech
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) { //if the controller recognizes a new press from the left arrow button
    isLoaderExtended = !isLoaderExtended; //flips the condition of the current state of the loader
    loaderMech.set_value(isLoaderExtended); //sets the physical state to the bool condition of the loader
  } 
}

void handleWingMechCommands() { //toggle button wing mech
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) { //if the controller recognizes a new press from the B button
    isWingsOut = !isWingsOut; //flips the condition of the current state of the wings
    wingMech.set_value(isWingsOut); //sets the physical state to the bool condition of the wings
  }
}



