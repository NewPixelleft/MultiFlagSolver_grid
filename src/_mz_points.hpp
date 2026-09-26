#pragma once

namespace pt{

struct Point{
    int r = -128, c = -128;
};
constexpr Point PNULL = {-128, -128};

inline Point operator + (const Point a, const Point b) {
    return {
        a.r + b.r,
        a.c + b.c
    };
}
inline bool operator==(const Point a, const Point b) {
    return a.r == b.r && a.c == b.c;
}


};