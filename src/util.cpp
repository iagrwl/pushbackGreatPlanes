#include "main.h";
#include "pros/llemu.hpp"
#include "setup.hpp"

int BLUE_MAX = 230;
int BLUE_MIN = 190;
int RED_MIN = 0;
int RED_MAX = 40;

int block_dist = 80;
int bottom_block_dist = block_dist + 30;

bool isBlockThere(pros::Distance& currDist, bool isBlockPassing) {
  if (currDist.get_distance() <= block_dist) {
  if (!isBlockPassing) pros::delay(500);
    return currDist.get_distance() <= block_dist;
  }
  return false;
}

int i = 0;
int det = 0;

void sortOut() {
    IsColorSortEngaged = true;
    frontIntake.move(40);
    //pros::delay(100);
    colorSortRoller.move(-127);
    pros::delay(500);
    colorSortRoller.move(80);
    frontIntake.move(127);
    IsColorSortEngaged = false;
    pros::lcd::print(4, "sort %d", i++);
}

void colorSort() {
int min, max;
    if (!KeepRed){
        min = RED_MIN;
        max = RED_MAX;
    } else {
        min = BLUE_MIN;
        max = BLUE_MAX;
    } 
    while (true) {
        if (isBlockThere(bottomDistance, true)) {
            det++;
            colorSortOptical.set_led_pwm(100);
            while (colorSortOptical.get_proximity() < 100) {
                pros::delay(10);
            }
            float currHue = colorSortOptical.get_hue();
            if (currHue < max && currHue > min) {
                pros::Task sort(&sortOut);
            }
            //pros::lcd::print(4, "currHue: %.2f", currHue);
        }
        pros::delay(30);
    }
}

