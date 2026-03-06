#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "colorSort.hpp"

bool isColorSortOn = true;
bool isRed = false;
bool isColorPriority = false;


void colorSort(){
    if (!isColorSortOn) {
        isColorPriority = false;
        pros::lcd::print(4, "colorsort off");
        pros::lcd::print(7, "");
        scoringRoller.move(0);
        return;
    }

    int hue = topOptical.get_hue();
    bool oppositeDetected = isRed ? (hue > 205 && hue < 220) : (hue > 10 && hue < 25);

    isColorPriority = oppositeDetected;

    pros::lcd::print(4, "colorsort activated");
    pros::lcd::print(5, isRed ? "red alliance selected" : "blue alliance selected");
    pros::lcd::print(6, "color: %d", hue);

    if (oppositeDetected) {
        pros::lcd::print(7, "opposite color detected");
        scoringRoller.move(-127);
    } else {
        pros::lcd::print(7, "");
        scoringRoller.move(0);
    }
}
        
