#include "City.h"
#include <iostream>

int main() {
    // Creating some cities
    CityNode city1(0, 0, "City1");
    CityNode city2(1, 1, "City2");
    CityNode city3(0, 4, "City3");
    CityNode city4(-1, 5, "City4");
    CityNode city5(2, 3, "City5");

    // Adding cities to the FindWays class
    FindWays findWays;
    findWays.addCity(&city1);
    findWays.addCity(&city2);
    findWays.addCity(&city3);
    findWays.addCity(&city4);
    findWays.addCity(&city5);

    // Connecting the cities
    connect(&city1, &city2, 1);
    connect(&city1, &city5, 10);
    connect(&city2, &city5, 2);
    connect(&city2, &city3, 2);
    connect(&city3, &city5, 2);
    connect(&city3, &city4, 1);
    connect(&city5, &city4, 10);

    // Using the Dijkstra's algorithm to find the shortest path from city1 to city3
    RouteOutput outputDijkstra = findWays.Dijkstra(&city1, &city3);

    // Displaying the result of Dijkstra's algorithm
    std::cout << "Shortest path from " << city1.name << " to " << city3.name << " using Dijkstra:\n";
    for (const auto& city : outputDijkstra.cities) {
        std::cout << city->name << " ";
    }
    std::cout << "\nTotal time: " << outputDijkstra.time << " units\n";

    // Create a set of cities to use
    std::unordered_set<CityNode*> citiesToUse = {&city1, &city4};

    // Disconnecting city1 and city4
    disconnect(&city1, &city4);

    // Setting citiesSet in FindWays using the created set
    findWays.setCitiesSet(citiesToUse);

    // Using the A* algorithm to find the shortest path from city4 to city1 with the updated set of cities
    RouteOutput outputAStar = findWays.A_star(&city4, &city1);

    // Displaying the result of A* algorithm
    std::cout << "\nShortest path from " << city4.name << " to " << city1.name << " using A* with updated set of cities:\n";
    if (outputAStar.time != -1) {
        for (const auto& city : outputAStar.cities) {
            std::cout << city->name << " ";
        }
        std::cout << "\nTotal time: " << outputAStar.time << " units" << std::endl;
    }
    else {
        std::cout << "No Path!" << std::endl;
    }

    return 0;
}
