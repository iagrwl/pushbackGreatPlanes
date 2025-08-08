#include "main.h"
#include "autons.hpp"
#include "op_control.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/motors.h"
#include "robodash/api.h" 
#include "setup.hpp"

void positionTracker() {
    while (true) {
    pros::lcd::print(1, "X: %.2f, Y: %.2f, Theta: %.2f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
		std::uint32_t now = pros::millis();
		std::int32_t intakePosition = intake.get_raw_position(&now);

        pros::delay(10); // Delay to avoid overloading the system
    }
}


rd::Selector selector({
  // format is {"name of route", &routeFunction}
  // it's a 2D array, the string inputted will be
  // displayed on the screen and the referenced 
  // function is what will be run
  {"two goal",&two_goal },
  {"", }
});

rd::Console console;

void initialize() {
	pros::lcd::initialize(); // initialize if you want posTracker
                             // comment out if you want autoSelector

	pros::Task pos(&positionTracker);
  chassis.calibrate();

  loaderMech.set_value(false);

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
  }

void competition_initialize() {
  selector.focus();
  pros::Task Rumble(&rumble);
}

void autonomous() {
  // runs selected auton
  //selector.run_auton();
  //driveTesting(true);
  //turnTesting(true);
  //two_goal();
  one_goal();
 }

void opcontrol() {
  while (true) {
    // drive functions should be called in here
    handleDriveMode(true);
    
    handleIntakeCommands();
    handleOuttakeCommands();

    handleLoaderMechCommands();

    // 20 ms delay to avoid strain on the brain
		pros::delay(20);
	}
} 