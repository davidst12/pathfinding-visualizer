#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Pathfinding/managers/IMapManager.hpp"

const std::vector<std::string> grid1 =
    { "XXX"
    , "XSX"
    , "XOX"
    , "XOX"
    , "XEX"
    , "XXX"
    };

const std::vector<std::string> grid2 =
    { "XXXXX"
    , "XSOOX"
    , "XOOOX"
    , "XOOOX"
    , "XOOEX"
    , "XXXXX"
    };

inline std::map<std::string, Grid> mock_maps = {{"map1", Grid("map1", grid1)}, {"map2", Grid("map2", grid2)}};

class MockMapManager : public IMapManager
{
public:
    virtual ~MockMapManager() = default;

    MOCK_METHOD(void, loadAllMaps, (const std::string&), (override));
    MOCK_METHOD((std::map<std::string, Grid>), getAllMaps, (), (override));
};