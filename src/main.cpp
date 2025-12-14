#include "main.h"
#include "autons.hpp"
#include "op_control.hpp"
#include "pros/abstract_motor.hpp"
#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "robodash/api.h"
#include "setup.hpp"

bool tuneMode = false; // set true for green screen set false for competition
std::string testRoute = "S"; // select from S, 1GR, 1GL, AWP, 2GL, 2GR

/*
Sets variables - some are settings for the primary driver, some are holding times for controls.
*/
bool shouldLift = false; // internal bool for program to verify if ball in prime position
bool defaultDrive = true; //default toggler, true for arcade default and false for tank

int DHoldTime = 0; // counter for the seconds button is held for drive mode switch
int ParkHoldTime = 0; // counter for the seconds button is held for park macro
int CSSwitchHoldTime = 0;
int POHoldTime = 0;// counter for the park override button
bool isParkDown = false; // marks if the park bar is down

float DPDcurveMultiplier = 0.63; // changes the amount of curve the delay has
int FDPV = 120; // enter at 100 psi what the delay is
int LDPV = 40; // enter the lowest functioning psi is
float DPdelay = 0;


int BLUE_MAX = 230; // max blue hue
int BLUE_MIN = 190; // min blue hue
int RED_MAX = 20; // max red hue
int RED_MIN = 5; // min red hue

int OPP_MIN; // enemy alliance color min
int OPP_MAX; // enemy alliance color max


/*
Define tasks to be run in parallel here
Use the below format.
*/


/*
Tuning screen - screen that displays x,y theta + additional debug info. 
Only runs when tunemode is set to true
*/
void positionTracker() {
    while (true) {
    pros::lcd::print(1, "X: %.2f, Y: %.2f, Theta: %.2f", chassis.getPose().x, chassis.getPose().y, chassis.getPose().theta);
    pros::lcd::print(3, "applied DP delay %.2f", DPdelay);
    pros::lcd::print(4, "est. psi: %d", PSI);
    //pros::lcd::print(5, "colorval: %.2f", topOptical.get_hue());
    //pros::lcd::print(6, "alliance: %d", isRed ? "RED SELECTED" : "BLUE SELECTED");
    //pros::lcd::print(7, "NEW BOT CODE");
    pros::delay(10);
    }
}

