#pragma once

#include <string>

struct Position {
    int x;
    int y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

    Position operator+(const Position& other) const {
        return Position(x + other.x, y + other.y);
    }

    std::string to_string() {
        return "{" + std::to_string(x) + " , " + std::to_string(y) + "}";
    }
};