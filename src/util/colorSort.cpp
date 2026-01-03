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
    // gets current time from the program
    current = pros::millis();
    // gets proximity from sensor
    proximity = topOptical.get_proximity();
    topOptical.set_integration_time(3);
    pros::lcd::print(0, "Proximity: %d", topOptical.get_proximity());
    //opponent color
    if (isRed) {
        oppMin = BLUE_MIN;
        oppMax = BLUE_MAX;
    } else {
        oppMin = RED_MIN;
        oppMax = RED_MAX;
    }




    // if block is detected in the intake
    if (proximity>240&&proximity<260){
        // gets current hue from sensor
        hue = topOptical.get_hue();
    // if hue is detected as in opponents color range and sort is false
    if (hue>=oppMin&&hue<=oppMax&&!sort){
        // sets sorting to true
        sort = true;
        // sets var start to the time that the opponent block is detected
        start = pros::millis();
    }
    // if the sorting has been going on for less than 300ms
    if (current-start<300&&sort)
    {
        scoringRoller.move(-127);
        middleRollers.move(0);
        frontIntake.move(-20);
    }
    // if the sorting has been going on for longer than 300ms it lets the driver code continue operating rollers and sets sort to false
    if (current-start>300){
        scoringRoller.move(0);
        start=0;
        sort=false;
    }
    }
    
    
      

}