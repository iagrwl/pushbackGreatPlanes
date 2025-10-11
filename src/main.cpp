#include "main.h"
#include "autons.hpp"
#include "op_control.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "robodash/api.h" 
#include "setup.hpp"


void positionTracker() {
    while (true) {
    pros::lcd::print(1, "X: %.2f, Y: %.2f, Theta: %.2f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    pros::lcd::print(2, "dist: %d", bottomDistance.get_distance());

		std::uint32_t now = pros::millis();
		//std::int32_t intakePosition = intake.get_raw_position(&now);

        pros::delay(10); // Delay to avoid overloading the system
    }
}

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


void wallDistanceTask(void* param) {
    while (true) {
        wallDistance(true); 
        pros::delay(50);    
    }
}



static void stall_check(void*){
    while(true){
        stall_checker();
        pros::delay(100);
    }
}

rd::Selector selector({
  {"two goal LEFT",&two_goal_LEFT },
  {"one goal LEFT", &one_goal_left},
  {"one goal RIGHT", &one_goal_right},
  {"solo AWP", &solo_awp},
  {"auton skills", &autonSkills}
});


//rd::Console console;

void initialize() {
	pros::lcd::initialize(); // initialize if you want posTracker
                             // comment out if you want autoSelector
	pros::Task pos(&positionTracker);

  pros::Task dis(wallDistanceTask, (void*)nullptr, "Wall Distance Task");

  static pros::Task checkforstall(stall_check);

  
  chassis.calibrate();

  

  left_dt.set_brake_mode(pros::MotorBrake::coast);
  right_dt.set_brake_mode(pros::MotorBrake::coast);

  selector.on_select([](std::optional<rd::Selector::routine_t> routine) {
		if (routine == std::nullopt) {
			std::cout << "No routine selected" << std::endl;
      controller.print(2, 0, "No routine selected!!");

		} else {
			std::cout << "Selected Routine: " << routine.value().name << std::endl;
      controller.print(2, 0, "Selected: %s", routine.value().name.c_str());

		}
	});
}

void disabled() {
    scoringBar.set_value(true);
  }

void competition_initialize() {
  selector.focus();
}

void autonomous() {
  // runs selected auton
  //selector.run_auton();
  //solo_awp();
  //one_goal_right();
  //two_goal_LEFT();
  //autonSkills();
 }

void opcontrol() {
  bool shouldPark = false;
  bool isArcade = true; //inverse for drivemode swap
  int holdTime = 0; // counter for the seconds button is held
  int ParkholdTime = 0; // counter for the seconds button is held
  
  while (true) {
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
            holdTime += 20; // loop delay is 20ms
            if (holdTime >= 2000) { // hold delay
                isArcade = !isArcade; // toggle mode
                controller.rumble(".."); // give feedback
                holdTime = 0; // reset so it doesn’t keep toggling
            }
        } else {
            holdTime = 0; // reset if released early
        }
    if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) and controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                ParkholdTime += 20; // loop delay is 20ms
                if (ParkholdTime >= 30) { // hold delay
                    controller.rumble(".."); // give feedback
                    bottomOptical.set_led_pwm(100);
                    left_dt.move(-127);
                    right_dt.move(-127);
                    pros::delay(75);
                    left_dt.move(0);
                    right_dt.move(0);
                    while (shouldPark==false){
                        frontIntake.move(-70);
                        middleRollers.move(-100);
                        scoringRoller.move(-127);
                        if (bottomDistance.get_distance() >= 40 && bottomDistance.get_distance() <=70){
                            frontIntake.move(0);
                            wingMech.set_value(true);
                            pros::delay(100);
                            middleRollers.move(0);
                            scoringRoller.move(0);
                            shouldPark = true;
                        }
                    }
                    
                    
                    ParkholdTime = 0; // reset so it doesn’t keep toggling
                }  
            } 
            
            else {
                ParkholdTime = 0; // reset if released early
            }

    // driver control functions go here
    handleDriveMode(isArcade);
    handleIOCommands();
    handleLoaderMechCommands();
    handleWingMechCommands();
    handleParkCommands();
    //checkforpark();
    // 20 ms delay to avoid strain on the brain
		pros::delay(20);
	}
}