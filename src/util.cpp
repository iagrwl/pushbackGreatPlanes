#include "main.h";
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

void colorSort() {
int min, max;
    if (KeepRed){
        min = RED_MIN;
        max = RED_MAX;
    } else {
        min = BLUE_MIN;
        max = BLUE_MAX;
    } 
    while (true) {
        if (isBlockThere(bottomDistance, true)) {
            colorSortOptical.set_led_pwm(100);
            while (colorSortOptical.get_proximity() > 50) {
                pros::delay(10);
            }
            float currHue = colorSortOptical.get_hue();
            if (currHue < max && currHue > min) {
                colorSortRoller.move(-127);
                pros::delay(200);
                colorSortRoller.move(127);
            }
        }
        pros::delay(30);
    }
}

