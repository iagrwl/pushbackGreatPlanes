#include "main.h"
#include "pros/misc.h"
#include "setup.hpp"

bool isIndexerOn = false;
bool isFirstTimePressed = true;
bool isOuttakeToggled = false;
bool OuttakeOverride = false;
bool isIntakeForward = true;
bool isDescoreExtended = false;
bool isLoaderExtended = false;
bool isWingExtended = false;
bool isHighSpeed = false;
int toggle_power = 60;

bool DriveMode = true; // true for arcade false for tank
int DynamicDriveSwitchClickCount = 0; // tracks how many times toggle combo has been clicked in sequence
uint32_t lastDynamicSwitchClickTime = 0; // js stores the last timestamp of when the combo has been clicked

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



void handleDynamicDriveMode() { // function that allows driver to switch drive modes by clicking x and right arrow button on the controller 3 times in a row to switch
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        uint32_t now = pros::millis(); // simply gets the current time in relation to when prog started
        if (now - lastDynamicSwitchClickTime <= 1000) { // if the current time minus by the last time the combo was pressed is less than 1 second then the condition passess
            DynamicDriveSwitchClickCount++; // adds one to the combo click count
        } 
        else { // if the combo is not pressed within the last in a second then this passes
            DynamicDriveSwitchClickCount = 1; // resets the combo count
        }

        lastDynamicSwitchClickTime = now; // since the combo condition was passed above the last time the combo was click is set to the current prog runtime

        if (DynamicDriveSwitchClickCount >= 3) { // checks if the combo click count is more than or equal to 3
            DriveMode = !DriveMode; // flips the drive mode statement to toggle the drive mode
            DynamicDriveSwitchClickCount = 0; // sets the click count all the way to zero to prevent early engagement of dynamic drive switching
            controller.rumble("."); // rumbles to notify driver
        }
    }
}

void toggleHighSpeed() { // function that uses the up arrow to toggle between high speed and low speed for scoring. starts in low speed mode as default
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {  // if the controller gets a new press from the up arrow then this passes
        isHighSpeed = !isHighSpeed; // flips the highspeed boolean to allow for differentiation in speed
        if (isHighSpeed){ // if the high speed condition is true then the speed is max (127)
          toggle_power = 127; // sets the toggled power to 127
        } else{ // if the above statement fails then this statement passes
          toggle_power = 50; // sets the toggled power to 50
        }
    }
}

void handleIntakeCommands () { // handles intake control using the left trigger buttons on the controller
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) { // checks for new press from the left top trigger buttons
    isOuttakeToggled = !isOuttakeToggled; // flips the boolean to toggle the boolean that keeps track if the outtake is toggled

    if (isOuttakeToggled) { // if the outtake is toggle and the above statement is passed then this passes
      intake.move(127); // moves the intake at max speed
      if (!OuttakeOverride){ // if the outtake override is the inverse of the current state then this passes
        outtake.move(127); // it moves the outtake/colorsort roller forward at max speed. this moves because it helps the intake pull balls up
        isIntakeForward = true; // sets the intake boolean to true that keeps tracks of the direction of the intake
      }
    } 
    else { // if the above statement does not pass this statement passes
        intake.move(0); // switches the intake off
      if (!OuttakeOverride){
        outtake.move(0); // if the outtake override is the inverse of the currentt state then this passes
        isIntakeForward = false; // sets the intake boolean to false
      }
    }
  }

if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { // if the bottom left trigger button is held activate reverse intake/outtake/color sort roller
    
    isOuttakeToggled = false; // turn off outtake toggle to avoid conflict with manual override
    
    isIndexerOn = false; // disable indexer while L2 is held
    intake.move(-80); // run intake in reverse at reduced speed
    indexer.move(-127); // run indexer in reverse at full power
    outtake.move(-127); // run outtake in reverse at full power to eject balls
    OuttakeOverride = true; // set override to prevent other intake/outtake logic from interfering
    isIntakeForward = false; // update intake direction state to indicate reverse mode
} else if (!controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2) && !isIntakeForward) {
    isIndexerOn = true; // re-enable indexer once L2 is released and intake was previously reversed
    intake.move(0); // stop intake motor as reverse mode is no longer active
    OuttakeOverride = false; // clear override so normal intake/outtake logic resumes
}
}

void handleOuttakeCommands() { // function to control the scoring of game elements using outtake
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) { // this function is simply to avoid the L2 button interfering from this func to the above oen
    return;//skip logic coolio
  }
  if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { // if the right top trigger button is held then this passes
    indexer.move(toggle_power); // sets the indexer to the selected power mode
    isIndexerOn = true; // sets the boolean to true
    outtake.move(toggle_power); // sets the outtake to the selected power mode
    OuttakeOverride = true; // turns on override to force engagement of above code
  } 
  else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) { // if the right bottom trigger button is held then this passes
    indexer.move(toggle_power); // sets the indexer to selected power mode
    isIndexerOn = true; // sets the boolean to true
    outtake.move(-toggle_power); // sets the outtake to inverse of the selected power mode to spin in reverse
    OuttakeOverride = true; // forces engagement of above code
  } 
  else { // if all above statements fail this passes

    if (isIndexerOn) {
    indexer.move(0); // stop the indexer motor if it was previously running 
    isIndexerOn = false; // update the indexer state 
    }

    if (isOuttakeToggled) {
        outtake.move(toggle_power); // run the outtake motor at the current toggled power if outtake toggle is active
    } 
    else {
        outtake.move(0); // stop the outtake motor if the toggle is not active 
    }

    OuttakeOverride = false; // reset the override state so normal intake/outtake control can resume
    }
}


void handleLoaderMechCommands() { // handles loader mech controls and prevents from activation if descore mech is in use
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) { // passes if the left button is clicked
    if (!isLoaderExtended && !isDescoreExtended) { // check if loader is not already extended and descore mech is not extended
      
      isLoaderExtended = true; // extend the loader mech
      
      if (isDescoreExtended) { // if descore mech was extended, retract it to stay in limit
        isDescoreExtended = false; // update descore state
        descoreMech.set_value(false); // retract the descore mech
      }
    } else if (isLoaderExtended) { // if loader is already extended
      
      isLoaderExtended = false; // retract the loader mech
    }
    loaderMech.set_value(isLoaderExtended); // physically alter the state of the piston
  }
}

void handleDescoreMechCommands() { // handles descore mech controls and prevents from activiation if loader mech in use
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) { // passes if A button is clicked
    if (!isDescoreExtended && !isLoaderExtended) { // check if descore is not extended and loader is not extended
      
      isDescoreExtended = true; // extend the descore mech
      
      if (isLoaderExtended) { // if loader was extended, retract it to stay in limit
        isLoaderExtended = false; // update loader state
        loaderMech.set_value(false); // retract the loader mech
      }
    } else if (isDescoreExtended) { // if descore mech is already extended
      
      isDescoreExtended = false; // retract the descore mech
    }
    descoreMech.set_value(isDescoreExtended); // set the descore mech according to its current state
  }
}

void handleWingMechCommands() { // handles wing mech controls
  if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) { // passes if B button is clicked
    !isWingExtended ? isWingExtended = true : isWingExtended = false; // toggle wing mech state
    wingMech.set_value(isWingExtended); // apply the current state to the wing mech
  }
}

//rumbles controller BRRRRRRR
void rumble() {
  for (int i = 60; i > 0; i--) {
    if (i == 10) {
      controller.rumble("--");
    }
    pros::delay(1000);
  }
}