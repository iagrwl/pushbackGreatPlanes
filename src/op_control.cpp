#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "setup.hpp"
#include "util.hpp"
#include <fstream>
#include <string>

// states
bool isOuttakeToggled = false;
bool OuttakeOverride = false;
bool isIntakeForward = false;
bool isHighSpeed = false;
bool isScoringBarUp = false;
bool isBlockDetected = true;
bool IntakeOverride = false;
bool isLoaderExtended = false;
bool isIntakeOn = false;

// constants
int toggle_power = 60;

// amp and rpm for stalling
double colorSortRoller_rpm = 0.0, colorSortRoller_current = 0.0;
double frontIntake_rpm = 0.0, frontIntake_current = 0.0;
double middleRollers_rpm = 0.0, middleRollers_current = 0.0;
double scoringRoller_rpm = 0.0, scoringRoller_current = 0.0;

// drivetrain storage
double leftDT_rpm[3] = {0}, leftDT_current[3] = {0};
double rightDT_rpm[3] = {0}, rightDT_current[3] = {0};

//threshold vals
double amp_threshold = 2000;
double rpm_threshold = 150;

//stall states
bool frontIntakeStall = false;
bool colorSortRollerStall = false;
bool middleRollersStall = false;
bool scoringRollerStall = false;

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
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
    isIntakeForward = !isIntakeForward;
    // Reset stall flags on toggle
    frontIntakeStall = false;
    colorSortRollerStall = false;
    middleRollersStall = false;
    scoringRollerStall = false;
    
  }
  if (scoringRollerStall){
    scoringRoller.move(20);
  }
  if (colorSortRollerStall){
    colorSortRoller.move(0);
  } 
  if (middleRollersStall){
  middleRollers.move(0);
  }
  if (isIntakeForward) {
    if (!IsColorSortEngaged)
    frontIntake.move(80);
    middleRollers.move(127);
    scoringRoller.move(127);
    if (!IsColorSortEngaged) 
    colorSortRoller.move(127);
  } 
  else {
    frontIntake.move(0);
    middleRollers.move(0);
    scoringRoller.move(0);
    colorSortRoller.move(0);
    isIntakeOn = false;
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
  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { // R2 = low score
    OuttakeOverride = true;
    scoringBar.set_value(false);
    frontIntake.move(127);
    middleRollers.move(127);
    colorSortRoller.move(127);
    scoringRoller.move(-127);
  } 
  else if (!isIntakeForward || isIntakeOn) { // when neither is pressed
    OuttakeOverride = false;
    frontIntake.move(0);
    middleRollers.move(0);
    colorSortRoller.move(0);
    scoringRoller.move(0); 
    scoringBar.set_value(false);
  }
}


void stall_checker() {
  
  initLog();
  colorSortRoller_rpm = colorSortRoller.get_actual_velocity();
  colorSortRoller_current = colorSortRoller.get_current_draw();
  frontIntake_rpm = frontIntake.get_actual_velocity();
  frontIntake_current = frontIntake.get_current_draw();
  middleRollers_rpm = middleRollers.get_actual_velocity();
  middleRollers_current = middleRollers.get_current_draw();
  scoringRoller_rpm = scoringRoller.get_actual_velocity();
  scoringRoller_current = scoringRoller.get_current_draw();
  
  //lower the amp thresh. the more sensitive 
  //higher the rpm thresh. the more sensitive
  if (OuttakeOverride == false){
    if (!scoringRollerStall){
      scoringRollerStall = (scoringRoller_rpm < 180);
      if (!middleRollersStall){
        middleRollersStall = (middleRollers_rpm < 160);
        if (!colorSortRollerStall){
          colorSortRollerStall = (colorSortRoller_rpm < 180);
          if (!frontIntakeStall)
            frontIntakeStall = (frontIntake_rpm < 30);
        }
      }
    }
  }

  pros::lcd::print(4, "RPM: %.2f", frontIntake_rpm,frontIntakeStall ? "FRONT FULL NOT STOPPING" : "");
  pros::lcd::print(5, "RPM: %.2f", colorSortRoller_rpm,colorSortRollerStall ? "----LOWER FULL" : "");
  pros::lcd::print(6, "RPM: %.2f", middleRollers_rpm, middleRollersStall ? "----MIDDLE FULL" : "");
  pros::lcd::print(7, "RPM: %.2f", scoringRoller_rpm, scoringRollerStall ? "----TOP FULL" : "");
  logData();
}

void handleLoaderMechCommands() {
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT)) {
    isLoaderExtended = !isLoaderExtended;
    LoaderMech.set_value(isLoaderExtended);
  }
}
