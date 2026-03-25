#pragma once

#include <filesystem>
#include <map>
#include <nlohmann/json.hpp>
#include <string>

#include "Pathfinding/core/Grid.hpp"
#include "Pathfinding/managers/IMapManager.hpp"

class MapManager : public IMapManager {
   public:
    MapManager() = default;

    void loadAllMaps(const std::string& folderPath) override;
    std::map<std::string, Grid> getAllMaps() override;

   private:
    std::map<std::string, Grid> m_loaded_maps;

    void loadMap(const std::string& filePath);
};