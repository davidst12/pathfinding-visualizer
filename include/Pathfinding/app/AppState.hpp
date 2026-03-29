#pragma once

#include <cstdint>

enum class AppState : std::uint8_t {
    kMainMenu,
    kSelectTestModeMenu,
    kSelectAlgorithmMenu,
    kSelectMapMenu,
    kSelectExecutionMenu,
    kPlaying,
    kExit,
};