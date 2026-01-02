#pragma once

#include "api.h"
#include "lemlib/api.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/motors.hpp"


// controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER); //controller

// drivetrain
inline pros::MotorGroup right_dt({7,-8 , 9}, pros::MotorGearset::blue);    // right side
inline pros::MotorGroup left_dt({-14,-16,15}, pros::MotorGearset::blue);  // left side

// drivetrain config for movement functions
// (wheel size, width, rpm, etc.)
inline lemlib::Drivetrain drivetrain(&left_dt,
							  &right_dt,
							  10.25,
							  lemlib::Omniwheel::NEW_325 * 24/23.68,
							  450,
							  2
);

inline pros::Imu imu(1);
// declare sensors needed for odom setup
/*inline pros::Rotation horizontalEnc(17);
inline pros::Rotation verticalEnc(18);
*/

inline pros::Rotation verticalEnc(-6);
//configure tracking wheels
//inline lemlib::TrackingWheel horizontalTrackingWheel(&horizontalEnc, lemlib::Omniwheel::NEW_2 * 24/25.2, -5);
inline lemlib::TrackingWheel verticalTrackingWheel(&verticalEnc, lemlib::Omniwheel::NEW_275, 0);
//inline lemlib::TrackingWheel verticalTrackingWheel(&verticalEnc, lemlib::Omniwheel::NEW_2 * 24/25.2, 1.5);
// configure entire odom setup
inline lemlib::OdomSensors sensors(&verticalTrackingWheel,
							nullptr,
							nullptr,
							nullptr,
							&imu
);

// lateral pid
inline lemlib::ControllerSettings lateral_controller(6.25, //proportional gain (kP) //5.5
                                            0, // integral gain (kI) //0.5
                                        25, // derivative gain (kD) //18
                                         1,//windup
                                           0.5, // small error range, in inches
                                          100, // small error range timeout, in milliseconds
                                           1, // large error1range, in inches
                                         750, // large error range timeout, in milliseconds
                                              5 // maximum acceleration (slew)
);

// angular pid
inline lemlib::ControllerSettings angular_controller(5, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              43.5, // derivative gain (kD)
                                              3.5, // anti windup
                                              0.5, // small error range, in degrees
                                                50, // small error range timeout, in milliseconds
                                              1.5, // large error range, in degrees
                                              200, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);


// look at  https://www.vexforum.com/t/expo-drive-lemlibs-implementation
// for drive curves explanation and interactive desmos graph

// input curve for throttle input during driver control
// inline lemlib::ExpoDriveCurve
//     throttle_curve(3,    // joystick deadband out of 127
//                    0,   // minimum output where drivetrain will move out of 127
//                    1.017 // expo curve gain
//     );
inline lemlib::ExpoDriveCurve throttle_curve(
    3,    // deadband
    0,    // min output
    1.0  
);
// input curve for steer input during driver control
// inline lemlib::ExpoDriveCurve
//     steer_curve(60,    // joystick deadband out of 127
//                 10,   // minimum output where drivetrain will move out of 127
//                 1.016 // expo curve gain
//     );
inline lemlib::ExpoDriveCurve steer_curve(
    3,    // deadband 
    0,    // min output
<<<<<<< Updated upstream
    1.0   // LINEAR
=======
    1.01   // LINEAR
>>>>>>> Stashed changes
);


inline lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors, // odometry sensors
                        &throttle_curve,
                        &steer_curve
);

// declare additional motors, sensors, and pnuematics here

//negative means regular direction is flipped
//intake groups
inline pros::Motor frontIntake(5, pros::MotorGearset::blue);
inline pros::Motor middleRollers(-10);
inline pros::Motor colorSortRoller(4);
inline pros::Motor scoringRoller(-11);

//extensions
// false means open and true means close
inline pros::adi::DigitalOut scoringGate('A');
inline pros::adi::DigitalOut loaderMech('B');
inline pros::adi::DigitalOut wingMech('C');
inline pros::adi::DigitalOut parkMech('D');

// clog sensors
inline pros::Optical topOptical(4);
inline pros::Distance bottomDistance(8);
inline pros::Distance leftDistance(17);
inline pros::Distance rightDistance(13);