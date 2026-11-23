#include <iostream>
#include <vector>
#include <limits>
#include "TrafficLane.h"
#include "TrafficController.h"
#include "TrafficPredictor.h"
#include "RouteOptimizer.h"
#include "Database.h"

using namespace std;

int readInteger(const string& message, int minimum, int maximum) {
    int value;

    while (true) {
        cout << message;

        if (cin >> value && value >= minimum && value <= maximum) {
            return value;
        }

        cout << "Invalid input. Enter a number from "
             << minimum << " to " << maximum << ".\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void recordTraffic(Database& database,
                   TrafficController& controller,
                   TrafficPredictor& predictor) {

    vector<TrafficLane> lanes;
    vector<string> names = {"North", "South", "East", "West"};

    cout << "\n========== ENTER TRAFFIC DETAILS ==========\n";

    for (const string& name : names) {
        cout << "\n" << name << " Lane\n";

        int vehicles = readInteger("Number of vehicles (0-500): ", 0, 500);
        int emergency = readInteger("Ambulance present? (1 = Yes, 0 = No): ", 0, 1);

        lanes.emplace_back(name, vehicles, emergency == 1);
    }

    controller.analyse(lanes);

    cout << "\n========== TRAFFIC PREDICTION ==========\n";

    for (const auto& lane : lanes) {
        vector<int> readings;

        cout << "\nEnter three previous vehicle readings for "
             << lane.getName() << " lane.\n";

        for (int i = 1; i <= 3; i++) {
            readings.push_back(
                readInteger("Previous reading " + to_string(i) + ": ", 0, 500)
            );
        }

        double prediction = predictor.predictNext(readings);

        cout << "Estimated next reading: "
             << prediction << " vehicles\n";
    }

    cout << "\n========== SAVING TRAFFIC DATA ==========\n";

    for (const auto& lane : lanes) {
        database.saveTraffic(lane);
    }

    cout << "\nTraffic analysis completed.\n";
}

int main() {
    TrafficController controller;
    TrafficPredictor predictor;
    RouteOptimizer routeOptimizer;
    Database database;

    cout << "\n============================================\n";
    cout << "           NEUROTRAFFIC V5.0\n";
    cout << "      INTELLIGENT TRAFFIC MANAGEMENT\n";
    cout << "============================================\n";

    if (database.isConnected()) {
        cout << "Database: Connected successfully\n";
    } else {
        cout << "Database: Connection failed\n";
    }

    int choice;

    do {
        cout << "\n=============== MAIN MENU ===============\n";
        cout << "1. Record and analyse traffic\n";
        cout << "2. View saved traffic history\n";
        cout << "3. Find shortest route\n";
        cout << "4. Exit\n";
        cout << "=========================================\n";

        choice = readInteger("Enter your choice: ", 1, 4);

        switch (choice) {
            case 1:
                recordTraffic(database, controller, predictor);
                break;

            case 2:
                database.showHistory();
                break;

            case 3: {
                cout << "\nAvailable locations: 0, 1, 2, 3, 4\n";

                int start = readInteger("Enter starting location: ", 0, 4);
                int destination = readInteger("Enter destination: ", 0, 4);

                routeOptimizer.findShortestRoute(start, destination);
                break;
            }

            case 4:
                cout << "\nThank you for using NeuroTraffic!\n";
                cout << "System shutting down.\n";
                break;
        }

    } while (choice != 4);

    return 0;
}
