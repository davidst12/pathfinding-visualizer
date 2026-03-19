#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Pathfinding/player/IPlayer.hpp"

class MockPlayer : public IPlayer
{
public:
    virtual ~MockPlayer() = default;

    MOCK_METHOD(AppStateEvent, processAppState, (AppState), (override));
    MOCK_METHOD(void, setAvailableMaps, ((std::map<std::string, Grid>) maps), (override));
};
