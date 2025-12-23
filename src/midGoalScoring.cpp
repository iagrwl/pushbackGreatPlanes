#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "midGoalScoring.hpp"

void midGoalScoring(){
    frontIntake.move(127);
    middleRollers.move(127);
    scoringRoller.move(127); 

}