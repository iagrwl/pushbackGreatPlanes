#include "main.h"
#include "autons.hpp"
#include "op_control.hpp"
#include "pros/rtos.hpp"
#include "robodash/api.h" 
#include "setup.hpp"

void positionTracker() {
    while (true) {
    pros::lcd::print(1, "X: %.2f, Y: %.2f, Theta: %.2f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
		std::uint32_t now = pros::millis();
		std::int32_t intakePosition = intake.get_raw_position(&now);

		pros::lcd::print(2, "Hue: %.2f, Prox: %d", intakeOptical.get_hue(), intakeOptical.get_proximity());
		pros::lcd::print(3, "Pos: %d", intakePosition);
        pros::delay(10); // Delay to avoid overloading the system
    }
}


rd::Selector selector({
  // format is {"name of route", &routFunction}
  // it's a 2D array, the string inputted will be
  // displayed on the screen and the referenced 
  // function is what will be run
  {"", },
  {"", }
});

rd::Console console;

void initialize() {
	//pros::lcd::initialize(); // initialize if you want posTracker
                             // comment out if you want autoSelector

	pros::Task pos(&positionTracker);
  chassis.calibrate();

  selector.on_select([](std::optional<rd::Selector::routine_t> routine) {
		if (routine == std::nullopt) {
			std::cout << "No routine selected" << std::endl;
      master.print(2, 0, "No routine selected!!");

		} else {
			std::cout << "Selected Routine: " << routine.value().name << std::endl;
      master.print(2, 0, "Selected: %s", routine.value().name.c_str());

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
  selector.run_auton();
}

void opcontrol() {
  while (true) {
    // drive functions should be called in here

    // 20 ms delay to avoid strain on the brain
		pros::delay(20);
	}
} 