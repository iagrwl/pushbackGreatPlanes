#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "setup.hpp"
#include "op_control.hpp"
#include "colorSort.hpp"
#include <fstream>
#include <string>


//STATES
//extensions
bool openGate = true;
bool isLoaderExtended = false;
bool isWingsOut = true;
bool isDescoreOut = false;
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

void handleIOCommands() {
  const bool colorPriority = isColorPriority;
  // Non-blocking mid-goal reverse timing for R2 (keeps opcontrol responsive).
  static bool r2WasHeld = false;
  static int32_t r2ReverseUntilMs = 0;

  // if L1 is clicked then system is toggled on or off 
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) { 
    isIntakeOn = !isIntakeOn;
  }

  // when L2 is held the system reverses when let go it returns to the state of L1 toggle
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { 
    // L2 overrides R2; clear R2 hold state so a fresh hold retriggers the timer.
    r2WasHeld = false;
    frontIntake.move(-100);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    pistake.set_value(true);
    return; // return bc its a hold
  }

  pistake.set_value(false);

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


  const bool r2Held = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
  if (r2Held && !r2WasHeld) {
    // start window
    r2ReverseUntilMs = pros::millis() + 750;
  }
  r2WasHeld = r2Held;

  if (r2Held) { 
    const bool reverseWindow = pros::millis() < r2ReverseUntilMs;
    if (reverseWindow) {
      // first burst for 750ms
      frontIntake.move(-127);
      middleRollers.move(-127);
      scoringRoller.move(-127);
    } else {
      // post burst after above
      frontIntake.move(127);
      middleRollers.move(55);
      scoringRoller.move(-30);
    }
    descoreMech.set_value(false);
    return; // return bc its a hold
  }

  descoreMech.set_value(true);

  
  if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) &&
      !controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      if (isIntakeOn) {
        frontIntake.move(127);
        middleRollers.move(115);
        scoringRoller.move(127);
      } else {
        frontIntake.move(0);
        middleRollers.move(0);
        scoringRoller.move(0);
      }
  }

  // Color-sort takes control of scoring roller while ejecting,
  // but still allow L1/R1/R2 state updates above.
  if (colorPriority &&
      !controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1) &&
      !controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
    pistake.set_value(false);
    frontIntake.move(0);
    middleRollers.move(0);
    scoringRoller.move(-127);
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
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) { 
    //if the controller recognizes a new press from the left arrow button
    isLoaderExtended = !isLoaderExtended; 
    //flips the condition of the current state of the loader
    loaderMech.set_value(isLoaderExtended); 
    //sets the physical state to the bool condition of the loader
    if (isLoaderExtended == false){
      LE++;
    }
  } 
}

void handleWingMechCommands() { //toggle button wing mech
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) { 
    //if the controller recognizes a new press from the B button
    isWingsOut = !isWingsOut; 
    //flips the condition of the current state of the wings
    wingMech.set_value(isWingsOut); 
    //sets the physical state to the bool condition of the wings
    if (isWingsOut == false){
      WE++;
    }
  }
}



void handleDoublePark() {
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) { //if the controller recognizes a new press from the B button
    DPDescoreToggle = !DPDescoreToggle; //flips the condition of the current state of the wings
    parkMech.set_value(DPDescoreToggle); //sets the physical state to the bool condition of the wings
  }
}

void handleDescoreMechCommands() { //toggle button wing mech
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) { 
    isDescoreOut = !isDescoreOut; 

    descoreMech.set_value(isDescoreOut); 
  }
}


// void handleQuickWing() {
//   if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
//     chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
//     left_dt.move(100);
//     right_dt.move(100);
//     pros::delay(170);
//     left_dt.brake();
//     right_dt.brake();
//     left_dt.move(0);
//     right_dt.move(0);
//     pros::delay(100);
//     chassis.turnToHeading(chassis.getPose().theta+ 38,200);
//     pros::delay(200);
//     left_dt.brake();
//     right_dt.brake();
//     pros::delay(200);
//     left_dt.move(-100);
//     right_dt.move(-100);
//     pros::delay(200);
//     left_dt.brake();
//     right_dt.brake();
//     left_dt.move(0);
//     right_dt.move(0);
//     chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

//   }
// }

void intakeAutoStopping() {
}

void updatePSI(){
  usedPSI = (LE*LP)+(DE*DP)+(WE*WP)+(PE*DD);
  PSI = 100-usedPSI;
}
