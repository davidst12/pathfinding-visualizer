#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "Pathfinding/core/Grid.hpp"
#include "Pathfinding/managers/IMapManager.hpp"

class MapManager : public IMapManager
{
public:
    MapManager() = default;

    void loadAllMaps(const std::string& folderPath) override;
    std::map<std::string, Grid> getAllMaps() override;

private:
    std::map<std::string, Grid> loadedMaps;

    void loadMap(const std::string& filePath);
};