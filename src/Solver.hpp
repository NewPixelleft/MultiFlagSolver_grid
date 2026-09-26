#pragma once

#include <algorithm>
#include <cstdint>

#include "Grid.hpp"
#include "Direction.hpp"
#include "_mz_points.hpp"

#define bitmask_bit uint16_t


namespace pt{

class Solution{
public:
    Solution()  = default;
    ~Solution() = default;

    Grid grid;
    void solve();

    std::vector <Dir> get_solution() const;
private:
    std::vector <Dir> solution;

    struct State{
        Point point;
        bitmask_bit mask;
    };

    struct Parent{
        Point point;
        bitmask_bit mask;
        Dir direction;
    };
};

};