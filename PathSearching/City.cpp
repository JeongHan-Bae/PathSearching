#include "City.h"

// CityNode
CityNode::CityNode() : position({0, 0}), name("Unknown City") {}
CityNode::CityNode(int x, int y, std::string  cityName)
            : position({x, y}), name(std::move(cityName)) {}
CityNode::CityNode(std::string  cityName)
            : position({0, 0}), name(std::move(cityName)) {}

// Function to connect two cities with a given time
void connect(CityNode* a, CityNode* b, int time) {
    a->connections[b] = time;
    b->connections[a] = time;
}
// Function to disconnect two cities
void disconnect(CityNode* a, CityNode* b) {
    // Find and erase connection in a's connections
    auto it_a = a->connections.find(b);
    if (it_a != a->connections.end()) {
        a->connections.erase(it_a);
    }

    // Find and erase connection in b's connections
    auto it_b = b->connections.find(a);
    if (it_b != b->connections.end()) {
        b->connections.erase(it_b);
    }
}

// Function to Calculate Distance * tempo
double calc_dist(const std::pair<int, int>& position1, const std::pair<int, int>& position2) {
    return std::sqrt(std::pow(position1.first - position2.first, 2) + std::pow(position1.second - position2.second, 2));
}

// Dijkstra
RouteOutput FindWays::Dijkstra(CityNode* depart, CityNode* arrive) {
    // Initialization of distances to infinity
    std::unordered_map<CityNode*, int> distances;
    for (const auto& city : citiesSet) {
        distances[city] = std::numeric_limits<int>::max();
    }
    // Distance from the departure itself is always 0
    distances[depart] = 0;

    // Initialisation of Priority Queue
    std::priority_queue<std::pair<int, CityNode*>, std::vector<std::pair<int, CityNode*>>, std::greater<>> pq;
    pq.emplace(0, depart);

    // Initialization of the path traveled
    std::unordered_map<CityNode*, CityNode*> previous;

    // Algorithm of Dijkstra
    while (!pq.empty()) {
        auto current = pq.top().second;
        pq.pop();

        for (const auto& connection : current->connections) {
            auto neighbor = connection.first;
            int new_distance = distances[current] + connection.second;

            if (new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                previous[neighbor] = current;
                pq.emplace(new_distance, neighbor);
            }
        }
    }
    // Reconstruction of the path
    RouteOutput result;
    if (distances[arrive] == std::numeric_limits<int>::max()) {
        // No path found
        result.time = -1; // or any other value indicating no path
    } else {
        // Reconstruction of the path
        result.time = distances[arrive];

        CityNode* current = arrive;
        while (current != nullptr) {
            result.cities.push_back(current);
            current = previous[current];
        }
        std::reverse(result.cities.begin(), result.cities.end());
    }

    return result;
}
// A*
RouteOutput FindWays::A_star(CityNode* depart, CityNode* arrive) {
    // Initialization of distances to infinity
    std::unordered_map<CityNode*, int> distances;
    for (const auto& city : citiesSet) {
        distances[city] = std::numeric_limits<int>::max();
    }
    // Distance from the departure itself is always 0
    distances[depart] = 0;

    // Initialization of the priority queue with a custom comparator using the potential function
    std::priority_queue<std::pair<int, CityNode*>, std::vector<std::pair<int, CityNode*>>, AStarComparator> pq;
    pq.emplace(0, depart);

    // Initialization of the path traveled
    std::unordered_map<CityNode*, CityNode*> previous;

    // A* algorithm
    while (!pq.empty()) {
        auto current = pq.top().second;
        pq.pop();

        for (const auto& connection : current->connections) {
            auto neighbor = connection.first;
            int new_distance = distances[current] + connection.second;

            if (new_distance < distances[neighbor]) {
                distances[neighbor] = new_distance;
                previous[neighbor] = current;
                int potential = new_distance + static_cast<int>(calc_dist(neighbor->position, arrive->position));
                pq.emplace(potential, neighbor);
            }
        }
    }

    // Reconstruction of the path
    RouteOutput result;
    if (distances[arrive] == std::numeric_limits<int>::max()) {
        // No path found
        result.time = -1; // or any other value indicating no path
    } else {
        // Reconstruction of the path
        result.time = distances[arrive];

        CityNode* current = arrive;
        while (current != nullptr) {
            result.cities.push_back(current);
            current = previous[current];
        }
        std::reverse(result.cities.begin(), result.cities.end());
    }
    return result;
}

// Function to add a city to the set of cities managed by the class
void FindWays::addCity(CityNode* city) {
    citiesSet.insert(city);
}
// Function to set the citySet to a given set
void FindWays::setCitiesSet(const std::unordered_set<CityNode*>& citiesToUse) {
    citiesSet = citiesToUse;
}