#pragma once

#include "autons.hpp"

// declare all auton functions written in "autons.cpp"
// so that they can be referenced in different files.

void turnTesting(bool isCW);
void driveTesting(bool isForward);
void two_goal_RIGHT();
void two_goal_LEFT();
void one_goal_left();
void one_goal_right();
void solo_awp();
void one_goal();
void autonSkills();
void scoreBlocks(int count, bool isTop, int speed = 127);