#include <gtest/gtest.h>

#include "Pathfinding/app/App.hpp"
#include "Pathfinding/player/IPlayer.hpp"
#include "Pathfinding/player/Player.hpp"
#include "MockPlayer.hpp"
#include "MockMapManager.hpp"


TEST(AppTest, TestRunApp) {
    std::map<std::string, Grid> maps = {};
    
    auto player = std::make_unique<MockPlayer>();
    auto map_manager = std::make_unique<MockMapManager>();
    EXPECT_CALL(*map_manager, loadAllMaps("assets/maps/"))
        .Times(testing::AtLeast(1));
    EXPECT_CALL(*map_manager, getAllMaps())
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(maps));
    EXPECT_CALL(*player, setAvailableMaps(maps))
        .Times(testing::AtLeast(1));
    EXPECT_CALL(*player, processAppState(AppState::MainMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::Exit));

    App app = App(std::move(player), std::move(map_manager));
    app.run();
}

TEST(AppTest, TestRunForwardApp) {
    std::map<std::string, Grid> maps = {};
    
    auto player = std::make_unique<MockPlayer>();
    auto map_manager = std::make_unique<MockMapManager>();
    EXPECT_CALL(*map_manager, loadAllMaps("assets/maps/"))
        .Times(testing::AtLeast(1));
    EXPECT_CALL(*map_manager, getAllMaps())
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(maps));
    EXPECT_CALL(*player, setAvailableMaps(maps))
        .Times(testing::AtLeast(1));

    EXPECT_CALL(*player, processAppState(AppState::MainMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::Continue));
    EXPECT_CALL(*player, processAppState(AppState::SelectTestModeMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::Continue));
    EXPECT_CALL(*player, processAppState(AppState::SelectAlgorithmMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::Continue));
    EXPECT_CALL(*player, processAppState(AppState::SelectMapMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::Continue));
    EXPECT_CALL(*player, processAppState(AppState::SelectExecutionMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::Continue));
    EXPECT_CALL(*player, processAppState(AppState::Playing))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::Exit));

    App app = App(std::move(player), std::move(map_manager));
    app.run();
}

TEST(AppTest, TestRunBackwardApp) {
    std::map<std::string, Grid> maps = {};
    
    auto player = std::make_unique<MockPlayer>();
    auto map_manager = std::make_unique<MockMapManager>();
    EXPECT_CALL(*map_manager, loadAllMaps("assets/maps/"))
        .Times(testing::AtLeast(1));
    EXPECT_CALL(*map_manager, getAllMaps())
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(maps));
    EXPECT_CALL(*player, setAvailableMaps(maps))
        .Times(testing::AtLeast(1));

    EXPECT_CALL(*player, processAppState(AppState::MainMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::Continue));
    EXPECT_CALL(*player, processAppState(AppState::SelectTestModeMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::Continue));
    EXPECT_CALL(*player, processAppState(AppState::SelectAlgorithmMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::Continue));
    EXPECT_CALL(*player, processAppState(AppState::SelectMapMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::Continue));
    EXPECT_CALL(*player, processAppState(AppState::SelectExecutionMenu))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::Continue));
    EXPECT_CALL(*player, processAppState(AppState::Playing))
        .Times(testing::AtLeast(1))
        .WillOnce(testing::Return(AppStateEvent::Exit));

    App app = App(std::move(player), std::move(map_manager));
    app.run();
}