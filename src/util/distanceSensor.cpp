#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "distanceSensor.hpp"

float wallDistance(bool shouldPrint = false, bool useRightSensor = true) { 
    float rightOffsetX = 2.5, rightOffsetY = 0.5; 
    float leftOffsetX  = 3.0, leftOffsetY  = -1.0; 
 
    float offsetX = useRightSensor ? rightOffsetX : leftOffsetX; 
    float offsetY = useRightSensor ? rightOffsetY : leftOffsetY; 
 
    float distancemm = useRightSensor ? rightDistance.get() : leftDistance.get(); 
    float distancecorr = distancemm / 25.4;
    float distanceIn = distancemm / 25.4 + offsetX; 
 
    float angDeg = chassis.getPose().theta; 
    float angRad = angDeg * M_PI / 180.0; 
 
    float angle = fmod(angDeg, 360.0); 
    if (angle < 0) angle += 360.0; 
 
    float rotatedX = offsetX * cos(angRad) - offsetY * sin(angRad); 
    float rotatedY = offsetX * sin(angRad) + offsetY * cos(angRad); 
 
    float correctedDist = 0; 
    float finalPos = 0; 
    bool isXAxis = true;
 
    if (angle >= 315 || angle < 45) { 
        isXAxis = true;
        if (useRightSensor) { 
            // Right sensor points to +X wall at 71
            correctedDist = distanceIn * fabs(cos(angRad)) + fabs(rotatedX); 
            finalPos = 71 - correctedDist; 
        } else { 
            // Left sensor points to -X wall at -71
            correctedDist = distanceIn * fabs(cos(angRad)) + fabs(rotatedX); 
            finalPos = -71 + correctedDist; 
        } 
    } else if (angle >= 45 && angle < 135) { 
        isXAxis = false;
        if (useRightSensor) { 
            // Right sensor points to -Y wall at -71
            correctedDist = distanceIn * fabs(sin(angRad)) + fabs(rotatedY); 
            finalPos = -71 + correctedDist; 
        } else { 
            // Left sensor points to +Y wall at 71
            correctedDist = distanceIn * fabs(sin(angRad)) + fabs(rotatedY); 
            finalPos = 71 - correctedDist; 
        } 
    } else if (angle >= 135 && angle < 225) { 
        isXAxis = true;
        if (useRightSensor) { 
            // Right sensor points to -X wall at -71
            correctedDist = distanceIn * fabs(cos(angRad)) + fabs(rotatedX); 
            finalPos = -71 + correctedDist; 
        } else { 
            // Left sensor points to +X wall at 71
            correctedDist = distanceIn * fabs(cos(angRad)) + fabs(rotatedX); 
            finalPos = 71 - correctedDist; 
        } 
    } else { 
        isXAxis = false;
        if (useRightSensor) { 
            // Right sensor points to +Y wall at 71
            correctedDist = distanceIn * fabs(sin(angRad)) + fabs(rotatedY); 
            finalPos = 71 - correctedDist; 
        } else { 
            // Left sensor points to -Y wall at -71
            correctedDist = distanceIn * fabs(sin(angRad)) + fabs(rotatedY); 
            finalPos = -71 + correctedDist; 
        } 
    } 
 
    lemlib::Pose currentPose = chassis.getPose();
    
    if (isXAxis) {
        chassis.setPose(finalPos, currentPose.y, currentPose.theta);
    } else {
        chassis.setPose(currentPose.x, finalPos, currentPose.theta);
    }
 
    if (shouldPrint) { 
        pros::lcd::print(5, "Distance: %.2f", distancecorr); 
        pros::lcd::print(6, "Corrected: %.2f, Axis: %s", correctedDist, isXAxis ? "X" : "Y"); 
        pros::lcd::print(7, "Reset pos: %.2f", finalPos);
    } 
 
    return finalPos; 
}