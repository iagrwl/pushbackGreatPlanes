#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "setup.hpp"
#include "util.hpp"
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
//core func
bool isIntakeOn = false;
bool isOuttakeOn = false;
bool shouldSC = false; // should stall check? bool
//other
bool isBlockDetected = true;
bool isHighSpeed = false;

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
  if (!logInitialized) {
    logFile.open("/usd/stall_log.csv", std::ios::out | std::ios::trunc);
    if (logFile.is_open()) {
      logFile << "time_ms,"
              << "frontIntake_rpm,frontIntake_current,frontIntakeStall,"
              << "colorSortRoller_rpm,colorSortRoller_current,colorSortRollerStall,"
              << "middleRollers_rpm,middleRollers_current,middleRollersStall,"
              << "scoringRoller_rpm,scoringRoller_current,scoringRollerStall,"
              // drivetrain motors
              << "leftDT_m7_rpm,leftDT_m7_amp,"
              << "leftDT_m6_rpm,leftDT_m6_amp,"
              << "leftDT_m5_rpm,leftDT_m5_amp,"
              << "rightDT_m14_rpm,rightDT_m14_amp,"
              << "rightDT_m15_rpm,rightDT_m15_amp,"
              << "rightDT_m16_rpm,rightDT_m16_amp"
              << std::endl;
      logInitialized = true;
    }
  }
}

void logData() {
  if (logInitialized && logFile.is_open()) {
    log_mutex.take();

    // collect drivetrain data
    leftDT_rpm[0] = pros::Motor(-7).get_actual_velocity();
    leftDT_current[0] = pros::Motor(-7).get_current_draw();
    leftDT_rpm[1] = pros::Motor(-6).get_actual_velocity();
    leftDT_current[1] = pros::Motor(-6).get_current_draw();
    leftDT_rpm[2] = pros::Motor(5).get_actual_velocity();
    leftDT_current[2] = pros::Motor(5).get_current_draw();

    rightDT_rpm[0] = pros::Motor(14).get_actual_velocity();
    rightDT_current[0] = pros::Motor(14).get_current_draw();
    rightDT_rpm[1] = pros::Motor(15).get_actual_velocity();
    rightDT_current[1] = pros::Motor(15).get_current_draw();
    rightDT_rpm[2] = pros::Motor(-16).get_actual_velocity();
    rightDT_current[2] = pros::Motor(-16).get_current_draw();

    logFile << pros::millis() << ","
            << frontIntake_rpm << "," << frontIntake_current << "," << frontIntakeStall << ","
            << colorSortRoller_rpm << "," << colorSortRoller_current << "," << colorSortRollerStall << ","
            << middleRollers_rpm << "," << middleRollers_current << "," << middleRollersStall << ","
            << scoringRoller_rpm << "," << scoringRoller_current << "," << scoringRollerStall << ","
            // drivetrain
            << leftDT_rpm[0] << "," << leftDT_current[0] << ","
            << leftDT_rpm[1] << "," << leftDT_current[1] << ","
            << leftDT_rpm[2] << "," << leftDT_current[2] << ","
            << rightDT_rpm[0] << "," << rightDT_current[0] << ","
            << rightDT_rpm[1] << "," << rightDT_current[1] << ","
            << rightDT_rpm[2] << "," << rightDT_current[2]
            << std::endl;

    log_mutex.give();
  }
}

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

void spinIntake() {
  // if (!IsColorSortEngaged) 
  // frontIntake.move(127);
  // middleRollers.move(127);
  // if (!IsColorSortEngaged) 
  // colorSortRoller.move(80);
  // scoringRoller.move(127);
  // pros::delay(50);
  // while (!isBlockThere(bottomDistance)) {
  //   if (isBlockThere(topDistance) && !isBlockThere(middleDistance)) {
  //     scoringRoller.move(50);
  //   }

  //   if (isBlockThere(middleDistance) && isBlockThere(topDistance)) {
  //     middleRollers.move(0);
  //     scoringRoller.move(0);
  //   }

  //   if(colorSortRoller.get_actual_velocity() < 5 && isBlockThere(middleDistance)) {
  //     colorSortRoller.move(0);
  //   }

  //   pros::lcd::print(3, "no bottom block");
  //   pros::delay(10);
  // }
  // if (!IsColorSortEngaged)
  // frontIntake.move(0);
  // pros::lcd::print(4, "bottom block");
}

