#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "setup.hpp"

//states
bool isOuttakeToggled = false;
bool OuttakeOverride = false;
bool isIntakeForward = false;
bool isHighSpeed = false;
bool isScoringBarUp = false;

//constants
int block_dist = 80;
int bottom_block_dist = block_dist + 30;
int toggle_power = 60;

//dynamic switching vars
bool DriveMode = true;                   // true = arcade, false = tank
int DynamicDriveSwitchClickCount = 0;    // tracks how many times toggle combo clicked
uint32_t lastDynamicSwitchClickTime = 0; // stores last time the combo was pressed

//temps
double FI_temp = 0;
double MR_temp = 0;
double CSR_temp = 0;
double SR_temp = 0;

//amps
double FI_amps = 0;
double MR_amps = 0;
double CSR_amps = 0;
double SR_amps = 0;

//func to make pulling temps easy
double getTempF(pros::Motor& m) {
    return m.get_temperature() * 9.0 / 5.0 + 32;
}

//acts as a refresher func for temps
void pullTempsTask(void* param) {
    while (true) {
        FI_temp  = getTempF(frontIntake);
        MR_temp  = getTempF(middleRollers);
        CSR_temp = getTempF(colorSortRoller);
        SR_temp  = getTempF(scoringRoller);

        pros::delay(100);
    }
}

//func to make pulling amps easy
double getAmps(pros::Motor& m) {
    return m.get_current_draw(); 
}

//acts as a refresher func for amps
void pullAmpsTask(void* param) {
    while (true) {
        FI_amps  = getAmps(frontIntake);
        MR_amps  = getAmps(middleRollers);
        CSR_amps = getAmps(colorSortRoller);
        SR_amps  = getAmps(scoringRoller);

        pros::delay(100);
    }
}

// drive mode handler
void handleDriveMode(bool isArcade) {
  isArcade ? handleArcade() : handleTank();
}

//arcade driver
void handleArcade() {
  int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
  int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
  chassis.arcade(leftY, rightX); // move the robot
}

//tank driver 
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

//testing sequence
void testing_sequence(){
  pros::lcd::set_text(1, "testing bobot");
  toggleScoringBar();
  pros::delay(1000);
  toggleScoringBar();

  frontIntake.move(127);
  pros::delay(500);
  frontIntake.move(63.5);
  pros::delay(500);
  frontIntake.move(0);

  middleRollers.move(127);
  pros::delay(500);
  middleRollers.move(63.5);
  pros::delay(500);
  middleRollers.move(0);

  colorSortRoller.move(127);
  pros::delay(500);
  colorSortRoller.move(63.5);
  pros::delay(500);
  colorSortRoller.move(0);

  scoringRoller.move(127);
  pros::delay(500);
  scoringRoller.move(63.5);
  pros::delay(500);
  scoringRoller.move(0);

  pros::lcd::set_text(1, "bobot passed");
}

// intake control (L1 toggle)
void handleIntakeCommands() {
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
        isIntakeForward = !isIntakeForward;
        if (isIntakeForward) {
            frontIntake.move(127);
            middleRollers.move(127);
            scoringRoller.move(127);
            colorSortRoller.move(127);
        } else {
            frontIntake.move(0);
            middleRollers.move(0);
            scoringRoller.move(0);
            colorSortRoller.move(0);
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

//scoring bar toggler (B button)
void toggleScoringBar() {
  isScoringBarUp = !isScoringBarUp;
  scoringBar.set_value(isScoringBarUp);
}