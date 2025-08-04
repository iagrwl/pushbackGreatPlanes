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
inline pros::MotorGroup right_dt({10, 9, -8}, pros::MotorGearset::blue);  // right side

// drivetrain config for movement functions
// (wheel size, width, rpm, etc.)
inline lemlib::Drivetrain drivetrain(&left_dt,
							  &right_dt,
							  10.125,
							  lemlib::Omniwheel::NEW_325,
							  450,
							  2
);

// declare sensors needed for odom setup
inline pros::Rotation horizontalEnc(14);
inline pros::Rotation verticalEnc(4);
inline pros::Imu imu(19);

// configure tracking wheels
inline lemlib::TrackingWheel horizontalTrackingWheel(&horizontalEnc, lemlib::Omniwheel::NEW_2 * 24/25.2, -5);
inline lemlib::TrackingWheel verticalTrackingWheel(&verticalEnc, lemlib::Omniwheel::NEW_2 * 24/25.2, -0.475);

// configure entire odom setup
inline lemlib::OdomSensors sensors(&verticalTrackingWheel,
							nullptr,
							&horizontalTrackingWheel,
							nullptr,
							&imu
);

// lateral pid
inline lemlib::ControllerSettings lateral_controller(6, //proportional gain (kP)
                                            0, // integral gain (kI)
                                        18, // derivative gain (kD)
                                         0,//windup
                                           0, // small error range, in inches
                                          0, // small error range timeout, in milliseconds
                                           0, // large error1range, in inches
                                         0, // large error range timeout, in milliseconds
                                              10// maximum acceleration (slew)
);

// angular pid
inline lemlib::ControllerSettings angular_controller(3.3, // proportional gain (kP) was 3.5
                                              0.4, // integral gain (kI)
                                              20, // derivative gain (kD)
                                              3.5, // anti windup
                                              0.5, // small error range, in degrees
                                              75, // small error range timeout, in milliseconds
                                              2, // large error range, in degrees
                                              750, // large error range timeout, in milliseconds
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
inline pros::Motor indexer(11);

inline pros::Motor outtake(20);

inline pros::Motor intake(-12, pros::MotorGearset::blue);

inline pros::adi::DigitalOut loaderMech('A');

inline pros::Optical opticalSensor(1);

inline pros::Distance leftDistance(16);

inline pros::Distance rightDistance(15);
