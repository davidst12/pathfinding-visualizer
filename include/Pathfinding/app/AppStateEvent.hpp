#pragma once

#include <cstdint>

enum class AppStateEvent : std::int8_t {
    kUnhandled,
    kContinue,
    kBack,
    kExit,
};