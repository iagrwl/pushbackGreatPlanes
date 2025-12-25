#include "main.h"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "colorSort.hpp"

int BLUE_MIN = 190, BLUE_MAX = 230, RED_MIN = 5, RED_MAX = 30;

void colorSort() {
    static bool sorting = false;
    static uint32_t start = 0;
    const uint32_t sort_time = 350;

    topOptical.set_integration_time(3);

    int opp_min = isRed ? BLUE_MIN : RED_MIN;
    int opp_max = isRed ? BLUE_MAX : RED_MAX;

    double hue = topOptical.get_hue();

    if (colorsortOn && !sorting && hue >= opp_min && hue <= opp_max) {
        sorting = true;
        start = pros::millis();
    }

    if (sorting) {
        scoringRoller.move(-127);
        pros::lcd::print(7, "SORT");
        if (pros::millis() - start >= sort_time) {
             
            scoringRoller.move(0);
            sorting = false;
        }
    }
    pros::lcd::print(7, "KEEP");

    pros::delay(3);
}