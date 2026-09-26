#include "Grid.hpp"

namespace pt {

std::string Grid::getGridString(){
    std::string returnval;
    for (const std::string &str: _grid){
        returnval += str + '\n';
    }
    return returnval;
}

bool Grid::is_char_valid(const char& c) {
    return c == 'X' ||
           c == 'S' ||
           c == 'F' ||
           c == 'G' ||
           c == '.' ||
           c == '#';
}

bool Grid::in_bound(const int a, const int b) const {
    return (a >= 0 && a < n) &&
           (b >= 0 && b < m);
}

bool Grid::in_bound(const Point a) const {
    return in_bound(a.r, a.c);
}

int Grid::flag_id(Point p) const {
    for (int i = 0; i < flags.size(); ++i) {
        if (flags[i] == p)
            return i;
    }

    return -1;
}

char Grid::at(int r, int c) const {
    if (!in_bound(r, c)) {
        return '\0';
    }

    return _grid[r][c];
}

char Grid::at(Point p) const {
    return at(p.r, p.c);
}

bool Grid::walkable(char c) const {
    return c == '.' ||
           c == 'S' ||
           c == 'F' ||
           c == 'G';
}

bool Grid::valid(Point p) const {
    return in_bound(p) && walkable(at(p));
}

Point Grid::get_start() const{
    return start;
}

Point Grid::get_finish() const{
    return finish;
}

int Grid::rows() const{
    return n;
}

int Grid::cols() const{
    return m;
}

int Grid::flag_count() const{
    return flags.size();
}

StatusCode Grid::load(const std::vector<std::string>& _arg_grid) {
    // flags.clear();
    start = PNULL;
    finish = PNULL;
    _grid.clear();
    n = 0;
    m = 0;

    if (_arg_grid.empty()) {
        return StatusCode::EMPTY_GRID_ERROR;
    }

    if (_arg_grid[0].empty()) {
        return StatusCode::EMPTY_GRID_ERROR;
    }

    int _n = static_cast<int>(_arg_grid.size());
    int _m = static_cast<int>(_arg_grid[0].length());

    for (int i = 0; i < _n; i++) {

        // Every row must have the same length
        if (static_cast<int>(_arg_grid[i].length()) != _m) {
            return StatusCode::VARIABLE_VECTOR_SIZE_ERROR;
        }

        for (int j = 0; j < _m; j++) {

            char c = _arg_grid[i][j];

            if (!is_char_valid(c)) {
                return StatusCode::MISUSED_CHARACTER_ERROR;
            }

            switch (c) {
            case 'S':
                if (start != PNULL) {
                    return StatusCode::MULTIPLE_START_ERROR;
                }

                start = {i, j};
                break;
            case 'G':
                if (finish != PNULL) {
                    return StatusCode::MULTIPLE_FINISH_ERROR;
                }

                finish = {i, j};
                break;
            case 'F':
                flags.push_back({i, j});
                break;

            default:
                break;
            }
        }
    }

    // S and G must exist
    if (start == PNULL) {
        return StatusCode::NO_START_ERROR;
    }

    if (finish == PNULL) {
        return StatusCode::NO_FINISH_ERROR;
    }

    // Only commit after validation succeeds
    _grid = _arg_grid;
    n = _n;
    m = _m;

    return StatusCode::SUCCESS;
}

StatusCode Grid::load_from_file(std::ifstream& _file) {

    if (!_file.is_open()) {
        return StatusCode::FILE_ERROR;
    }

    std::string _temp_string;
    std::vector<std::string> _arg_grid;

    while (std::getline(_file, _temp_string)) {
        _arg_grid.push_back(_temp_string);
    }

    return load(_arg_grid);
}

// std::vector<Point> Grid::reachable_flags() {

//     std::vector<std::vector<bool>>
//         check(n, std::vector<bool>(m, NOT_REACHED));

//     std::vector<Point> ret_flags;

//     std::queue<Point> q;

//     // Start BFS at S
//     q.push(start);
//     check[start.r][start.c] = REACHED;

//     while (!q.empty()) {

//         Point temp = q.front();
//         q.pop();

//         // Found a flag
//         if (_grid[temp.r][temp.c] == 'F') {
//             ret_flags.push_back(temp);
//         }

//         for (const Point& dir : directions) {

//             int nr = temp.r + dir.r;
//             int nc = temp.c + dir.c;

//             // Outside grid
//             if (!in_bound(nr, nc)) {
//                 continue;
//             }

//             // Already visited
//             if (check[nr][nc] == REACHED) {
//                 continue;
//             }

//             // Wall / mine
//             if (!walkable(_grid[nr][nc])) {
//                 continue;
//             }

//             // Mark BEFORE enqueueing
//             check[nr][nc] = REACHED;
//             q.push({nr, nc});
//         }
//     }

//     return ret_flags;
// }

};