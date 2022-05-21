#include <vector>
#include <memory>
#include <cmath>

#include <iostream>
#include <chrono>

struct MapPoint {
    int weight;
    int index;
    int parentIndex;
};

void Traverse(const int X,
              const int Y,
              const int ParentIndex,
              std::vector<MapPoint> &CheckList,
              int* Paths,
              const std::vector<int> &Map,
              const std::pair<int, int> &MapDimensions,
              const std::pair<int, int> &Start
) {
//    std::cout << "bounds" << std::endl;
    if ((X < 0 || X >= MapDimensions.first) || (Y < 0 || Y >= MapDimensions.second)) {
        return;
    }

    int index = X + Y * MapDimensions.first;
//    std::cout << "map" << std::endl;
    if (Map[index] == 0) {
        return;
    }
//    std::cout << "locked" << std::endl;
    if (Paths[index] != 0) {
        return;
    }
    Paths[index] = ParentIndex;

    // Point or index is traversable, save it for later checking
    MapPoint mapPoint{
            .weight = std::abs(Start.first - X) + std::abs(Start.second - Y),
            .index = index,
            .parentIndex = ParentIndex,
    };


    // Prioritize points to check
//    for (int i = static_cast<int>(CheckList.size()) - 1; i >= 0; i--) {
//        if (mapPoint.weight < CheckList[i].weight) {
//            CheckList.insert(CheckList.begin() + i + 1, mapPoint);
//    auto now   = std::chrono::high_resolution_clock::now();
//    auto after_mseconds = duration_cast<std::chrono::nanoseconds>(now - epoch).count();
//    std::cout << "Time: " << (after_mseconds - before_mseconds) << " ns" << std::endl;
//            return;
//        }
//    }
//    std::cout << "end " << std::endl;
//    auto epoch = std::chrono::high_resolution_clock::from_time_t(0);
//    auto before   = std::chrono::high_resolution_clock::now();
//    auto before_mseconds = duration_cast<std::chrono::nanoseconds>(before - epoch).count();
//    CheckList.insert(CheckList.begin(), mapPoint);
    CheckList.emplace_back(mapPoint);
//    auto now   = std::chrono::high_resolution_clock::now();
//    auto after_mseconds = duration_cast<std::chrono::nanoseconds>(now - epoch).count();
//    std::cout << "Time: " << (after_mseconds - before_mseconds) << " ns" << std::endl;

}

bool FindPath(std::pair<int, int> Start,
              std::pair<int, int> Target,
              const std::vector<int> &Map,
              std::pair<int, int> MapDimensions,
              std::vector<int> &OutPath
) {

    // List containing which path point to check next. Most back element is the least heavy choice.
    std::vector<MapPoint> checkList;
    int checkIndex = 0;
    // History for traversing back to where you started
    int* paths = new int[Map.size()];
    for (int i = 0; i < Map.size(); i++)
        paths[i] = 0;

    int x = Start.first;
    int y = Start.second;
    int startIndex = x + y * MapDimensions.first;
    paths[startIndex] = -1;
    int pathIndex = -1;

    while (x != Target.first || y != Target.second) {

        // Check this points neighbors and order their weight afterwards.
        // TODO How about doing while? Just keep going until you hit something?
        Traverse(x + 1, y, pathIndex, checkList, paths, Map, MapDimensions, Start);
        Traverse(x - 1, y, pathIndex, checkList, paths, Map, MapDimensions, Start);
        Traverse(x, y + 1, pathIndex, checkList, paths, Map, MapDimensions, Start);
        Traverse(x, y - 1, pathIndex, checkList, paths, Map, MapDimensions, Start);

        // Ready next point to check
        if (!checkList.empty()) {
            MapPoint &nearestPoint = checkList[checkIndex];
            checkIndex++;

            pathIndex = nearestPoint.index;

            x = pathIndex % MapDimensions.first;
            y = pathIndex / MapDimensions.first;

//            // Remove to not recheck and to avoid comparing weight to this
//            checkList.pop_back();
        } else {
            // No more routes to check
            return false;
        }
    }

    while (pathIndex != -1) {
        OutPath.insert(OutPath.begin(), pathIndex);
        pathIndex = paths[pathIndex];
    }

    delete[] paths;

    return true;
}



int main() {
//    std::vector<int> Map = {
//            1, 0, 1, 0, 1, 1, 1, 0, 1, 1,
//            1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
//            1, 0, 0, 1, 0, 0, 0, 1, 1, 1,
//            1, 0, 1, 1, 1, 1, 1, 0, 1, 0,
//            1, 1, 1, 0, 0, 0, 1, 0, 1, 1,
//            0, 0, 1, 1, 1, 0, 1, 0, 0, 1,
//            1, 1, 0, 1, 0, 0, 1, 0, 1, 1,
//            0, 1, 0, 1, 1, 1, 1, 0, 1, 0,
//            0, 1, 1, 1, 0, 0, 1, 0, 1, 1,
//            0, 1, 0, 1, 1, 1, 1, 1, 0, 1,
//            0, 1, 1, 0, 1, 0, 0, 0, 1, 1,
//    };
//    std::vector<int> OutPath;

    std::vector<int> Map;
    int64_t dimension = 5000;
    int64_t size = dimension*dimension;
    for (int64_t i = 0; i < size; i++) {
        Map.emplace_back(1);
    }
    std::vector<int> OutPath;

//    std::vector<int> Map = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
//    std::vector<int> OutPath;

    auto epoch = std::chrono::high_resolution_clock::from_time_t(0);
    auto before   = std::chrono::high_resolution_clock::now();
    auto before_mseconds = duration_cast<std::chrono::milliseconds>(before - epoch).count();

    std::cout << "Starting..." << std::endl;
//        auto foundPath = FindPath({0, 0}, {9, 10}, Map, {10, 11}, OutPath);
    auto foundPath = FindPath({0, 0}, {dimension-1, dimension-1}, Map, {dimension, dimension}, OutPath);
//    auto foundPath = FindPath({0, 0}, {1, 2}, Map, {4, 3}, OutPath);


    auto now   = std::chrono::high_resolution_clock::now();
    auto after_mseconds = duration_cast<std::chrono::milliseconds>(now - epoch).count();

    std::cout << "Found path: " << foundPath << std::endl;
    if (foundPath) {
        for (auto path: OutPath) {
            std::cout << "Path: " << path << std::endl;
        }
        std::cout << "Length: " << OutPath.size() << std::endl;
    }
    std::cout << "Time: " << (after_mseconds - before_mseconds) << " ms" << std::endl;

    return 0;
}
