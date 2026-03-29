#include <gtest/gtest.h>

#include "Pathfinding/managers/MapManager.hpp"


TEST(MapManagerTest, TestMainFunctionality) {
    
    std::unique_ptr<IMapManager> map_manager = std::make_unique<MapManager>();

    map_manager->loadAllMaps("tests/managers/test_maps");
    auto maps = map_manager->getAllMaps();

    EXPECT_EQ(maps.size(), 2);
    EXPECT_EQ(maps["Laberinto Delta"].getName(), "Laberinto Delta");
    EXPECT_EQ(maps["Mapa grande"].getName(), "Mapa grande");
}