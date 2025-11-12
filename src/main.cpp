#include "main.h"
#include "autons.hpp"
#include "op_control.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "robodash/api.h" 
#include "setup.hpp"

bool tuneMode = true; // set true for green screen set false for competition
/*
Sets variables - some are settings for the primary driver, some are holding times for controls.
*/
bool shouldLift = false; // internal bool for program to verify if ball in prime position
bool defaultDrive = true; //default toggler, true for arcade default and false for tank

int DHoldTime = 0; // counter for the seconds button is held for drive mode switch
int ParkHoldTime = 0; // counter for the seconds button is held for park macro
int POHoldTime = 0;// counter for the park override button
bool isParkDown = false; // marks if the park bar is down

float DPDcurveMultiplier = 0.63; // changes the amount of curve the delay has
int FDPV = 120; // enter at 100 psi what the delay is
int LDPV = 40; // enter the lowest functioning psi is
float DPdelay = 0;

int BLUE_MAX = 230;
int BLUE_MIN = 150;
int RED_MAX = 50;
int RED_MIN = 0;
bool isRed = true;


/*
A tuning screen that shows x,y, theta and helps for tuning. only runs when the tunemode is set to true
*/
void positionTracker() {
    while (true) {
    //XY THETA DISPLAY
    pros::lcd::print(1, "X: %.2f, Y: %.2f, Theta: %.2f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    //BOTTOM DIST SENSOR DISPLAY
    pros::lcd::print(2, "left: %d", leftDistance.get_distance());
    //TOP COLOR SENSOR DISPLAY
    pros::lcd::print(3, "DPDelay: %.2f", DPdelay);
    pros::lcd::print(4, "PSI: %d", PSI);
    pros::delay(10); // delay to avoid overloading the system
    }
}
/*
Define tasks to be run in parallel here
Use the below format.
*/


void telemetryTask(void*){
    while(true){
        telemetry();
        pros::delay(100);
    }
}

//2D array for RD auton selector
rd::Selector selector({
  {"solo AWP", &solo_awp},
  {"two goal LEFT",&two_goal_LEFT },
  {"one goal LEFT", &one_goal_left},
  {"one goal RIGHT", &one_goal_right},
  {"auton skills", &autonSkills}
});

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
    controller.set_text(0, 0, "imu ready");
    //task caller
    //pros::Task dis(wallDistanceTask, (void*)nullptr, "Wall Distance Task");

    pros::Task telemetryTask(telemetry);

    //calibrates drivetrain
    chassis.calibrate();

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

/*
Occurs when the 15s auton period is happening
1. Runs the auton selected by the selector.
*/
void autonomous() {
  // runs selected auton
  //selector.run_auton();
  solo_awp();

 }


void opcontrol() {
    //chassis.setPose(15,-48,90);
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

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            POHoldTime += 10; // loop delay is 20ms
            if (POHoldTime >= 300) { // must hold for 2000 ms for statement to pass
                isParkDown = !isParkDown; // toggle mode
                controller.rumble("--"); // give feedback
                POHoldTime = 0; // reset so it doesn’t keep toggling
                parkMech.set_value(isParkDown);
            }
        } else {
            POHoldTime = 0; // reset if released early
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
                                pros::delay(80);
                                frontIntake.move(0);
                                parkMech.set_value(true);
                                isParkDown = true;
                                float o = LDPV;
                                float t = FDPV;
                                float p = PSI;
                                float c = DPDcurveMultiplier;
                                float ratio = (100 - o != 0) ? (p - o) / (100.0 - o) : 0;
                                if (ratio < 0) ratio = 0;
                                DPdelay = t * pow(ratio, c);
                                pros::lcd::print(3, "DPDelay: %.2f", DPdelay);
                                pros::delay(DPdelay);
                                controller.set_text(0, 0, "lifting bot");
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
    updatePSI();
    //handleParkCommands();
    // 20 ms delay to avoid strain on the brain
	pros::delay(20);
	}
}