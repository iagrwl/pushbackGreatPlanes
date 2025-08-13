#pragma once

#include "autons.hpp"

// declare all auton functions written in "autons.cpp"
// so that they can be referenced in different files.

void turnTesting(bool isCW);
void driveTesting(bool isForward);
void two_goal();
void one_goal();

void scoreBlocks(int count, bool isTop, int speed = 127);