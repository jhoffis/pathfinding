#include <vector>
#include <cstdint>
#include <algorithm>

#include <iostream>
#include <chrono>

bool FindPath(std::pair<int, int> Start,
              std::pair<int, int> Target,
              const std::vector<int> &Map,
              std::pair<int, int> MapDimensions,
              std::vector<int> &OutPath
) {
    // List containing which path point to check next. The first elements are the closest to Start which ensures shortest path
    std::vector<int> checkList(Map.size(), -1);
    int checkIndex = 0;
    int checkPlacementIndex = 0;

    // History for traversing back to where you started
    std::vector<int> paths(checkList);

    int x = Start.first;
    int y = Start.second;
    int startIndex = x + y * MapDimensions.first;
    int targetIndex = Target.first + Target.second * MapDimensions.first;
    paths[startIndex] = startIndex;
    int pathIndex = startIndex;

    int_fast8_t horizontalCheck[4] = {1, -1, 0, 0};
    int_fast8_t verticalCheck[4] = {0, 0, 1, -1};

    while (pathIndex != targetIndex) {

        // Check this points neighbors
        for (int_fast8_t i = 0; i < 4; i++) {
            unsigned int xNeighbor = x + horizontalCheck[i];
            unsigned int yNeighbor = y + verticalCheck[i];
            if (xNeighbor >= MapDimensions.first || yNeighbor >= MapDimensions.second) {
                continue;
            }

            auto index = xNeighbor + yNeighbor * MapDimensions.first;
            if (Map[index] == 0 || paths[index] >= 0) {
                continue;
            }
            paths[index] = pathIndex;

            // Point or index is traversable, save it for later checking
            checkList[checkPlacementIndex] = static_cast<int>(index);
            checkPlacementIndex++;
        }

        // Ready next point to check
        if (checkIndex < checkPlacementIndex) {
            pathIndex = checkList[checkIndex];
            checkIndex++;

            x = pathIndex % MapDimensions.first;
            y = pathIndex / MapDimensions.first;
        } else {
            // No more routes to check
            return false;
        }
    }

    while (pathIndex != startIndex) {
        OutPath.emplace_back(pathIndex);
        pathIndex = paths[pathIndex];
    }
    std::reverse(OutPath.begin(), OutPath.end());

    return true;
}



int main() {
//    std::vector<int> Map = {
//            1, 0, 1, 0, 1, 1, 1, 0, 1, 1,
//            1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
//            1, 0, 0, 0, 1, 0, 0, 1, 1, 1,
//            1, 0, 1, 1, 1, 1, 1, 0, 1, 0,
//            1, 1, 1, 0, 0, 0, 1, 0, 1, 1,
//            0, 0, 1, 1, 1, 0, 1, 0, 0, 1,
//            1, 1, 0, 1, 0, 0, 1, 0, 1, 1,
//            0, 1, 0, 1, 1, 1, 1, 0, 1, 0,
//            0, 1, 1, 1, 0, 0, 1, 0, 1, 1,
//            0, 1, 0, 1, 1, 1, 1, 1, 0, 1,
//            0, 1, 1, 0, 1, 0, 0, 0, 1, 1,
//    };

    int64_t dimension = 5000;
    std::vector<int> Map(dimension*dimension, 1);


//    int64_t dimension = 5000;
//    std::vector<int> Map(dimension*dimension, 1);
//    int n = 0;
//    int y = 1;
//    int x = 0;
//    for (auto i = dimension + x; i < dimension*dimension; i++) {
//        if (n < dimension-1) {
//            n++;
//        } else {
//            y += 2;
//            if (x == 0)
//                x = 1;
//            else
//                x = 0;
//            i = dimension*y + x;
//            n = 1;
//        }
//        Map[i] = 0;
//    }

//    std::vector<int> Map = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};

//    std::vector<int> Map = {0, 0, 1, 0, 1, 1, 1, 0, 1};


    std::vector<int> OutPath;

    auto epoch = std::chrono::high_resolution_clock::from_time_t(0);
    auto before   = std::chrono::high_resolution_clock::now();
    auto before_mseconds = duration_cast<std::chrono::milliseconds>(before - epoch).count();

    std::cout << "Starting..." << std::endl;
//        auto foundPath = FindPath({0, 0}, {9, 10}, Map, {10, 11}, OutPath);
    auto foundPath = FindPath({0, 0}, {dimension-1, dimension-1}, Map, {dimension, dimension}, OutPath);
//    auto foundPath = FindPath({0, 0}, { n < y ? dimension - 1 : 0, dimension-1}, Map, {dimension, dimension}, OutPath);
//    auto foundPath = FindPath({0, 0}, {1, 2}, Map, {4, 3}, OutPath);
//    auto foundPath = FindPath({2, 0}, {0, 2}, Map, {3, 3}, OutPath);


    auto now   = std::chrono::high_resolution_clock::now();
    auto after_mseconds = duration_cast<std::chrono::milliseconds>(now - epoch).count();

    std::cout << "Found path: " << foundPath << std::endl;
//    if (foundPath) {
//        for (auto path: OutPath) {
//            std::cout << "Path: " << path << std::endl;
//        }
//        std::cout << "Length: " << OutPath.size() << std::endl;
//    }
    std::cout << "Time: " << (after_mseconds - before_mseconds) << " ms" << std::endl;

    return 0;
}
