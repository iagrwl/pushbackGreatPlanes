#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "setup.hpp"

#include <fstream>
#include <string>

//STATES
//stalling
bool frontIntakeStall = false;
bool colorSortRollerStall = false;
bool middleRollersStall = false;
bool scoringRollerStall = false;
//extensions
bool isScoringBarUp = false;
bool isLoaderExtended = false;
bool isWingsOut = false;
bool isParkDown = false;
//core func
bool isIntakeOn = false;
bool shouldSC = false;
//other
bool isBlockDetected = true;
bool isHighSpeed = false;
bool checkpark = false;

//amp rpm vars
double colorSortRoller_rpm = 0.0, colorSortRoller_current = 0.0;
double frontIntake_rpm = 0.0, frontIntake_current = 0.0;
double middleRollers_rpm = 0.0, middleRollers_current = 0.0;
double scoringRoller_rpm = 0.0, scoringRoller_current = 0.0;

//drivetrain storage
double leftDT_rpm[3] = {0}, leftDT_current[3] = {0};
double rightDT_rpm[3] = {0}, rightDT_current[3] = {0};
pros::Mutex log_mutex;
std::ofstream logFile;
bool logInitialized = false;

void initLog() {
  // if (!logInitialized) {
  //   logFile.open("/usd/stall_log.csv", std::ios::out | std::ios::trunc);
  //   if (logFile.is_open()) {
  //     logFile << "time_ms,"
  //             << "frontIntake_rpm,frontIntake_current,frontIntakeStall,"
  //             << "colorSortRoller_rpm,colorSortRoller_current,colorSortRollerStall,"
  //             << "middleRollers_rpm,middleRollers_current,middleRollersStall,"
  //             << "scoringRoller_rpm,scoringRoller_current,scoringRollerStall,"
  //             // drivetrain motors
  //             << "leftDT_m7_rpm,leftDT_m7_amp,"
  //             << "leftDT_m6_rpm,leftDT_m6_amp,"
  //             << "leftDT_m5_rpm,leftDT_m5_amp,"
  //             << "rightDT_m14_rpm,rightDT_m14_amp,"
  //             << "rightDT_m15_rpm,rightDT_m15_amp,"
  //             << "rightDT_m16_rpm,rightDT_m16_amp"
  //             << std::endl;
  //     logInitialized = true;
  //   }
  // }
}

void logData() {
  // if (logInitialized && logFile.is_open()) {
  //   log_mutex.take();

  //   // collect drivetrain data
  //   leftDT_rpm[0] = pros::Motor(-7).get_actual_velocity();
  //   leftDT_current[0] = pros::Motor(-7).get_current_draw();
  //   leftDT_rpm[1] = pros::Motor(-6).get_actual_velocity();
  //   leftDT_current[1] = pros::Motor(-6).get_current_draw();
  //   leftDT_rpm[2] = pros::Motor(5).get_actual_velocity();
  //   leftDT_current[2] = pros::Motor(5).get_current_draw();

  //   rightDT_rpm[0] = pros::Motor(14).get_actual_velocity();
  //   rightDT_current[0] = pros::Motor(14).get_current_draw();
  //   rightDT_rpm[1] = pros::Motor(15).get_actual_velocity();
  //   rightDT_current[1] = pros::Motor(15).get_current_draw();
  //   rightDT_rpm[2] = pros::Motor(-16).get_actual_velocity();
  //   rightDT_current[2] = pros::Motor(-16).get_current_draw();

  //   logFile << pros::millis() << ","
  //           << frontIntake_rpm << "," << frontIntake_current << "," << frontIntakeStall << ","
  //           << colorSortRoller_rpm << "," << colorSortRoller_current << "," << colorSortRollerStall << ","
  //           << middleRollers_rpm << "," << middleRollers_current << "," << middleRollersStall << ","
  //           << scoringRoller_rpm << "," << scoringRoller_current << "," << scoringRollerStall << ","
  //           // drivetrain
  //           << leftDT_rpm[0] << "," << leftDT_current[0] << ","
  //           << leftDT_rpm[1] << "," << leftDT_current[1] << ","
  //           << leftDT_rpm[2] << "," << leftDT_current[2] << ","
  //           << rightDT_rpm[0] << "," << rightDT_current[0] << ","
  //           << rightDT_rpm[1] << "," << rightDT_current[1] << ","
  //           << rightDT_rpm[2] << "," << rightDT_current[2]
  //           << std::endl;

  //   log_mutex.give();
  // }
}

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
    shouldSC = false;
    frontIntake.move(-127);
    middleRollers.move(-127);
    scoringRoller.move(-127);
    return;
  }

  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { // when R1 is held the system runs forward with scoring bar deployed when let go returns to the state of L1 toggle
    shouldSC = false;
    scoringBar.set_value(true);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    return;
  } else { // what happens when the R1 is let go off
    scoringBar.set_value(false);
  }

  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { // when R2 is held the system runs forward with scoring roller reversed for mid scoring and when let go returns to the state of L1 toggle
    shouldSC = false;
    scoringBar.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(-60);
    return;
  }

  if (isIntakeOn) { // if the L1 is toggled on then this passes
    shouldSC = true;
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    if (middleRollersStall) {
      middleRollers.move(20);
    } else {
      middleRollers.move(127);
    }
    if (scoringRollerStall) {
      scoringRoller.move(20);
    } else {
      scoringRoller.move(127);
    }
  } else { // if the L1 is toggled off then this passes
    shouldSC = false;
    frontIntake.move(0);
    middleRollers.move(0);
    scoringRoller.move(0);
  }
}

void stall_checker() {
  initLog(); //initalizes the sd card for data input
  //updates variables every time the function is called
  colorSortRoller_rpm = colorSortRoller.get_actual_velocity();
  colorSortRoller_current = colorSortRoller.get_current_draw();
  frontIntake_rpm = frontIntake.get_actual_velocity();
  frontIntake_current = frontIntake.get_current_draw();
  middleRollers_rpm = middleRollers.get_actual_velocity();
  middleRollers_current = middleRollers.get_current_draw();
  scoringRoller_rpm = scoringRoller.get_actual_velocity();
  scoringRoller_current = scoringRoller.get_current_draw();

  //every time the intake sequence is toggled these flaggers reset
  //higher the rpm thresh. the more sensitive
  if (shouldSC){ //if the stall check code is permitted to run, set by other parts in the code this passes
    if (scoringRoller_rpm < 20){
      scoringRollerStall = true;
    }
    else if (scoringRoller_rpm > 40){
      scoringRollerStall = false;
    }
    if (middleRollers_rpm < 20){
    middleRollersStall = true;
    } 
    else if (middleRollers_rpm > 40){
      middleRollersStall = false;
    } 
  }                                                                                                                   
  //displays the rpm and the stall state of each roller section on the brains 4,5,SIX, SEVENNN lines of the screen (o)(o)
  pros::lcd::print(4, "RPM: %.2f %s", frontIntake_rpm, frontIntakeStall ? "FRONT FULL" : "");
  pros::lcd::print(6, "RPM: %.2f %s", middleRollers_rpm, middleRollersStall ? "MIDDLE FULL" : "");
  pros::lcd::print(7, "RPM: %.2f %s", scoringRoller_rpm, scoringRollerStall ? "TOP FULL" : "");
  logData(); //logs the data onto the sd card for data analysis
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

void handleParkCommands() { //toggle button for park mech
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) { //if the controller recognizes a new press from the down arrow button
    isParkDown = !isParkDown; //flips the condition of the current state of the park bool
    parkMech.set_value(isParkDown); //sets the physical state to the bool condition of the park sys
  }
}

//macros

