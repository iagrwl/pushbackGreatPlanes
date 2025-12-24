#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "colorSort.hpp"

int BLUE_MAX = 230; // max blue hue
int BLUE_MIN = 190; // min blue hue
int RED_MAX = 20; // max red hue
int RED_MIN = 5; // min red hue

int OPP_MIN; // enemy alliance color min
int OPP_MAX; // enemy alliance color max

void colorSort() {
    
    // fastest int time to 3ms
    topOptical.set_integration_time(3);

   
        // assigns enemy range based on alliance color
        if (isRed){
            OPP_MIN = BLUE_MIN;
            OPP_MAX = BLUE_MAX;
        }
        else{
            OPP_MIN = RED_MIN;
            OPP_MAX = RED_MAX;
        }
        // checks if colorsort is allowed to run
        if (colorsortOn == true){

            // gets hue from sensor
            double colorValue = topOptical.get_hue();
        
            // filters false readings
            if (colorValue >= 0 && colorValue <= 360) {
                // checks if in range of enemy color
                if (colorValue >= OPP_MIN && colorValue <= OPP_MAX) {
                    // code that occurs when enemy color detected
                    scoringRoller.move(-120);
             
                }
            }
        }
        // passes if color sort isnt allowed to run
        else{ 
            pros::delay(5);
        }
    
    }