#ifndef ROUTEOPTIMIZER_H
#define ROUTEOPTIMIZER_H

#include <vector>

class RouteOptimizer {
private:
    std::vector<std::vector<std::pair<int, int>>> graph;

public:
    RouteOptimizer();
    void addRoad(int from, int to, int distance);
    void findShortestRoute(int start, int destination) const;
};

#endif
