#include "RouteOptimizer.h"
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <limits>
#include <algorithm>

RouteOptimizer::RouteOptimizer() : graph(5) {
    addRoad(0, 1, 4);
    addRoad(0, 2, 2);
    addRoad(1, 2, 1);
    addRoad(1, 3, 5);
    addRoad(2, 3, 8);
    addRoad(2, 4, 10);
    addRoad(3, 4, 2);
}

void RouteOptimizer::addRoad(int from, int to, int distance) {
    if (from < 0 || to < 0 ||
        from >= static_cast<int>(graph.size()) ||
        to >= static_cast<int>(graph.size()) || distance < 0) {
        return;
    }

    graph[from].push_back({to, distance});
    graph[to].push_back({from, distance});
}

void RouteOptimizer::findShortestRoute(
    int start, int destination) const {

    const int n = static_cast<int>(graph.size());

    if (start < 0 || destination < 0 || start >= n || destination >= n) {
        std::cout << "Invalid location.\n";
        return;
    }

    const int INF = std::numeric_limits<int>::max();

    std::vector<int> distance(n, INF);
    std::vector<int> parent(n, -1);

    using Node = std::pair<int, int>;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [currentDistance, node] = pq.top();
        pq.pop();

        if (currentDistance != distance[node]) continue;

        for (const auto& road : graph[node]) {
            int next = road.first;
            int weight = road.second;

            if (distance[node] + weight < distance[next]) {
                distance[next] = distance[node] + weight;
                parent[next] = node;
                pq.push({distance[next], next});
            }
        }
    }

    if (distance[destination] == INF) {
        std::cout << "No route found.\n";
        return;
    }

    std::vector<int> path;

    for (int node = destination; node != -1; node = parent[node]) {
        path.push_back(node);
    }

    std::reverse(path.begin(), path.end());

    std::cout << "\n========== SHORTEST ROUTE ==========\n";
    std::cout << "Route: ";

    for (size_t i = 0; i < path.size(); i++) {
        std::cout << "Location " << path[i];

        if (i + 1 < path.size()) std::cout << " -> ";
    }

    std::cout << "\nTotal Distance: " << distance[destination] << " km\n";
    std::cout << "Algorithm: Dijkstra's Shortest Path\n";
    std::cout << "Note: This is a simulated road network.\n";
    std::cout << "===================================\n";
}
