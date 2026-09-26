#pragma once

#include "Solver.hpp"

#include <queue>
#include <vector>

namespace pt {

void Solution::solve() {
    int mask_count = 1 << grid.flag_count();

    std::vector visited(
        grid.rows(),
        std::vector(
            grid.cols(),
            std::vector<bool>(mask_count, false)
        )
    );

    std::vector parent(
        grid.rows(),
        std::vector(
            grid.cols(),
            std::vector<Parent>(mask_count)
        )
    );

    bitmask_bit all_flags =
        (1u << grid.flag_count()) - 1;

    std::queue<State> q;

    Point start = grid.get_start();

    q.push({start, 0});
    visited[start.r][start.c][0] = true;

    while (!q.empty()) {

        State current = q.front();
        q.pop();

        // We found the finish with every flag collected.
        if (current.point == grid.get_finish() &&
            current.mask == all_flags) {

            State trace = current;

            solution.clear();

            while (trace.point != start || trace.mask != 0) {

                Parent p =
                    parent[
                        trace.point.r
                    ][
                        trace.point.c
                    ][
                        trace.mask
                    ];

                solution.push_back(p.direction);

                trace.point = p.point;
                trace.mask = p.mask;
            }

            std::reverse(solution.begin(), solution.end());

            return;
        }

        for (Dir dir : {
            Dir::UP,
            Dir::DOWN,
            Dir::RIGHT,
            Dir::LEFT
        }) {

            Point next =
                current.point + Direction(dir);

            if (!grid.valid(next))
                continue;

            bitmask_bit new_mask = current.mask;

            int flag = grid.flag_id(next);

            if (flag != -1)
                new_mask |= (1u << flag);

            if (visited[next.r][next.c][new_mask])
                continue;

            visited[next.r][next.c][new_mask] = true;

            parent[next.r][next.c][new_mask] = {
                current.point,
                current.mask,
                dir
            };

            q.push({
                next,
                new_mask
            });
        }
    }
}
std::vector <Dir> Solution::get_solution() const{
    return solution;
}
}
