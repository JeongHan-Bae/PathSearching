#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>
#include <queue>
#include <limits>
#include <algorithm>
#include <cmath>
#include <string>

// CityNode Declaration
struct CityNode {
    std::pair<int, int> position;
    std::string name;
    std::unordered_map<CityNode*, int> connections;

    // Constructors Declaration
    CityNode();
    CityNode(int x, int y, std::string  cityName);
    explicit CityNode(std::string  cityName);
};

// Connect & Disconnect Function Declaration
void connect(CityNode* a, CityNode* b, int time);

void disconnect(CityNode* a, CityNode* b);

// Function to Calculate Distance * tempo Declaration
double calc_dist(const std::pair<int, int>& position1, const std::pair<int, int>& position2);

// Output of Find-ways algorithms Declaration
struct RouteOutput {
    std::vector<CityNode*> cities;
    int time{};
};

// Class FindWays Declaration
class FindWays {
private:
    struct AStarComparator {
        bool operator()(const std::pair<int, CityNode*>& lhs, const std::pair<int, CityNode*>& rhs) {
            return lhs.first > rhs.first; // Min-heap based on the potential function
        }
    };
    std::unordered_set<CityNode*> citiesSet;
public:
    // Dijkstra Declaration
    RouteOutput Dijkstra(CityNode* depart, CityNode* arrive);

    // A* Declaration
    RouteOutput A_star(CityNode* depart, CityNode* arrive);

    // Function to add a city to the list of cities managed by the class
    void addCity(CityNode* city);

    void setCitiesSet(const std::unordered_set<CityNode*>& citiesToUse);

};
