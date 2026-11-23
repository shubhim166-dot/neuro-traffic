#ifndef TRAFFICCONTROLLER_H
#define TRAFFICCONTROLLER_H

#include "TrafficLane.h"
#include <vector>

class TrafficController {
public:
    void analyse(const std::vector<TrafficLane>& lanes) const;
    int selectPriorityLane(const std::vector<TrafficLane>& lanes) const;
};

#endif
