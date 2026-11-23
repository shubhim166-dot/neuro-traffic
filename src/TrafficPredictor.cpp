#include "TrafficPredictor.h"

double TrafficPredictor::predictNext(
    const std::vector<int>& readings) const {

    if (readings.empty()) return 0;

    double total = 0;

    for (int value : readings) {
        total += value;
    }

    return total / readings.size();
}
