#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <queue>

#include "_mz_points.hpp"
#include "Status.hpp"

#define PointInt pt::

namespace pt {

const std::vector<Point> directions = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
};

constexpr bool REACHED = true;
constexpr bool NOT_REACHED = false;

class Grid {
public:
    Grid() = default;
    ~Grid() = default;

    StatusCode load(const std::vector<std::string>& _arg_grid);
    StatusCode load_from_file(std::ifstream& _file_grid);

    // // BFS: determines which flags are reachable from S
    // std::vector<Point> reachable_flags(); // -> Deactivated
    std::vector <Point> flaglists();

    char at(int r, int c) const;
    char at(Point p) const;
    bool in_bound(const int a, const int b) const;
    bool in_bound(const Point a) const;

    Point get_start() const;
    Point get_finish() const;

    int rows() const;
    int cols() const;

    int flag_count() const;
    int flag_id(Point p) const;

    bool valid(Point p) const;


    std::string getGridString();

private:
    std::vector<std::string> _grid;
    int n = 0;
    int m = 0;

    bool is_valid();
    bool is_char_valid(const char& c);

    bool walkable(char c) const;

    Point start = PNULL;
    Point finish = PNULL;

    std::vector<Point> flags;
};

}