#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "distanceSensor.hpp"

float wallDistance(bool shouldPrint = false, bool useRightSensor = true) { 
    float rightOffsetX = 2.5, rightOffsetY = -1.0; 
    float leftOffsetX  = 1.5, leftOffsetY  = 0.0; 
 
    float offsetX = useRightSensor ? rightOffsetX : leftOffsetX; 
    float offsetY = useRightSensor ? rightOffsetY : leftOffsetY; 
 
    float distancemm = useRightSensor ? rightDistance.get() : leftDistance.get(); 
    float distanceIn = distancemm / 25.4 + offsetX; 
 
    float angDeg = chassis.getPose().theta; 
    float angRad = angDeg * M_PI / 180.0; 
 
    float angle = fmod(angDeg, 360.0); 
    if (angle < 0) angle += 360.0; 
 
    float rotatedX = offsetX * cos(angRad) - offsetY * sin(angRad); 
    float rotatedY = offsetX * sin(angRad) + offsetY * cos(angRad); 
 
    float correctedDist = 0; 
    float finalPos = 0; 
    bool isXAxis = true;  // true if measuring X position, false if measuring Y
 
    if (angle >= 315 || angle < 45) { 
        isXAxis = true;  // Facing forward/back walls (measuring Y)
        if (useRightSensor) { 
            correctedDist = -distanceIn * cos(angRad) - rotatedX; 
            finalPos = 71 - correctedDist; 
        } else { 
            correctedDist = distanceIn * cos(angRad) + rotatedX; 
            finalPos = correctedDist - 71; 
        } 
    } else if (angle >= 45 && angle < 135) { 
        isXAxis = false;  // Facing left/right walls (measuring X)
        if (useRightSensor) { 
            correctedDist = -distanceIn * sin(angRad) - rotatedY; 
            finalPos = correctedDist - 71; 
        } else { 
            correctedDist = distanceIn * sin(angRad) + rotatedY; 
            finalPos = 71 - correctedDist; 
        } 
    } else if (angle >= 135 && angle < 225) { 
        isXAxis = true;  // Facing forward/back walls (measuring Y)
        if (useRightSensor) { 
            correctedDist = distanceIn * cos(angRad) + rotatedX; 
            finalPos = -correctedDist - 71; 
        } else { 
            correctedDist = -distanceIn * cos(angRad) - rotatedX; 
            finalPos = 71 - correctedDist; 
        } 
    } else { 
        isXAxis = true;  // Facing left/right walls (measuring X)
        if (useRightSensor) { 
            correctedDist = distanceIn * sin(angRad) + rotatedY; 
            finalPos = 71 + correctedDist; 
        } else { 
            correctedDist = -distanceIn * sin(angRad) - rotatedY; 
            finalPos = correctedDist - 71; 
        } 
    } 
 
    // Get current pose
    lemlib::Pose currentPose = chassis.getPose();
    
    // Reset appropriate axis based on which walls we're measuring
    if (isXAxis) {
        // Sensors face left/right walls - reset X position
        chassis.setPose(finalPos, currentPose.y, currentPose.theta);
    } else {
        // Sensors face front/back walls - reset Y position
        chassis.setPose(currentPose.x, finalPos, currentPose.theta);
    }
 
    if (shouldPrint) { 
        pros::lcd::print(5, "Distance: %.2f", distanceIn); 
        pros::lcd::print(6, "Corrected: %.2f, Axis: %s", correctedDist, isXAxis ? "X" : "Y"); 
        pros::lcd::print(7, "Reset pos: %.2f", finalPos);
    } 
 
    return finalPos; 
}