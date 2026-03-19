#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Pathfinding/visualization/IVisualization.hpp"
#include "Pathfinding/visualization/ScreenResult.hpp"

class MockVisualization : public IVisualization
{
public:
    virtual ~MockVisualization() = default;

    MOCK_METHOD(BasicScreenResult, displayHome, (), (override));
    MOCK_METHOD(TestModeSelectionResult, displayTestModeSelectionScreen, (), (override));
    MOCK_METHOD(AlgorithmSelectionResult, displayAlgorithmSelectionScreen, (bool allow_multiple_selection), (override));
    MOCK_METHOD(MapSelectionResult, displayMapSelectionScreen, ((std::map<std::string, Grid>) maps), (override));
    MOCK_METHOD(ExecutionSelectionResult, displayExecutionSelectionScreen, (), (override));
    MOCK_METHOD(BasicScreenResult, displaySimulationScreen, (std::vector<AlgorithmResult> results, bool wait_for_input), (override));
};
