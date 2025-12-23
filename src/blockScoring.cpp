#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "blockScoring.hpp"



void scoreBlocks(int numberOfBlocks, bool colorsort){
    int blocksPending = numberOfBlocks;
    
    while (blocksPending>0){
        scoringGate.set_value(false);
        scoringRoller.move(127);
        middleRollers.move(127);
        float dist = topOptical.get_proximity();
        if (dist > 10 && dist < 90){ // change range here for when it detects a ball
            blocksPending--;
            pros::delay(10); // time that i wait to ensure it doesnt mark the same ball twice
        }
        
    }
}