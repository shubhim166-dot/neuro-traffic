#ifndef TRAFFICPREDICTOR_H
#define TRAFFICPREDICTOR_H

#include <vector>

class TrafficPredictor {
public:
    double predictNext(const std::vector<int>& readings) const;
};

#endif