float wallDistance(bool shouldPrint = false, bool useRightSensor = true) {
    // Sensor positions relative to robot center
    // Right: 4.5" right, 0.5" back → (+4.5, -0.5)
    // Left:  4.5" left, 1.5" back  → (-4.5, -1.5)
    float rightOffsetX = 4.5, rightOffsetY = -0.5;
    float leftOffsetX  = -4.5, leftOffsetY  = -1.5;

    // Get raw sensor distances in inches
    float rightDistMm = rightDistance.get();
    float leftDistMm = leftDistance.get();
    float rightSensorDist = rightDistMm / 25.4;
    float leftSensorDist = leftDistMm / 25.4;

    // Get robot angle
    float angDeg = chassis.getPose().theta;
    float angRad = angDeg * M_PI / 180.0;

    // Normalize angle to [0, 360)
    float angle = fmod(angDeg, 360.0);
    if (angle < 0) angle += 360.0;

    // At theta=0, robot faces +Y (forward)
    // Right sensor points +X (right), left sensor points -X (left)
    
    // Right sensor points 90° clockwise from robot heading (in world frame)
    float rightSensorAngle = angle + 90;
    if (rightSensorAngle >= 360) rightSensorAngle -= 360;

    // Left sensor points 90° counter-clockwise from robot heading
    float leftSensorAngle = angle - 90;
    if (leftSensorAngle < 0) leftSensorAngle += 360;

    // Calculate adjusted distances (sensor reading + offset magnitude in sensor direction)
    float rightAdjustedDist = rightSensorDist + sqrt(rightOffsetX * rightOffsetX + rightOffsetY * rightOffsetY);
    float leftAdjustedDist = leftSensorDist + sqrt(leftOffsetX * leftOffsetX + leftOffsetY * leftOffsetY);

    // Determine which wall each sensor faces and calculate robot position
    // Assuming field: X: [-72, 72], Y: [-72, 72] with walls at boundaries
    float rightWallPos = 0, leftWallPos = 0;
    float rightRobotPos = 0, leftRobotPos = 0;
    const char* rightWall = "";
    const char* leftWall = "";
    
    // Calculate angle deviation from perpendicular for each sensor
    float rightAngleDeviation = 0;
    float leftAngleDeviation = 0;

    // Right sensor - calculate perpendicular distance using cosine correction
    if (rightSensorAngle >= 315 || rightSensorAngle < 45) {  // Right wall (+X)
        rightWall = "Right(+X)";
        rightWallPos = 72;
        // Angle from perpendicular to wall (0° = perpendicular to +X wall)
        rightAngleDeviation = (rightSensorAngle > 180) ? (360 - rightSensorAngle) : rightSensorAngle;
        rightAdjustedDist = rightAdjustedDist * cos(rightAngleDeviation * M_PI / 180.0);
        rightRobotPos = rightWallPos - rightAdjustedDist;
    } else if (rightSensorAngle >= 45 && rightSensorAngle < 135) {  // Top wall (+Y)
        rightWall = "Top(+Y)";
        rightWallPos = 72;
        // Angle from perpendicular to wall (90° = perpendicular to +Y wall)
        rightAngleDeviation = fabs(90 - rightSensorAngle);
        rightAdjustedDist = rightAdjustedDist * cos(rightAngleDeviation * M_PI / 180.0);
        rightRobotPos = rightWallPos - rightAdjustedDist;
    } else if (rightSensorAngle >= 135 && rightSensorAngle < 225) {  // Left wall (-X)
        rightWall = "Left(-X)";
        rightWallPos = -72;
        // Angle from perpendicular to wall (180° = perpendicular to -X wall)
        rightAngleDeviation = fabs(180 - rightSensorAngle);
        rightAdjustedDist = rightAdjustedDist * cos(rightAngleDeviation * M_PI / 180.0);
        rightRobotPos = rightWallPos + rightAdjustedDist;
    } else {  // Bottom wall (-Y)
        rightWall = "Bottom(-Y)";
        rightWallPos = -72;
        // Angle from perpendicular to wall (270° = perpendicular to -Y wall)
        rightAngleDeviation = fabs(270 - rightSensorAngle);
        rightAdjustedDist = rightAdjustedDist * cos(rightAngleDeviation * M_PI / 180.0);
        rightRobotPos = rightWallPos + rightAdjustedDist;
    }

    // Left sensor - calculate perpendicular distance using cosine correction
    if (leftSensorAngle >= 315 || leftSensorAngle < 45) {  // Right wall (+X)
        leftWall = "Right(+X)";
        leftWallPos = 72;
        leftAngleDeviation = (leftSensorAngle > 180) ? (360 - leftSensorAngle) : leftSensorAngle;
        leftAdjustedDist = leftAdjustedDist * cos(leftAngleDeviation * M_PI / 180.0);
        leftRobotPos = leftWallPos - leftAdjustedDist;
    } else if (leftSensorAngle >= 45 && leftSensorAngle < 135) {  // Top wall (+Y)
        leftWall = "Top(+Y)";
        leftWallPos = 72;
        leftAngleDeviation = fabs(90 - leftSensorAngle);
        leftAdjustedDist = leftAdjustedDist * cos(leftAngleDeviation * M_PI / 180.0);
        leftRobotPos = leftWallPos - leftAdjustedDist;
    } else if (leftSensorAngle >= 135 && leftSensorAngle < 225) {  // Left wall (-X)
        leftWall = "Left(-X)";
        leftWallPos = -72;
        leftAngleDeviation = fabs(180 - leftSensorAngle);
        leftAdjustedDist = leftAdjustedDist * cos(leftAngleDeviation * M_PI / 180.0);
        leftRobotPos = leftWallPos + leftAdjustedDist;
    } else {  // Bottom wall (-Y)
        leftWall = "Bottom(-Y)";
        leftWallPos = -72;
        leftAngleDeviation = fabs(270 - leftSensorAngle);
        leftAdjustedDist = leftAdjustedDist * cos(leftAngleDeviation * M_PI / 180.0);
        leftRobotPos = leftWallPos + leftAdjustedDist;
    }

    if (shouldPrint) {
        pros::lcd::print(5, "R adj: %.2f\"  L adj: %.2f\"", 
                        rightAdjustedDist, leftAdjustedDist);
        pros::lcd::print(6, "R: %s  L: %s", rightWall, leftWall);
        pros::lcd::print(7, "R pos: %.2f  L pos: %.2f", 
                        rightRobotPos, leftRobotPos);
    }

    // Return the requested sensor's calculated robot position
    return useRightSensor ? rightRobotPos : leftRobotPos;
}

