#ifndef TRAFFICLANE_H
#define TRAFFICLANE_H

#include <string>

class TrafficLane {
private:
    std::string name;
    int vehicles;
    bool ambulance;

public:
    TrafficLane(std::string laneName, int count, bool emergency);

    std::string getName() const;
    int getVehicles() const;
    bool hasAmbulance() const;

    std::string getDensity() const;
    int getGreenTime() const;
};

#endif
