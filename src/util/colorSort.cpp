#include "main.h"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "colorSort.hpp"

void colorSort() {
    static bool ejecting = false;
    static uint32_t eject_start = 0;
    
    topOptical.set_integration_time(1);
    
    double hue = topOptical.get_hue();
    double prox = topOptical.get_proximity();
    
    int enemy_min = isRed ? BLUE_MIN : RED_MIN;
    int enemy_max = isRed ? BLUE_MAX : RED_MAX;
    
    pros::lcd::print(6, "H:%.0f P:%.0f", hue, prox);
    
    if (ejecting) {
        scoringRoller.move_voltage(-20000);
        frontIntake.move_voltage(-20000);
        middleRollers.move_voltage(-20000);
        pros::lcd::print(7, "EJECT");
        
        if (pros::millis() - eject_start >= 50) {
            ejecting = false;
        }
        return;
    }
    
    if (colorsortOn && prox > 50 && hue >= enemy_min && hue <= enemy_max) {
        ejecting = true;
        eject_start = pros::millis();
    } else {
        pros::lcd::print(7, "READY");
    }
}