void wallTask(void* param) {
  while (true) {
    wallDistance(true, false);
    pros::delay(10);
  }
}

/*
Color sorting task - ejects opposite alliance rings
Runs continuously during autonomous and driver control
*/
void colorSort() {
    
    // fastest int time to 3ms
    topOptical.set_integration_time(3);

    // all code that should run consistently below here
    while (true) {
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
}



//2D array for RD auton selector
rd::Selector selector({
  {"solo AWP", &solo_awp},
  {"two goal LEFT",&two_goal_LEFT },
  {"one goal LEFT", &one_goal_left},
  {"one goal RIGHT", &one_goal_right},
  {"skilly", &autonSkills}
});

/*
Occurs when bot goes into init phase.
1. Checks if user wants tune screen and runs lines for it
2. Calls tasks to be run in parallel
3. Calibrates the drivetrain
4. Sets the braking mode(idle mode) to coast
5. Robodash code - dont mess w it prolly
*/
void initialize() {
    selector.focus();
    scoringBar.set_value(false);
    if (tuneMode == true){
        pros::lcd::initialize();
        pros::Task pos(&positionTracker);
    }
    
    // init color sensor
    topOptical.set_led_pwm(100);
    topOptical.disable_gesture();
    
    // sets text on controller. 
    //NOTE: slow updating text on controller
    controller.set_text(0, 0, ("goodluck! eternity."));

    // task callerss
    
    pros::Task telemetryTask(telemetry);
    //pros::Task colorSortTask(colorSort);
    pros::Task wall(wallTask);
    // calibrates drivetrain
    chassis.calibrate();
    
    // sets idle mode on drivetrain
    left_dt.set_brake_mode(pros::MotorBrake::coast);
    right_dt.set_brake_mode(pros::MotorBrake::coast);

    // robodash - dont mess w
    selector.on_select([](std::optional<rd::Selector::routine_t> routine) {
        if (routine == std::nullopt) {
            std::cout << "No routine selected" << std::endl;
        controller.print(2, 0, "select route");

        } else {
            std::cout << "Selected Routine: " << routine.value().name << std::endl;
        controller.print(2, 0, "run: %s", routine.value().name.c_str());

        }
    });
    
}

/*
Occurs when bot is in disable phase - when the autonomous and driving period are over.
1. Sets the scoring hood to lift to let blocks pass using inertia even when auton period is over.
*/

void disabled() {
    scoringBar.set_value(false);
  }

/*
Occurs when the bot is running the program
1. Shows the auton selector on the screen.
*/
//NOTE: the selected program is stored on the brains SD card for future runs
void competition_initialize() {
  selector.focus();
}

/*
Occurs when the 15s auton period is happening
1. Runs the auton selected by the selector.
NOTE: Color sort task is already running from initialize()
*/
void autonomous() {
  int hue = topOptical.get_hue();
  if (hue >= BLUE_MIN && hue <= BLUE_MAX){
    isRed = false;
  }
  else if (hue >= RED_MIN && hue <= RED_MAX){
    isRed = true;
  }
  
  if (tuneMode){
    if (testRoute == "S"){
        autonSkills();
    }
    else if (testRoute == "1GR")
    {
        one_goal_right();
    }
    else if (testRoute == "1GL")
    {
        one_goal_left();
    }
    else if (testRoute == "AWP")
    {
        solo_awp();
    }
    else if (testRoute == "2GL")
    {
        two_goal_LEFT();
    }
    else if (testRoute == "2GR")
    {
        two_goal_RIGHT();
    }

  }
  else{
  // runs auton from selected
  selector.run_auton();
  }
  
 }


void opcontrol() {
//chassis.setPose(15,-48,90);
  while (true) {

        //drivemode switcher
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
            DHoldTime += 20; // loop delay is 20ms
            if (DHoldTime >= 2000) { // must hold for 2000 ms for statement to pass
                defaultDrive = !defaultDrive; // toggle mode
                controller.rumble(".."); // give feedback
                DHoldTime = 0; // reset so it doesn't keep toggling
            }
        } else {
            DHoldTime = 0; // reset if released early
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y)) {
            CSSwitchHoldTime += 20; // loop delay is 20ms
            if (CSSwitchHoldTime >= 1000) { // must hold for 2000 ms for statement to pass
                isRed = !isRed; // toggle mode
                controller.rumble("-"); // give feedback
                CSSwitchHoldTime = 0; // reset so it doesn't keep toggling
            }
        } else {
            CSSwitchHoldTime = 0; // reset if released early
        }

        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
            POHoldTime += 10; // loop delay is 20ms
            if (POHoldTime >= 300) { // must hold for 2000 ms for statement to pass
                isParkDown = !isParkDown; // toggle mode
                controller.rumble("--"); // give feedback
                POHoldTime = 0; // reset so it doesn't keep toggling
                parkMech.set_value(isParkDown);
            }
        } else {
            POHoldTime = 0; // reset if released early
        }
        //double park macro
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT) and controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
                    ParkHoldTime += 10; // loop increments in 10ms

                    if (ParkHoldTime >= 30) { // must hold for 30+ ms
                        controller.rumble(".."); // give feedback to signal DP in progress
                        left_dt.move(-127);
                        right_dt.move(-127);
                        pros::delay(80);
                        left_dt.move(0);
                        right_dt.move(0);

                        while (shouldLift==false){
                            frontIntake.move(-60);
                            middleRollers.move(-100);
                            scoringRoller.move(-127);
                            controller.set_text(0, 0, "lifting bot");
                            if (bottomDistance.get_distance() >= 50 && bottomDistance.get_distance() <=80){
                                pros::delay(80);
                                frontIntake.move(0);
                                parkMech.set_value(true);
                                isParkDown = true;
                                float o = LDPV;
                                float t = FDPV;
                                float p = PSI;
                                float c = DPDcurveMultiplier;
                                float ratio = (100 - o != 0) ? (p - o) / (100.0 - o) : 0;
                                if (ratio < 0) ratio = 0;
                                DPdelay = t * pow(ratio, c);
                                pros::lcd::print(3, "DPDelay: %.2f", DPdelay);
                                pros::delay(DPdelay);

                                middleRollers.move(0);
                                scoringRoller.move(0);
                                shouldLift = true;
                            }

                        }

                        ParkHoldTime = 0; // reset so it doesn't keep toggling
                    }

                }
                else {
                    ParkHoldTime = 0; // reset if released early
                }
    
    // driver control functions go here
    handleDriveMode(defaultDrive);
    handleIOCommands();
    handleLoaderMechCommands();
    handleWingMechCommands();
    updatePSI();
    //handleParkCommands();
    // 20 ms delay to avoid strain on the brain
	pros::delay(20);
	}
}