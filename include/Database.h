#ifndef DATABASE_H
#define DATABASE_H

#include "TrafficLane.h"
#include <sqlite3.h>
#include <string>

class Database {
private:
    sqlite3* db;

public:
    Database();
    ~Database();

    bool isConnected() const;
    void saveTraffic(const TrafficLane& lane);
    void showHistory() const;
};

#endif
