#include <gtest/gtest.h>

#include "Pathfinding/player/IPlayer.hpp"
#include "Pathfinding/player/Player.hpp"
#include "MockVisualization.hpp"
#include "MockMapManager.hpp"


TEST(PlayerTest, TestMainMenuState) {
    
    auto visualization = std::make_unique<MockVisualization>();
    EXPECT_CALL(*visualization, displayHome())
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(BasicScreenResult{AppStateEvent::Continue}));
    std::unique_ptr<IPlayer> player_instance = std::make_unique<Player>(std::move(visualization));

    AppStateEvent result = player_instance->processAppState(AppState::MainMenu);

    EXPECT_EQ(result, AppStateEvent::Continue);
}

TEST(PlayerTest, TestSelectTestModeState) {
    
    auto visualization = std::make_unique<MockVisualization>();
    EXPECT_CALL(*visualization, displayTestModeSelectionScreen())
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(TestModeSelectionResult{AppStateEvent::Continue, AlgorithmTestMode::SingleAlgorithm}));
    std::unique_ptr<IPlayer> player_instance = std::make_unique<Player>(std::move(visualization));

    AppStateEvent result = player_instance->processAppState(AppState::SelectTestModeMenu);

    EXPECT_EQ(result, AppStateEvent::Continue);
}

TEST(PlayerTest, TestSelectAlgorithmMenuState) {
    
    auto visualization = std::make_unique<MockVisualization>();
    EXPECT_CALL(*visualization, displayAlgorithmSelectionScreen(false))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(
            AlgorithmSelectionResult{
                AppStateEvent::Continue,
                std::set<AlgorithmType> {
                    AlgorithmType::AStar,
                    AlgorithmType::BFS,
                    AlgorithmType::DFS,
                    AlgorithmType::Dijkstra}}));
    std::unique_ptr<IPlayer> player_instance = std::make_unique<Player>(std::move(visualization));

    AppStateEvent result = player_instance->processAppState(AppState::SelectAlgorithmMenu);

    EXPECT_EQ(result, AppStateEvent::Continue);
}

TEST(PlayerTest, TestSelectMapMenuState) {
    
    auto visualization = std::make_unique<MockVisualization>();
    EXPECT_CALL(*visualization, displayMapSelectionScreen(mock_maps))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(MapSelectionResult{AppStateEvent::Continue, "Map1"}));
    std::unique_ptr<IPlayer> player_instance = std::make_unique<Player>(std::move(visualization));
    
    player_instance->setAvailableMaps(mock_maps);
    AppStateEvent result = player_instance->processAppState(AppState::SelectMapMenu);

    EXPECT_EQ(result, AppStateEvent::Continue);
}

TEST(PlayerTest, TestSelectExecutionMenuState) {
    
    auto visualization = std::make_unique<MockVisualization>();
    EXPECT_CALL(*visualization, displayExecutionSelectionScreen())
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(ExecutionSelectionResult{AppStateEvent::Continue, AlgorithmExecutionMode::Instant}));
    std::unique_ptr<IPlayer> player_instance = std::make_unique<Player>(std::move(visualization));
    
    AppStateEvent result = player_instance->processAppState(AppState::SelectExecutionMenu);

    EXPECT_EQ(result, AppStateEvent::Continue);
}
