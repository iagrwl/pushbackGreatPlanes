#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "setup.hpp"
#include "op_control.hpp"
#include <fstream>
#include <string>
#include "colorSort.hpp"


//STATES
//extensions
bool openGate = true;
bool isLoaderExtended = false;
bool isWingsOut = true;
bool DPDescoreToggle = false;
//core func
bool isIntakeOn = false;
bool shouldSC = false;
//# of extensions
int LE = 0; // loader
int DE = 0; // descore mech
int WE = 0; // wing mech
int PE = 0;  // park mech
//amount of PSI used for each system
int LP = 2; // loader
int DP = 2; // descore mech
int WP = 2; // wing mech
int DD = 2; // double park & descore

int usedPSI = 0; // the amount of psi used by the robot
int PSI = 100; // the amount of psi left over for the double park mechanism to use


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
  // if L1 is clicked then system is toggled on or off 
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) { 
    isIntakeOn = !isIntakeOn;
  }

  // when L2 is held the system reverses when let go it returns to the state of L1 toggle
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { 
    frontIntake.move(-110);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    return; // return bc its a hold
  }

  // detect a new R1 press
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
    DE++;
  }

  // hold behavior while R1 is held
  // when R1 is held the system runs forward with scoring bar deployed when let 
  // go returns to the state of L1 toggle
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { 
    scoringGate.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
  } else { // what happens when the R1 is let go off
    scoringGate.set_value(true);
    
  }
  bool r1_active = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);

  // when R2 is held the system runs forward with scoring roller reversed 
  // for mid scoring and when let go returns to the state of L1 toggle
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { 
    colorsortOn=false;
    frontIntake.move(100);
    middleRollers.move(100);
    scoringRoller.move(-70); 
  
    return; // return bc its a hold
  }

  // base intake toggle only applies when r1 and r2 are not being held
  if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) &&
      !controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      if (isIntakeOn) {
        frontIntake.move(127);
        middleRollers.move(127);
        scoringRoller.move(90);
      } else {
        frontIntake.move(0);
        middleRollers.move(0);
        scoringRoller.move(0);
      }
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
        << openGate << ","
        << isLoaderExtended << ","
        << isWingsOut << "\n";
  file.close();
}


void handleLoaderMechCommands() { //toggle button for loader mech
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) { //if the controller recognizes a new press from the left arrow button
    isLoaderExtended = !isLoaderExtended; //flips the condition of the current state of the loader
    loaderMech.set_value(isLoaderExtended); //sets the physical state to the bool condition of the loader
    if (isLoaderExtended == false){
      LE++;
    }
  } 
}

void handleWingMechCommands() { //toggle button wing mech
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) { //if the controller recognizes a new press from the B button
    isWingsOut = !isWingsOut; //flips the condition of the current state of the wings
    wingMech.set_value(isWingsOut); //sets the physical state to the bool condition of the wings
    if (isWingsOut == false){
      WE++;
    }
  }
}

void toggleCS() { // toggle on off
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) { //if the controller recognizes a new press from the B button
    colorsortOn = !colorsortOn; //flips the condition of the current state of the wings

  }
}

void switchCS() { // switche color
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) { //if the controller recognizes a new press from the B button
    isRed = !isRed; //flips the condition of the current state of the wings

  }
}

void handleDoublePark() {
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) { //if the controller recognizes a new press from the B button
    DPDescoreToggle = !DPDescoreToggle; //flips the condition of the current state of the wings
    parkMech.set_value(DPDescoreToggle); //sets the physical state to the bool condition of the wings
    if (DPDescoreToggle == false){
      PE++;
    }
  }
}


void updatePSI(){
  usedPSI = (LE*LP)+(DE*DP)+(WE*WP)+(PE*DD);
  PSI = 100-usedPSI;
}



