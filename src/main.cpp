#include "main.h"
#include "autons.hpp"
#include "op_control.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "robodash/api.h" 
#include "setup.hpp"

/*
Sets variables - some are settings for the primary driver, some are holding times for controls.
*/
bool tuneMode = false; 
bool shouldLift = false; // internal bool for program to verify if ball in prime position
bool defaultDrive = true; //default toggler, true for arcade default and false for tank
int DHoldTime = 0; // counter for the seconds button is held for drive mode switch
int ParkHoldTime = 0; // counter for the seconds button is held for park macro

/*
A tuning screen that shows x,y, theta and helps for tuning
*/
void positionTracker() {
    while (true) {
    //XY THETA DISPLAY
    pros::lcd::print(1, "X: %.2f, Y: %.2f, Theta: %.2f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    //BOTTOM DIST SENSOR DISPLAY
    pros::lcd::print(2, "BSD: %d", bottomDistance.get_distance());
    //FREE LINES
    pros::lcd::print(3, "TCS: %d", topOptical.get_hue());
    
    pros::delay(10); // delay to avoid overloading the system
    }
}
/*
TODO: idek what this is bhargav do it
*/
float wallDistance(bool shouldPrint = false) {
    //This accounts for the sensor turning off of the center of the bot
    //X means offset from the center along the width of the bot, Y means along the length
    float offsetX = 6.0; 
    float offsetY = 0; 

    float distancemm = sideDistance.get();
    float distanceIn = distancemm / 25.4 + offsetX;

    float angDeg = chassis.getPose().theta;
    float angRad = angDeg * M_PI / 180.0;

    //It was buggy so now if the angle is like 400 it'll turn to 40
    float angle = fmod(angDeg, 360.0);
    //Mod doesn't work on negatives for some reason
    if (angle < 0) angle += 360.0;

    float rotatedX = offsetX * cos(angRad) - offsetY * sin(angRad);
    float rotatedY = offsetX * sin(angRad) + offsetY * cos(angRad);

    float correctedDist = 0;

    //Left Wall
    if (angle >= 315 || angle < 45) {
        correctedDist = distanceIn * cos(angRad) + rotatedX;
    //Back Wall
    } else if (angle >= 45 && angle < 135) {
        correctedDist = distanceIn * sin(angRad) + rotatedY;
    //Right Wall
    } else if (angle >= 135 && angle < 225) {
        correctedDist = -distanceIn * cos(angRad) - rotatedX;
    //Close Wall
    } else {
        correctedDist = -distanceIn * sin(angRad) - rotatedY;
    }

    if (shouldPrint) {
        // pros::lcd::print(4, "Raw Distance: %f", distancemm);
        // pros::lcd::print(5, "Distance: %f", distanceIn);
        // pros::lcd::print(6, "Corrected: %f", correctedDist);
    }

    return correctedDist;
}

int BLUE_MAX = 230;
int BLUE_MIN = 150;
int RED_MAX = 50;
int RED_MIN = 0;
bool isRed = true;

bool isWrongColor(float currHue, bool allianceRed = true) {
    if (allianceRed) {
        return currHue <= BLUE_MAX && currHue >= BLUE_MIN; 
    } else {
        return currHue <= RED_MAX && currHue >= RED_MIN;
    }
}
void scoreCorrectColor() {
    float currHue;
    while (true) {
    currHue = topOptical.get_hue();
    if (isWrongColor(currHue, isRed)) {
        scoringBar.set_value(false);
    }
    }
    
}

/*
Define tasks to be run in parallel here
Use the below format.
*/
void wallDistanceTask(void* param) {
    while (true) {
        wallDistance(true); 
        pros::delay(50);    
    }
}

void stall_check(void*){
    while(true){
        stall_checker();
        pros::delay(100);
    }
}

//2D array for RD auton selector
rd::Selector selector({
  {"two goal LEFT",&two_goal_LEFT },
  {"one goal LEFT", &one_goal_left},
  {"one goal RIGHT", &one_goal_right},
  {"solo AWP RED", &solo_awpRED},
  {"solo AWP BLUE", &solo_awpBLUE},
  {"auton skills", &autonSkills}
});


rd::Console console;
/*
Occurs when bot goes into init phase.
1. Checks if user wants tune screen and runs lines for it
2. Calls tasks to be run in parallel
3. Calibrates the drivetrain
4. Sets the braking mode(idle mode) to coast
5. Robodash code - dont mess w it prolly
*/
void initialize() {
    
    if (tuneMode == true){
        pros::lcd::initialize(); // comment both lines for selector
        pros::Task pos(&positionTracker);
    }

    topOptical.set_led_pwm(100);

    //task caller
    pros::Task dis(wallDistanceTask, (void*)nullptr, "Wall Distance Task");

    pros::Task checkforstall(stall_check);

    //calibrates drivetrain
    chassis.calibrate();
    controller.set_text(0, 0, "imu ready - goodluck!");

    //SETS DRIVETRAIN IDLE MODE
    left_dt.set_brake_mode(pros::MotorBrake::coast);
    right_dt.set_brake_mode(pros::MotorBrake::coast);

    //robodash - dont mess w
    selector.on_select([](std::optional<rd::Selector::routine_t> routine) {
        if (routine == std::nullopt) {
            std::cout << "No routine selected" << std::endl;
        controller.print(2, 0, "select route");

        } else {
            std::cout << "Selected Routine: " << routine.value().name << std::endl;
        controller.print(2, 0, "run: %s", routine.value().name.c_str());

        }
    });
}

/*
Occurs when bot is in disable phase - when the autonomous and driving period are over.
1. Sets the scoring hood to lift to let blocks pass using inertia even when auton period is over.
*/

void disabled() {
    scoringBar.set_value(true);
  }

/*
Occurs when the bot is running the program
1. Shows the auton selector on the screen.
*/
//NOTE: the selected program is stored on the brains SD card for future runs
void competition_initialize() {
  selector.focus();
}

void stopIntake() {
    frontIntake.move(50);
    middleRollers.move(50);
    scoringRoller.move(-127);
    pros::delay(1000);
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127);
}
/*
Occurs when the 15s auton period is happening
1. Runs the auton selected by the selector.
*/
void autonomous() {
  // runs selected auton
  selector.run_auton();


//   float currHue;
//     frontIntake.move(127);
//     middleRollers.move(127);
//     scoringRoller.move(127);
//     while(true) {
//         currHue = topOptical.get_hue();
//         pros::lcd::print(5, "Hue: %.2f", topOptical.get_hue());
//         if (currHue > 120 && currHue < 250) {
//             pros::Task stop(&stopIntake);
//         }
//     }


 }


