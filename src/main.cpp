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
std::string testRoute = "1GR"; // select from S, 1GR, 1GL, AWP, 2GL, 2GR, HS

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

//tasks

// only runs when tuneMode true
void positionTrackerTask() {
    while (true) {
    pros::lcd::print(1, "X: %.2f, Y: %.2f, Theta: %.2f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    pros::lcd::print(2, "est. psi: %d", PSI);
    // line 3 taken by double park delay estimation
    // line 4-7 taken by colorsort debug
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

rd::Selector selector({
  {"solo AWP", &solo_awp},
  {"two goal LEFT",&two_goal_LEFT },
  {"two goal RUSH", &two_goal_RUSH},
  {"two goal RIGHT", &two_goal_RIGHT},
  {"one goal LEFT", &one_goal_left},
  {"one goal RIGHT", &one_goal_right},
  {"1G LEFT RUSH", &L_1G_R},
  {"dummy", &dummy},
  {"skilly", &autonSkills}
});

void initialize() {
    selector.focus();


    // define + run tasks here
    if (tuneMode == true){
        chassis.setPose(0, 0, 0);
        pros::lcd::initialize();
        pros::Task pos(&positionTrackerTask);
    }

    //pros::Task telemetryTask(telemetry);
    //pros::Task colorSortTask(CSTaskFunc);
    //pros::Task stopIntakeTask(stopIntakeFunc);
    //pros::Task wall(wallTask);

    // set default values here
    scoringGate.set_value(false);
    topOptical.set_integration_time(3);
    topOptical.set_led_pwm(100);

    // drivetrain calibration
    chassis.calibrate();
    left_dt.set_brake_mode(pros::MotorBrake::coast);
    right_dt.set_brake_mode(pros::MotorBrake::coast);


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

void disabled() {
    scoringGate.set_value(false);

    loaderMech.set_value(false);
    isLoaderExtended=false;
    wingMech.set_value(false);
    isWingsOut=false;
}

void competition_initialize() {
  selector.focus();
}

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
    selector.run_auton();
  }
 }


void opcontrol() {
  while (true) {
        // drivemode switcher
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
            DHoldTime += 10; 
            if (DHoldTime >= 2000) { // how long the button has to be held to activate
                defaultDrive = !defaultDrive;
                controller.rumble(".."); 
                DHoldTime = 0; 
            }
        } else {
            DHoldTime = 0; 
        }
        // manual park 
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            POHoldTime += 10;
            if (POHoldTime >= 300) {
                isParkDown = !isParkDown; 
                controller.rumble("--"); 
                POHoldTime = 0; 
                parkMech.set_value(isParkDown);
            }
        } else {
            POHoldTime = 0; 
        }

        // double park macro
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) and controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                    ParkHoldTime += 10;
                    if (ParkHoldTime >= 30) { 
                        controller.rumble(".."); 
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
                        ParkHoldTime = 0; 
                    }
                }
                else{
                    ParkHoldTime = 0; 
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