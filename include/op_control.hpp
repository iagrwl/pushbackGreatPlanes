#pragma once

// declare all op control functions written in "op_control.cpp"
// so that they can be referenced in different files.

//other
void testing_sequence();
void pullTempsTask(void* param); 
void pullAmpsTask(void* param); 

//drive
void handleArcade();
void handleTank();
void handleDriveMode(bool isArcade);

//handlers
void toggleScoringBar();
void handleIntakeCommands();
void handleOuttakeCommands();
void rumble();
