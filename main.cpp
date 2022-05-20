#include "point_based.cpp"

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
