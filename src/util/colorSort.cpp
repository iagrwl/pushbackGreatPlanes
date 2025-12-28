#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "colorSort.hpp"


int oppMin;
int oppMax;
int hue;
bool sort =false;
int proximity;
uint32_t start=0;
uint32_t current;

void colorSort() {
    current = pros::millis();
    proximity = topOptical.get_proximity();
    topOptical.set_integration_time(3);
    pros::lcd::print(0, "Proximity: %d", topOptical.get_proximity());
    // determine opponent color
    if (isRed) {
        oppMin = BLUE_MIN;
        oppMax = BLUE_MAX;
    } else {
        oppMin = RED_MIN;
        oppMax = RED_MAX;
    }

    if (proximity>240&&proximity<260){
        hue = topOptical.get_hue();
    if (hue>=oppMin&&hue<=oppMax&&!sort){
        sort = true;
        start = pros::millis();
    }
    if (current-start<300&&sort)
    {
        scoringRoller.move(-127);
        middleRollers.move(0);
        frontIntake.move(-20);
    }
    if (current-start>300){
        scoringRoller.move(0);
        start=0;
        sort=false;
    }
    }
    
    
}