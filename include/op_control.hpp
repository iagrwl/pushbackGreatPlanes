#pragma once

// declare all op control functions written in "op_control.cpp"
// so that they can be referenced in different files.


void handleArcade();
void handleTank();
void handleDriveMode(bool isArcade);

void handleIntakeCommands();
void handleIndexerCommands();
void handleOuttakeCommands();


void rumble();
