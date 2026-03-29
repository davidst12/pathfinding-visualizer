#include <gtest/gtest.h>

#include "MockMapManager.hpp"
#include "MockVisualization.hpp"
#include "Pathfinding/player/IPlayer.hpp"
#include "Pathfinding/player/Player.hpp"

TEST(PlayerTest, TestMainMenuState) {
    auto visualization = std::make_unique<MockVisualization>();
    EXPECT_CALL(*visualization, displayHome())
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(BasicScreenResult{AppStateEvent::kContinue}));
    std::unique_ptr<IPlayer> player_instance = std::make_unique<Player>(std::move(visualization));

    AppStateEvent result = player_instance->processAppState(AppState::kMainMenu);

    EXPECT_EQ(result, AppStateEvent::kContinue);
}

TEST(PlayerTest, TestSelectTestModeState) {
    auto visualization = std::make_unique<MockVisualization>();
    EXPECT_CALL(*visualization, displayTestModeSelectionScreen())
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(TestModeSelectionResult{AppStateEvent::kContinue,
                                                          AlgorithmTestMode::kSingleAlgorithm}));
    std::unique_ptr<IPlayer> player_instance = std::make_unique<Player>(std::move(visualization));

    AppStateEvent result = player_instance->processAppState(AppState::kSelectTestModeMenu);

    EXPECT_EQ(result, AppStateEvent::kContinue);
}

TEST(PlayerTest, TestSelectAlgorithmMenuState) {
    auto visualization = std::make_unique<MockVisualization>();
    EXPECT_CALL(*visualization, displayAlgorithmSelectionScreen(false))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AlgorithmSelectionResult{
            AppStateEvent::kContinue,
            std::set<AlgorithmType>{AlgorithmType::kAStar, AlgorithmType::kBFS, AlgorithmType::kDFS,
                                    AlgorithmType::kDijkstra}}));
    std::unique_ptr<IPlayer> player_instance = std::make_unique<Player>(std::move(visualization));

    AppStateEvent result = player_instance->processAppState(AppState::kSelectAlgorithmMenu);

    EXPECT_EQ(result, AppStateEvent::kContinue);
}

TEST(PlayerTest, TestSelectMapMenuState) {
    auto visualization = std::make_unique<MockVisualization>();
    EXPECT_CALL(*visualization, displayMapSelectionScreen(mock_maps))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(MapSelectionResult{AppStateEvent::kContinue, "Map1"}));
    std::unique_ptr<IPlayer> player_instance = std::make_unique<Player>(std::move(visualization));

    player_instance->setAvailableMaps(mock_maps);
    AppStateEvent result = player_instance->processAppState(AppState::kSelectMapMenu);

    EXPECT_EQ(result, AppStateEvent::kContinue);
}

TEST(PlayerTest, TestSelectExecutionMenuState) {
    auto visualization = std::make_unique<MockVisualization>();
    EXPECT_CALL(*visualization, displayExecutionSelectionScreen())
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(
            ExecutionSelectionResult{AppStateEvent::kContinue, AlgorithmExecutionMode::kInstant}));
    std::unique_ptr<IPlayer> player_instance = std::make_unique<Player>(std::move(visualization));

    AppStateEvent result = player_instance->processAppState(AppState::kSelectExecutionMenu);

    EXPECT_EQ(result, AppStateEvent::kContinue);
}
