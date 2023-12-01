# PathSearching Library

## Overview

`PathSearching` is a C++ library designed to facilitate pathfinding algorithms for cities. The library includes a `CityNode` struct with functionalities for connecting and disconnecting cities, calculating distances, and implementing Dijkstra's and A* algorithms to find the shortest paths between cities. The library also provides a `RouteOutput` struct to represent the output of pathfinding algorithms.

## Project Structure

```markdown
- PathSearching (Library)
    - City.cpp
    - City.h
    - CMakeLists.txt
    - cmake-build-debug
        - libPathSearching.dll (Dynamic DLL)
        - ...

- Test (Testing Project)
    - CMakeLists.txt
    - main.cpp
    - cmake-build-debug
        - libPathSearching.dll (Copy of the Dynamic DLL)
        - ...
```

## Usage

To use the `PathSearching` library in your C++ project, follow these steps:

1. **Declare Library Path:**
   Declare the path to the `PathSearching` library in your project's `CMakeLists.txt` file.

    ```cmake
    set(PATH_SEARCHING_DIR "${CMAKE_SOURCE_DIR}/../PathSearching")
    set(PATH_SEARCHING_LIB_DIR "${PATH_SEARCHING_DIR}/cmake-build-debug")
    ```

2. **Include and Link:**
   Include the library directory and link against the `libPathSearching.dll` in your `CMakeLists.txt`.

    ```cmake
    target_include_directories(YourProject PRIVATE "${PATH_SEARCHING_DIR}")
    target_link_libraries(YourProject PRIVATE "${PATH_SEARCHING_LIB_DIR}/libPathSearching.dll")
    ```

3. **Copy DLL:**
   Copy the `libPathSearching.dll` to your project's executable directory (e.g., `Test/cmake-build-debug`).

4. **Include Header:**
   In your source files, include the `City.h` header file.

    ```cpp
    #include "City.h"
    ```

5. **Use City Struct:**
   Create instances of `CityNode` and utilize functions like `connect`, `disconnect`, and pathfinding algorithms like `Dijkstra` and `A_star`.

    ```cpp
    CityNode city1(0, 0, "City1");
    CityNode city2(1, 1, "City2");
    // ...

    connect(&city1, &city2, 1);
    // ...

    RouteOutput output = findWays.Dijkstra(&city1, &city2);
    ```

## Example - CMakeLists.txt (Test Project)

```cmake
cmake_minimum_required(VERSION 3.24)
project(Test)

set(CMAKE_CXX_STANDARD 17)

# Set the path to the PathSearching library
set(PATH_SEARCHING_DIR "${CMAKE_SOURCE_DIR}/../PathSearching")
set(PATH_SEARCHING_LIB_DIR "${PATH_SEARCHING_DIR}/cmake-build-debug")

add_executable(Test main.cpp)

# Include the directory containing City.h
target_include_directories(Test PRIVATE "${PATH_SEARCHING_DIR}")

# Link against the PathSearching library
target_link_libraries(Test PRIVATE "${PATH_SEARCHING_LIB_DIR}/libPathSearching.dll")

# Set the working directory for the Test executable
set_target_properties(Test PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
```

## Structures - CityNode and RouteOutput

```cpp
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
// Output of Find-ways algorithms Declaration
struct RouteOutput {
    std::vector<CityNode*> cities;
    int time{};
};
```

## Example - main.cpp

Refer to the provided `main.cpp` for an example of using the `PathSearching` library to create cities, connect them, and find the shortest paths using Dijkstra's and A* algorithms. Make sure to include the necessary headers for `CityNode` and `RouteOutput`.

```cpp
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

    // This makes sure that no path can be found in citiesToUse.

    // Setting citiesSet in FindWays using the created set
    findWays.setCitiesSet(citiesToUse);

    // Using the A* algorithm to find the shortest path from city4 to city1 with the updated set of cities
    RouteOutput outputAStar = findWays.A_star(&city4, &city1);

    // Displaying the result of A* algorithm
    std::cout << "\nShortest path from " << city4.name << " to " << city1.name << " using A* with updated set of cities:\n";
    // if no path, outputAStar.time is -1.
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
```

## License

This project is licensed under the [MIT License](MIT License).

## Contact Us

If you have any questions or concerns, feel free to contact us:

- **Email:** [mastropseudo@gmail.com](mailto:mastropseudo@gmail.com)
- **GitHub:** [JeongHan-Bae](https://github.com/JeongHan-Bae)

## Usage and Disclaimer

### Using the Library Source Files

You have the option to copy the source files directly into your project and use the library without relying on the dynamic link library (DLL). This can be done by copying the `City.cpp` and `City.h` files into your project.

### Distance Calculation Function

In the current implementation, the distance calculation function `calc_dist` in `City.cpp` is temporary and may not be as precise as desired. It will not change the final result but might not give the A* method a best speed. Please consider modifying it based on your specific requirements for improved speed.

```cpp
// Function to Calculate Distance * tempo
double calc_dist(const std::pair<int, int>& position1, const std::pair<int, int>& position2) {
    // Consider replacing this temporary implementation with a more precise version
    return std::sqrt(std::pow(position1.first - position2.first, 2) + std::pow(position1.second - position2.second, 2));
}
```

Feel free to adapt this structure and instructions according to your project's specific requirements.