void opcontrol() {
    while (true) {
        //drivemode switcher
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
            DHoldTime += 20; // loop delay is 20ms
            if (DHoldTime >= 2000) { // must hold for 2000 ms for statement to pass
                defaultDrive = !defaultDrive; // toggle mode
                controller.rumble(".."); // give feedback
                DHoldTime = 0; // reset so it doesn’t keep toggling
            }
        } else {
            DHoldTime = 0; // reset if released early
        }

        //double park macro
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) and controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                    ParkHoldTime += 10; // loop increments in 10ms

                    if (ParkHoldTime >= 30) { // must hold for 30+ ms
                        controller.rumble(".."); // give feedback to signal DP in progress
                        left_dt.move(-127);
                        right_dt.move(-127);
                        pros::delay(80);
                        left_dt.move(0);
                        right_dt.move(0);

                        while (shouldLift==false){
                            frontIntake.move(-60);
                            middleRollers.move(-100);
                            scoringRoller.move(-127);

                            if (bottomDistance.get_distance() >= 50 && bottomDistance.get_distance() <=80){
                                pros::delay(25);
                                frontIntake.move(0);
                                parkMech.set_value(true);
                                pros::delay(100);
                                controller.set_text(0, 0, "lifting le bot");
                                middleRollers.move(0);
                                scoringRoller.move(0);
                                shouldLift = true;
                            }

                        }

                        ParkHoldTime = 0; // reset so it doesn’t keep toggling
                    }  

                } 
                else {
                    ParkHoldTime = 0; // reset if released early
                }

    // driver control functions go here
    handleDriveMode(defaultDrive);
    handleIOCommands();
    handleLoaderMechCommands();
    handleWingMechCommands();
    //handleParkCommands();
    // 20 ms delay to avoid strain on the brain
	pros::delay(20);
	}
}