#include "TrafficLane.h"
#include <algorithm>

TrafficLane::TrafficLane(std::string laneName, int count, bool emergency)
    : name(laneName), vehicles(std::max(0, count)), ambulance(emergency) {}

std::string TrafficLane::getName() const {
    return name;
}

int TrafficLane::getVehicles() const {
    return vehicles;
}

bool TrafficLane::hasAmbulance() const {
    return ambulance;
}

std::string TrafficLane::getDensity() const {
    if (vehicles < 10) return "LOW";
    if (vehicles < 25) return "MEDIUM";
    return "HIGH";
}

int TrafficLane::getGreenTime() const {
    return std::min(60, 15 + vehicles * 2);
}
