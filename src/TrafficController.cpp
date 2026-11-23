#include "TrafficController.h"
#include <iostream>

void TrafficController::analyse(const std::vector<TrafficLane>& lanes) const {
    std::cout << "\n========== TRAFFIC ANALYSIS ==========\n";

    for (const auto& lane : lanes) {
        std::cout << "\nLane: " << lane.getName()
                  << "\nVehicles: " << lane.getVehicles()
                  << "\nAmbulance: " << (lane.hasAmbulance() ? "YES" : "NO")
                  << "\nDensity: " << lane.getDensity()
                  << "\nGreen Time: " << lane.getGreenTime() << " seconds\n";

        if (lane.getVehicles() >= 25) {
            std::cout << "WARNING: Heavy congestion!\n";
        }
    }

    int priority = selectPriorityLane(lanes);

    if (priority >= 0) {
        std::cout << "\nRecommended Priority: "
                  << lanes[priority].getName() << " Lane\n";

        if (lanes[priority].hasAmbulance()) {
            std::cout << "EMERGENCY: Ambulance priority activated!\n";
        }
    }

    std::cout << "======================================\n";
}

int TrafficController::selectPriorityLane(
    const std::vector<TrafficLane>& lanes) const {

    int selected = -1;

    // Ambulance always receives priority.
    for (int i = 0; i < static_cast<int>(lanes.size()); i++) {
        if (lanes[i].hasAmbulance()) {
            return i;
        }
    }

    // Otherwise, select the lane with the most vehicles.
    for (int i = 0; i < static_cast<int>(lanes.size()); i++) {
        if (selected == -1 ||
            lanes[i].getVehicles() > lanes[selected].getVehicles()) {
            selected = i;
        }
    }

    return selected;
}
