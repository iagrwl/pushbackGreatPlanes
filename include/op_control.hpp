#pragma once

// declare all op control functions written in "op_control.cpp"
// so that they can be referenced in different files.


//other
void telemetry();

//drive
void handleArcade();
void handleTank();
void handleDriveMode(bool driveMode);


//handlers
void toggleScoringBar();
void handleIOCommands();
void handleScoringBarCommands();
void handleLoaderMechCommands();
void handleWingMechCommands();
void handleParkCommands();
void rumble();
