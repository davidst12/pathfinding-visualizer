#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

#include "Pathfinding/core/Grid.hpp"

class IMapManager
{
public:
    virtual ~IMapManager() = default;

    virtual void loadAllMaps(const std::string& folderPath) = 0;
    virtual std::map<std::string, Grid> getAllMaps() = 0;

protected:
    IMapManager() = default; 
    
    IMapManager(const IMapManager&) = delete;
    IMapManager& operator=(const IMapManager&) = delete;
};