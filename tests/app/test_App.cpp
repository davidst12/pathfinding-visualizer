#include <gtest/gtest.h>

#include "MockMapManager.hpp"
#include "MockPlayer.hpp"
#include "Pathfinding/app/App.hpp"
#include "Pathfinding/player/IPlayer.hpp"
#include "Pathfinding/player/Player.hpp"

TEST(AppTest, TestRunApp) {
    std::map<std::string, Grid> maps = {};

    auto player = std::make_unique<MockPlayer>();
    auto map_manager = std::make_unique<MockMapManager>();
    EXPECT_CALL(*map_manager, loadAllMaps("assets/maps/")).Times(testing::AtLeast(1));
    EXPECT_CALL(*map_manager, getAllMaps())
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(maps));
    EXPECT_CALL(*player, setAvailableMaps(maps)).Times(testing::AtLeast(1));
    EXPECT_CALL(*player, processAppState(AppState::kMainMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::kExit));

    App app = App(std::move(player), std::move(map_manager));
    app.run();
}

TEST(AppTest, TestRunForwardApp) {
    std::map<std::string, Grid> maps = {};

    auto player = std::make_unique<MockPlayer>();
    auto map_manager = std::make_unique<MockMapManager>();
    EXPECT_CALL(*map_manager, loadAllMaps("assets/maps/")).Times(testing::AtLeast(1));
    EXPECT_CALL(*map_manager, getAllMaps())
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(maps));
    EXPECT_CALL(*player, setAvailableMaps(maps)).Times(testing::AtLeast(1));

    EXPECT_CALL(*player, processAppState(AppState::kMainMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::kContinue));
    EXPECT_CALL(*player, processAppState(AppState::kSelectTestModeMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::kContinue));
    EXPECT_CALL(*player, processAppState(AppState::kSelectAlgorithmMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::kContinue));
    EXPECT_CALL(*player, processAppState(AppState::kSelectMapMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::kContinue));
    EXPECT_CALL(*player, processAppState(AppState::kSelectExecutionMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::kContinue));
    EXPECT_CALL(*player, processAppState(AppState::kPlaying))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::kExit));

    App app = App(std::move(player), std::move(map_manager));
    app.run();
}

TEST(AppTest, TestRunBackwardApp) {
    std::map<std::string, Grid> maps = {};

    auto player = std::make_unique<MockPlayer>();
    auto map_manager = std::make_unique<MockMapManager>();
    EXPECT_CALL(*map_manager, loadAllMaps("assets/maps/")).Times(testing::AtLeast(1));
    EXPECT_CALL(*map_manager, getAllMaps())
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(maps));
    EXPECT_CALL(*player, setAvailableMaps(maps)).Times(testing::AtLeast(1));

    EXPECT_CALL(*player, processAppState(AppState::kMainMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::kContinue));
    EXPECT_CALL(*player, processAppState(AppState::kSelectTestModeMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::kContinue));
    EXPECT_CALL(*player, processAppState(AppState::kSelectAlgorithmMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::kContinue));
    EXPECT_CALL(*player, processAppState(AppState::kSelectMapMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::kContinue));
    EXPECT_CALL(*player, processAppState(AppState::kSelectExecutionMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::kContinue));
    EXPECT_CALL(*player, processAppState(AppState::kPlaying))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::kExit));

    App app = App(std::move(player), std::move(map_manager));
    app.run();
}