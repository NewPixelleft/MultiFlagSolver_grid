#pragma once

#include "_mz_points.hpp"

namespace pt{
    enum class Dir : int{
        UP = 0,
        DOWN,
        RIGHT,
        LEFT
    };

    constexpr Point _dir[] = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };

    constexpr Point Direction(Dir dir) {
        return _dir[static_cast<int>(dir)];
    }
};