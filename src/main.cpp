#include "main.h"
#include "awp.hpp"
#include "blockScoring.hpp"
#include "distanceSensor.hpp"
#include "midGoalScoring.hpp"
#include "oneGoal.hpp"
#include "pidTesting.hpp"
#include "skills.hpp"
#include "testRoute.hpp"
#include "twoGoal.hpp"
#include "dummy.hpp"
#include "op_control.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "robodash/api.h"
#include "setup.hpp"
#include "colorSort.hpp"

bool tuneMode = true; // set true for green screen set false for competition
std::string testRoute = "HS"; // select from S, 1GR, 1GL, AWP, 2GL, 2GR, HS

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





/*
Tuning screen - screen that displays x,y theta + additional debug info. 
Only runs when tunemode is set to true
*/
void positionTracker() {
    while (true) {
    pros::lcd::print(1, "X: %.2f, Y: %.2f, Theta: %.2f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    pros::lcd::print(2, "applied DP delay %.2f", DPdelay);
    pros::lcd::print(3, "est. psi: %d", PSI);
    
    pros::delay(10);
    }
}




void wallTask(void* param) {
  while (true) {
    wallDistance(true, true);
    pros::delay(10);
  }
}



void CSTaskFunc(void* param) {
  while (true) {
    colorSort();
    pros::delay(4);
  }
}

void telemetryFunc(void* param) {
  while (true) {
    telemetry();
    pros::delay(12);
  }
}

void stopIntakeFunc(void* param) {
  while (true) {
    intakeAutoStopping();
    pros::delay(13);
  }
}

//2D array for RD auton selector
rd::Selector selector({
  {"solo AWP", &solo_awp},
  {"two goal LEFT",&two_goal_LEFT },
  {"two goal RUSH", &two_goal_RUSH},
  {"one goal LEFT", &one_goal_left},
  {"one goal RIGHT", &one_goal_right},
  {"1G LEFT RUSH", &L_1G_R},
  {"dummy", &dummy},
  {"skilly", &autonSkills}
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
    
    selector.focus();
    scoringGate.set_value(false);
    if (tuneMode == true){
        chassis.setPose(0, 0, 0);
        pros::lcd::initialize();
        pros::Task pos(&positionTracker);
    }
    
  
    topOptical.set_integration_time(3);
    topOptical.set_led_pwm(100);
    // task callerss
    //pros::Task telemetryTask(telemetry);
    pros::Task colorSortTask(CSTaskFunc);
    pros::Task stopIntakeTask(stopIntakeFunc);
    //pros::Task wall(wallTask);
    // calibrates drivetrain
    chassis.calibrate();
    
    // sets idle mode on drivetrain
    left_dt.set_brake_mode(pros::MotorBrake::coast);
    right_dt.set_brake_mode(pros::MotorBrake::coast);


    // robodash - dont mess w
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
    scoringGate.set_value(false);


    loaderMech.set_value(false);
    isLoaderExtended=false;
    wingMech.set_value(false);
    isWingsOut=false;
    
    
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
NOTE: Color sort task is already running from initialize()
*/
void autonomous() {
  if (tuneMode){
   if (testRoute == "S") autonSkills();
    else if (testRoute == "1GR") one_goal_right();
    else if (testRoute == "1GL") one_goal_left();
    else if (testRoute == "AWP") solo_awp();
    else if (testRoute == "2GL") two_goal_LEFT();
    else if (testRoute == "2GR") two_goal_RIGHT();
    else if (testRoute == "HS") HARDSkills();
    }
  else{
  // runs auton from selected
  selector.run_auton();
  }
  
  
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
                DHoldTime = 0; // reset so it doesn't keep toggling
            }
        } else {
            DHoldTime = 0; // reset if released early
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            POHoldTime += 10; // loop delay is 20ms
            if (POHoldTime >= 300) { // must hold for 2000 ms for statement to pass
                isParkDown = !isParkDown; // toggle mode
                controller.rumble("--"); // give feedback
                POHoldTime = 0; // reset so it doesn't keep toggling
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
                            frontIntake.move(-55);
                            middleRollers.move(-100);
                            scoringRoller.move(-127);
                            controller.set_text(0, 0, "lifting bot");
                            if (bottomDistance.get_distance() >= 50 && bottomDistance.get_distance() <=80){
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

                                middleRollers.move(0);
                                scoringRoller.move(0);
                                shouldLift = true;
                            }

                        }

                        ParkHoldTime = 0; // reset so it doesn't keep toggling
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
    handleDoublePark();
    updatePSI();
    handleDescoreMechCommands();
    //handleQuickWing();    
    //handleParkCommands();
    // 20 ms delay to avoid strain on the brain
	pros::delay(20);
	}
}