//pros::Task* intakeOn = nullptr;
// intake control (L1 toggle)
void handleIOCommands() {
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) { //if a new press of the top left trigger button is registered
    if (!isIntakeOn){ //passes if the intake is off
      //spins motors
      frontIntake.move(127);
      colorSortRoller.move(127);
      middleRollers.move(127);
      scoringRoller.move(127);
      //sets flags
      isIntakeOn = true; //sets the intake as on
      shouldSC = true; //allows the stall code to run
      //staller
      if (scoringRollerStall){ //if the scoring roller is marked as stalling this passes
        scoringRoller.move(10); //reduce speed to idle to prevent motor heating but keep blocks up and tensioned
      }
      else if (!scoringRollerStall){ //if the scoring roller isnt marked as stalling this passes
        scoringRoller.move(127); //returns the scoring roller back to running stage
      }
      //similar logic below

      if (middleRollersStall){
        middleRollers.move(0);
      }
      else if (!middleRollersStall){
        middleRollers.move(127);
      }

      if (colorSortRollerStall){
        colorSortRoller.move(0);
      }
      else if (!colorSortRollerStall){
        colorSortRoller.move(127);
      }
    }
    else if (isIntakeOn){ //if the intake is on then this passes
      //stops motors
      frontIntake.move(0);
      colorSortRoller.move(0);
      middleRollers.move(0);
      scoringRoller.move(0);
      isIntakeOn = false; //sets the intake to off
      shouldSC = false; //tells the stall check code to turn off
    }
  }

  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){ //if the top right trigger button is HELD this passes
    scoringBar.set_value(true); //sets the scoringbar/descore mech to push up to allow scoring into high goal
    frontIntake.move(127);
    colorSortRoller.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
    isOuttakeOn = true; //marks the outtake as on
    shouldSC = false; //tells the stall code to bypass to allow clean scoring
  }
  else if (isOuttakeOn){ //if the top right trigger button is let go of this passes
    scoringBar.set_value(false); //the scoring bar is dropped to allow for descoring
    //motors are shut off after the scoring sequence of intaking (L1 toggle) and the R1 or R2 combination if pressed
    frontIntake.move(0);
    colorSortRoller.move(0);
    middleRollers.move(0);
    scoringRoller.move(0);
    isOuttakeOn = false; //marks the outtake as off
    shouldSC = false; //tells the stall check code to turn off
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
    if (colorSortRoller_rpm < 10){ //if the rollers' rpm is below 20 the roller is marked as stalling
      colorSortRollerStall = true; //the roller is marked as stalling
    } 
    else if (colorSortRoller_rpm > 40){ //the roller has an oppurtuinity to recovery itself by having a min rpm of 50+ then it is given power again
      colorSortRollerStall = false; //the roller is marked as running
    }
    //similar logic below
    if (middleRollers_rpm < 10){
      middleRollersStall = true;
    } 
    else if (middleRollers_rpm > 40){
      middleRollersStall = false;
    }

    if (scoringRoller_rpm < 10){
      scoringRollerStall = true;
    }
    else if (scoringRoller_rpm > 40){
      scoringRollerStall = false;
    }
    
  }                                                                                                                   
  //displays the rpm and the stall state of each roller section on the brains 4,5,SIX, SEVENNN lines of the screen (o)(o)
  pros::lcd::print(4, "RPM: %.2f", frontIntake_rpm,frontIntakeStall ? " FRONT FULL" : "");
  pros::lcd::print(5, "RPM: %.2f", colorSortRoller_rpm,colorSortRollerStall ? " LOWER FULL" : "");
  pros::lcd::print(6, "RPM: %.2f", middleRollers_rpm, middleRollersStall ? " MIDDLE FULL" : "");
  pros::lcd::print(7, "RPM: %.2f", scoringRoller_rpm, scoringRollerStall ? " TOP FULL" : "");
  logData(); //logs the data onto the sd card for data analysis
}

void handleLoaderMechCommands() { //toggle button for loader mech
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) { //if the controller recognizes a new press from the left arrow button
    isLoaderExtended = !isLoaderExtended; //flips the condition of the current state of the loader
    loaderMech.set_value(isLoaderExtended); //sets the physical state to the bool condition of the loader
  }
}
