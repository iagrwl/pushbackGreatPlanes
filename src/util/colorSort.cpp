#include "lemlib/chassis/chassis.hpp"
#include "main.h"
#include "pros/distance.hpp"
#include "pros/llemu.hpp"
#include "setup.hpp"
#include "colorSort.hpp"

bool isColorSortOn = true;
bool isRed = false;
bool isColorPriority = false;

namespace {
// Tune these without touching logic.
constexpr int kProxMin = 10;      // minimum proximity to trust hue
constexpr int kProxMax = 90;      // maximum proximity to trust hue
constexpr int kEjectMinMs = 200;  // minimum reverse time once detected
constexpr int kEjectMaxMs = 600;  // safety timeout for eject
constexpr int kCooldownMs = 150;  // ignore new detections right after eject

constexpr int kOppBlueMin = 200;  // blue hue range
constexpr int kOppBlueMax = 210;
constexpr int kOppRedMin = 0;     // red hue range
constexpr int kOppRedMax = 10;
} // namespace


void colorSort(){
    static bool ejecting = false;
    static int32_t ejectStartMs = 0;
    static int32_t cooldownUntilMs = 0;

    if (!isColorSortOn) {
        isColorPriority = false;
        ejecting = false;
        pros::lcd::print(4, "colorsort off");
        pros::lcd::print(7, "");
        return;
    }

    const int hue = topOptical.get_hue();
    const int prox = topOptical.get_proximity();
    const bool ballPresent = (prox > kProxMin && prox < kProxMax);
    const bool oppositeDetected = ballPresent &&
        (isRed ? (hue > kOppBlueMin && hue < kOppBlueMax)
               : (hue > kOppRedMin && hue < kOppRedMax));

    const int32_t now = pros::millis();

    if (!ejecting) {
        if (oppositeDetected && now >= cooldownUntilMs) {
            ejecting = true;
            ejectStartMs = now;
        }
    } else {
        const int32_t elapsed = now - ejectStartMs;
        const bool minDone = elapsed >= kEjectMinMs;
        const bool maxDone = elapsed >= kEjectMaxMs;
        if ((minDone && !ballPresent) || maxDone) {
            ejecting = false;
            cooldownUntilMs = now + kCooldownMs;
        }
    }

    isColorPriority = ejecting;

    pros::lcd::print(4, "colorsort activated");
    pros::lcd::print(5, isRed ? "red alliance selected" : "blue alliance selected");
    pros::lcd::print(6, "color: %d prox: %d", hue, prox);

    if (ejecting) pros::lcd::print(7, "ejecting opposite");
    else if (oppositeDetected) pros::lcd::print(7, "opposite detected");
    else pros::lcd::print(7, "");
}
        
