#include <vector>
#include <memory>
#include <cmath>

#include <iostream>
#include <chrono>

constexpr void Traverse(const int X,
              const int Y,
              const int ParentIndex,
              const int CheckIndex,
              std::vector<int> &CheckList,
              std::vector<int> &Paths,
              const std::vector<int> &Map,
              const std::pair<int, int> &MapDimensions
) {
    if ((X < 0 || X >= MapDimensions.first) || (Y < 0 || Y >= MapDimensions.second)) {
        return;
    }

    auto index = X + Y * MapDimensions.first;
    if (Map[index] == 0 || Paths[index] != 0) {
        return;
    }
    Paths[index] = ParentIndex;

    // Point or index is traversable, save it for later checking
    // Prioritize points to check
    CheckList[CheckIndex] = index;
}

bool FindPath(std::pair<int, int> Start,
              std::pair<int, int> Target,
              const std::vector<int> &Map,
              std::pair<int, int> MapDimensions,
              std::vector<int> &OutPath
) {
    auto epoch2 = std::chrono::high_resolution_clock::from_time_t(0);
    auto before2   = std::chrono::high_resolution_clock::now();
    auto before_mseconds2 = duration_cast<std::chrono::nanoseconds>(before2 - epoch2).count();


    // List containing which path point to check next. Most back element is the least heavy choice.
    std::vector<int> checkList(Map.size(), 0);
    int checkIndex = 0;
    // History for traversing back to where you started
    std::vector<int> paths(checkList);

    int x = Start.first;
    int y = Start.second;
    int startIndex = x + y * MapDimensions.first;
    int targetIndex = Target.first + Target.second * MapDimensions.first;
    paths[startIndex] = -1;
    int pathIndex = -1;

    auto now2   = std::chrono::high_resolution_clock::now();
    auto after_mseconds2 = duration_cast<std::chrono::nanoseconds>(now2 - epoch2).count();
    std::cout << "Time setup: " << (after_mseconds2 - before_mseconds2) << " ns" << std::endl;

    auto epoch1 = std::chrono::high_resolution_clock::from_time_t(0);
    auto before1   = std::chrono::high_resolution_clock::now();
    auto before_mseconds1 = duration_cast<std::chrono::nanoseconds>(before1 - epoch1).count();


    while (pathIndex != targetIndex) {

        // Check this points neighbors and order their weight afterwards.
        Traverse(x + 1, y, pathIndex, checkIndex, checkList, paths, Map, MapDimensions);
        Traverse(x - 1, y, pathIndex, checkIndex, checkList, paths, Map, MapDimensions);
        Traverse(x, y + 1, pathIndex, checkIndex, checkList, paths, Map, MapDimensions);
        Traverse(x, y - 1, pathIndex, checkIndex, checkList, paths, Map, MapDimensions);

        // Ready next point to check
        if (checkIndex < static_cast<int>(checkList.size())) {
            pathIndex = checkList[checkIndex];
            checkIndex++;

            x = pathIndex % MapDimensions.first;
            y = pathIndex / MapDimensions.first;
        } else {
            // No more routes to check
            return false;
        }
    }

    auto now1   = std::chrono::high_resolution_clock::now();
    auto after_mseconds1 = duration_cast<std::chrono::nanoseconds>(now1 - epoch1).count();
    std::cout << "Time run: " << (after_mseconds1 - before_mseconds1) << " ns" << std::endl;

    auto epoch = std::chrono::high_resolution_clock::from_time_t(0);
    auto before   = std::chrono::high_resolution_clock::now();
    auto before_mseconds = duration_cast<std::chrono::nanoseconds>(before - epoch).count();

    while (pathIndex != -1) {
        OutPath.insert(OutPath.begin(), pathIndex);
        pathIndex = paths[pathIndex];
    }

    auto now   = std::chrono::high_resolution_clock::now();
    auto after_mseconds = duration_cast<std::chrono::nanoseconds>(now - epoch).count();
    std::cout << "Time after: " << (after_mseconds - before_mseconds) << " ns" << std::endl;

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
//    std::vector<int> OutPath;



    int64_t dimension = 5000;
    std::vector<int> Map(dimension*dimension, 1);
    std::vector<int> OutPath;

//    std::vector<int> Map = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
//    std::vector<int> OutPath;

//    std::vector<int> Map = {0, 0, 1, 0, 1, 1, 1, 0, 1};
//    std::vector<int> OutPath;

    auto epoch = std::chrono::high_resolution_clock::from_time_t(0);
    auto before   = std::chrono::high_resolution_clock::now();
    auto before_mseconds = duration_cast<std::chrono::milliseconds>(before - epoch).count();

    std::cout << "Starting..." << std::endl;
//        auto foundPath = FindPath({0, 0}, {9, 10}, Map, {10, 11}, OutPath);
    auto foundPath = FindPath({0, 0}, {dimension-1, dimension-1}, Map, {dimension, dimension}, OutPath);
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
