#pragma once

#include "api.h"
#include "lemlib/api.hpp"
#include "pros/adi.hpp"
#include "pros/distance.hpp"

// general setup

// controller
inline pros::Controller controller(pros::E_CONTROLLER_MASTER); //controller

// drivetrain
inline pros::MotorGroup left_dt({-1, -2, 3}, pros::MotorGearset::blue);    // left side
inline pros::MotorGroup right_dt({8, 9, -10}, pros::MotorGearset::blue);  // right side

// drivetrain config for movement functions
// (wheel size, width, rpm, etc.)
inline lemlib::Drivetrain drivetrain(&left_dt,
							  &right_dt,
							  10.25,
							  lemlib::Omniwheel::NEW_325,
							  450,
							  2
);

// declare sensors needed for odom setup
inline pros::Rotation horizontalEnc(-15);
inline pros::Rotation verticalEnc(-16);
inline pros::Imu imu(5);

// configure tracking wheels
inline lemlib::TrackingWheel horizontalTrackingWheel(&horizontalEnc, lemlib::Omniwheel::NEW_2 * 24/25.2, 2.125);
inline lemlib::TrackingWheel verticalTrackingWheel(&verticalEnc, lemlib::Omniwheel::NEW_2 * 24/25.2, -0.625);

// configure entire odom setup
inline lemlib::OdomSensors sensors(&verticalTrackingWheel,
							nullptr,
							&horizontalTrackingWheel,
							nullptr,
							&imu
);

// lateral pid
inline lemlib::ControllerSettings lateral_controller(0, //proportional gain (kP)
                                            0, // integral gain (kI)
                                        0, // derivative gain (kD)
                                         0,//windup
                                           0, // small error range, in inches
                                          0, // small error range timeout, in milliseconds
                                           0, // large error1range, in inches
                                         0, // large error range timeout, in milliseconds
                                              0// maximum acceleration (slew)
);

// angular pid
inline lemlib::ControllerSettings angular_controller(0, // proportional gain (kP) was 3.5
                                              0, // integral gain (kI)
                                              0, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in degrees
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in degrees
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);


// look at  https://www.vexforum.com/t/expo-drive-lemlibs-implementation
// for drive curves explanation and interactive desmos graph

// input curve for throttle input during driver control
inline lemlib::ExpoDriveCurve
    throttle_curve(3,    // joystick deadband out of 127
                   0,   // minimum output where drivetrain will move out of 127
                   1.017 // expo curve gain
    );

// input curve for steer input during driver control
inline lemlib::ExpoDriveCurve
    steer_curve(3,    // joystick deadband out of 127
                0,   // minimum output where drivetrain will move out of 127
                1.017 // expo curve gain
    );


inline lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors, // odometry sensors
                        &throttle_curve,
                        &steer_curve
);

// declare additional motors, sensors, and pnuematics here
inline pros::Motor indexer(-11);

inline pros::Motor outtake(20);

inline pros::Motor intake(-12, pros::MotorGearset::blue);

inline pros::adi::DigitalOut pnuematic('E');

inline pros::Optical opticalSensor(1);
