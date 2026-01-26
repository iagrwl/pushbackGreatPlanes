#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "colorSort.hpp"


int oppMin;
int oppMax;
int hue;
int proximity;


void colorSort() {
    
    // Set integration time to minimum for fastest response (3ms)
    topOptical.set_integration_time(3);
    
    
        
            if (isRed){
        oppMin = BLUE_MIN;
        oppMax = BLUE_MAX;
        }
        else{
            oppMin = RED_MIN;
            oppMax = RED_MAX;
        }
        if (colorsortOn == true){
        // Get current color sensor reading (hue value)
        double colorValue = topOptical.get_hue();
        
        // Check if the reading is valid (not an error)
        if (colorValue >= 0 && colorValue <= 360) {
            // Check if detected color is within opposite alliance range
            if (colorValue >= oppMin && colorValue <= oppMax) {
                // Opposite alliance color detected - STOP THE ROLLER
                
                scoringRoller.move(-50);
                
            }
        }
        }
        else{
            pros::delay(5);
        }
        // Minimal delay for fastest detection
        pros::delay(2);
    
}
