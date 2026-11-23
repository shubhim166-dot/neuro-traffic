#include "Database.h"
#include <iostream>

Database::Database() : db(nullptr) {
    if (sqlite3_open("neurotraffic.db", &db) != SQLITE_OK) {
        std::cerr << "Database connection failed: "
                  << sqlite3_errmsg(db) << "\n";
        if (db) sqlite3_close(db);
        db = nullptr;
        return;
    }

    const char* sql =
        "CREATE TABLE IF NOT EXISTS traffic_history ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "lane TEXT NOT NULL,"
        "vehicles INTEGER NOT NULL,"
        "ambulance TEXT NOT NULL,"
        "density TEXT NOT NULL,"
        "green_time INTEGER NOT NULL,"
        "recorded_at DATETIME DEFAULT CURRENT_TIMESTAMP);";

    char* error = nullptr;

    if (sqlite3_exec(db, sql, nullptr, nullptr, &error) != SQLITE_OK) {
        std::cerr << "Table creation error: " << error << "\n";
        sqlite3_free(error);
    }
}

Database::~Database() {
    if (db) sqlite3_close(db);
}

bool Database::isConnected() const {
    return db != nullptr;
}

void Database::saveTraffic(const TrafficLane& lane) {
    if (!db) {
        std::cout << "Database is not connected.\n";
        return;
    }

    const char* sql =
        "INSERT INTO traffic_history "
        "(lane, vehicles, ambulance, density, green_time) "
        "VALUES (?, ?, ?, ?, ?);";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) != SQLITE_OK) {
        std::cerr << "Could not prepare database statement.\n";
        return;
    }

    sqlite3_bind_text(statement, 1, lane.getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 2, lane.getVehicles());

    const char* emergency = lane.hasAmbulance() ? "YES" : "NO";
    sqlite3_bind_text(statement, 3, emergency, -1, SQLITE_STATIC);

    sqlite3_bind_text(statement, 4, lane.getDensity().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(statement, 5, lane.getGreenTime());

    if (sqlite3_step(statement) == SQLITE_DONE) {
        std::cout << "Saved " << lane.getName() << " lane record.\n";
    } else {
        std::cerr << "Failed to save traffic record.\n";
    }

    sqlite3_finalize(statement);
}

void Database::showHistory() const {
    if (!db) {
        std::cout << "Database is not connected.\n";
        return;
    }

    const char* sql =
        "SELECT id, lane, vehicles, ambulance, density, "
        "green_time, recorded_at FROM traffic_history ORDER BY id DESC;";

    sqlite3_stmt* statement = nullptr;

    if (sqlite3_prepare_v2(db, sql, -1, &statement, nullptr) != SQLITE_OK) {
        std::cerr << "Could not read database history.\n";
        return;
    }

    std::cout << "\n================ SAVED TRAFFIC HISTORY ================\n";

    bool found = false;

    while (sqlite3_step(statement) == SQLITE_ROW) {
        found = true;

        std::cout << "\nID: " << sqlite3_column_int(statement, 0)
                  << "\nLane: " << sqlite3_column_text(statement, 1)
                  << "\nVehicles: " << sqlite3_column_int(statement, 2)
                  << "\nAmbulance: " << sqlite3_column_text(statement, 3)
                  << "\nDensity: " << sqlite3_column_text(statement, 4)
                  << "\nGreen Time: " << sqlite3_column_int(statement, 5)
                  << " seconds\nRecorded At: "
                  << sqlite3_column_text(statement, 6) << "\n";
    }

    if (!found) std::cout << "No traffic records found yet.\n";

    std::cout << "=======================================================\n";

    sqlite3_finalize(statement);
}
