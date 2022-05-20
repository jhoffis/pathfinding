#include <iostream>
#include <vector>
#include <memory>

struct MapPoint {
    int weight;
    int index;
};

void Traverse(const int X,
              const int Y,
              std::vector<MapPoint> &CheckList,
              std::vector<int> &LockedMap,
              const std::vector<int> &Map,
              const std::pair<int, int> &MapDimensions,
              const std::pair<int, int> &Target
) {
    if ((X < 0 || X >= MapDimensions.first) || (Y < 0 || Y >= MapDimensions.second)) {
        return;
    }

    int index = X + Y * MapDimensions.first;

    if (Map[index] == 0) {
        return;
    }

    for (int locked: LockedMap) {
        if (locked == index) {
            return;
        }
    }
    LockedMap.push_back(index);

    // Point or index is traversable, save it for later checking
    MapPoint mapPoint{
            .weight = std::abs(Target.first - X) + std::abs(Target.second - Y),
            .index = index,
    };

    // Prioritize points to check
    for (int i = static_cast<int>(CheckList.size()) - 1; i >= 0; i--) {
        if (mapPoint.weight < CheckList[i].weight) {
            CheckList.insert(CheckList.begin() + i + 1, mapPoint);
            return;
        }
    }
    CheckList.insert(CheckList.begin(), mapPoint);
}

bool FindPath(std::pair<int, int> Start,
              std::pair<int, int> Target,
              const std::vector<int> &Map,
              std::pair<int, int> MapDimensions,
              std::vector<int> &OutPath
) {

    // List containing which path point to check next. Most back element is the least heavy choice.
    std::vector<MapPoint> checkList;
    // To not recheck points
    std::vector<int> lockedMap;
    // History for traversing back to where you started
    auto paths = std::make_unique<int[]>(static_cast<size_t>(MapDimensions.first * MapDimensions.second));
    //for (int i = 0; i < Map.size(); i++)
    //    paths[i] = -1;

    int smallestWeight = INT32_MAX;
    int x = Start.first;
    int y = Start.second;
    int startIndex = x + y * MapDimensions.first;
    int pathIndex = startIndex;
    lockedMap.emplace_back(pathIndex);

    while (x != Target.first || y != Target.second) {

        // Check this points neighbors and order their weight afterwards.
        Traverse(x + 1, y, checkList, lockedMap, Map, MapDimensions, Target);
        Traverse(x - 1, y, checkList, lockedMap, Map, MapDimensions, Target);
        Traverse(x, y + 1, checkList, lockedMap, Map, MapDimensions, Target);
        Traverse(x, y - 1, checkList, lockedMap, Map, MapDimensions, Target);

        // Ready next point to check
        if (!checkList.empty()) {
            MapPoint &nearestPoint = checkList.back();

            int parentIndex = pathIndex;
            pathIndex = nearestPoint.index;
            paths[pathIndex] = parentIndex;

            x = pathIndex % MapDimensions.first;
            y = pathIndex / MapDimensions.first;

            if (nearestPoint.weight <= smallestWeight) {
                smallestWeight = nearestPoint.weight;
            } else {
                // Update parents
                std::vector<int> improvedPath;
                FindPath(Start, {x, y}, Map, MapDimensions, improvedPath);

                    int parent = startIndex;
                    for (int point: improvedPath) {
                        paths[point] = parent;
                        parent = point;
                    }
            }

            // Remove to not recheck and to avoid comparing weight to this
            checkList.pop_back();
        } else {
            // No more routes to check
            return false;
        }
    }

    while (pathIndex != startIndex) {
        OutPath.insert(OutPath.begin(), pathIndex);
        pathIndex = paths[pathIndex];
    }

    return true;
}


int main() {
    std::vector<int> Map = {
            1, 0, 1, 0, 1, 1, 1, 0, 1, 1,
            1, 0, 1, 1, 1, 0, 1, 1, 0, 1,
            1, 0, 0, 1, 0, 0, 0, 1, 1, 1,
            1, 0, 1, 1, 1, 1, 1, 0, 1, 0,
            1, 1, 1, 0, 0, 0, 1, 0, 1, 1,
            0, 0, 1, 1, 1, 0, 1, 0, 0, 1,
            1, 1, 0, 1, 0, 0, 1, 0, 1, 1,
            0, 1, 0, 1, 1, 1, 1, 0, 1, 0,
            0, 1, 1, 1, 0, 0, 1, 0, 1, 1,
            0, 1, 0, 1, 1, 1, 1, 1, 0, 1,
            0, 1, 1, 0, 1, 0, 0, 0, 1, 1,
    };
    std::vector<int> OutPath;
    auto foundPath = FindPath({0, 0}, {9, 10}, Map, {10, 11}, OutPath);

    std::cout << "Found path: " << foundPath << std::endl;
    if (foundPath) {
        for (auto path: OutPath) {
            std::cout << "Path: " << path << std::endl;
        }
        std::cout << "Length: " << OutPath.size() << std::endl;
    }

    return 0;
}
