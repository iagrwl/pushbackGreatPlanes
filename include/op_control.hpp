#pragma once

// declare all op control functions written in "op_control.cpp"
// so that they can be referenced in different files.

//other
void stall_checker();

//drive
void handleArcade();
void handleTank();
void handleDriveMode(bool isArcade);

//handlers
void toggleScoringBar();
void handleIntakeCommands();
void handleOuttakeCommands();
void handleScoringBarCommands();
void rumble();
