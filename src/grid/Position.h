#pragma once

struct Position {
    int x;
    int y;

    Position(int x = 0, int y = 0) : x(x), y(y) {}  // Constructor

    // Podrías agregar operaciones si lo necesitas (por ejemplo, para comparaciones o sumas)
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};