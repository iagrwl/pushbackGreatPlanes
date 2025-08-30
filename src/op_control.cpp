#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "setup.hpp"

//states
bool isIntakeForward = false;
bool isHighSpeedScoring = false;
bool isScoringBarUp = false;
bool isFI_Stop = false;
bool isMR_Stop = false;
bool isCSR_Stop = false;
bool isSR_Stop = false;
bool isStallOverride = false;

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

//rpms
double FI_rpm = 0;
double MR_rpm = 0;
double CSR_rpm = 0;
double SR_rpm = 0;

//temps for checking spikeronis
double FI_prevTemp = 0;
double MR_prevTemp = 0;
double CSR_prevTemp = 0;
double SR_prevTemp = 0;

//threshold values
const double ampThreshold = 1500;
const double rpmThreshold = 5;
const double tempSpikeThreshold = 10;

//helper boy 1
double getTempF(pros::Motor& m) {
    return m.get_temperature() * 9.0 / 5.0 + 32;
}

//helper boy 2
double getAmps(pros::Motor& m) {
    return m.get_current_draw(); 
}

//helper boy 3
double getRPM(pros::Motor& m) {
    return m.get_actual_velocity();
}


void StallCheck(void* param) {
    while (true) {
        //front intake
        FI_temp = getTempF(frontIntake);
        FI_amps = getAmps(frontIntake);
        FI_rpm = getRPM(frontIntake);

        //middle rollers
        MR_temp = getTempF(middleRollers);
        MR_amps = getAmps(middleRollers);
        MR_rpm = getRPM(middleRollers);

        //color sort rollers
        CSR_temp = getTempF(colorSortRoller);
        CSR_amps = getAmps(colorSortRoller);
        CSR_rpm = getRPM(colorSortRoller);

        //scoring roller
        SR_temp = getTempF(scoringRoller);
        SR_amps = getAmps(scoringRoller);
        SR_rpm = getRPM(scoringRoller);

        //below code checks each motor if the amps is greater than the threshold then checks if the rpm is less then the threshold then checks if the average temp delta spike is more than the threshold

        //front intake
        if ((FI_amps > ampThreshold && abs(FI_rpm) < rpmThreshold) && (FI_temp - FI_prevTemp > tempSpikeThreshold)) {
            frontIntake.move(0);
        }

        //middle rollers
        if ((MR_amps > ampThreshold && abs(MR_rpm) < rpmThreshold) && (MR_temp - MR_prevTemp > tempSpikeThreshold)) {
            middleRollers.move(0);
        }

        //color sort rollers
        if ((CSR_amps > ampThreshold && abs(CSR_rpm) < rpmThreshold) && (CSR_temp - CSR_prevTemp > tempSpikeThreshold)) {
            colorSortRoller.move(0);
        }

        //scoring rollers
        if ((SR_amps > ampThreshold && abs(SR_rpm) < rpmThreshold) && (SR_temp - SR_prevTemp > tempSpikeThreshold)) {
            scoringRoller.move(0);
        }

        //updates spike check readings
        FI_prevTemp = FI_temp;
        MR_prevTemp = MR_temp;
        CSR_prevTemp = CSR_temp;
        SR_prevTemp = SR_temp;

        pros::delay(100); //delay so brain dont go boom boom
    }
}

//DRIVE

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

// lets driver switch drive modes (x + right arrow 3x in 1 sec) fea
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

//CORE

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

//EXTENSIONS
void handleScoringBarCommands() { 
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) { 
    !isScoringBarUp ? isScoringBarUp = true : isScoringBarUp = false;
    scoringBar.set_value(isScoringBarUp); 
  }
}

//TOGGLERS

//scoring bar toggler
void toggleScoringBar() {
  isScoringBarUp = !isScoringBarUp;
  scoringBar.set_value(isScoringBarUp);
}

//MACROS

//stall overrider in case code starts bugging during match
void toggleStallOverride(){
   if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) { 
    !isStallOverride ? isStallOverride = true : isStallOverride = false;
  }
}
