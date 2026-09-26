
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "Grid.hpp"
#include "Solver.hpp"
#include "Status.hpp"
#include "_mz_points.hpp"

using namespace pt;

// ---- DEFINITIONS AND MACROS ---- //
#define mainfunction int
#define loopfunction bool

#define repeatloop false
#define stoploop true

#define el '\n'

using std::cout, std::cin;


// ---- SUPPORTING FUNCTION ---- //

std::string parseDirection(Dir dir) {
    std::string retval;

    switch (dir) {
        case Dir::UP:
            retval = "DOWN";
            break;
        case Dir::DOWN:
            retval = "UP";
            break;
        case Dir::LEFT:
            retval = "RIGHT";
            break;
        case Dir::RIGHT:
            retval = "LEFT";
            break;
    }

    return retval;
}


void printHomepage() {
    cout << el;
    cout << "Queries: " << el;
    cout << "(t) Terminal input " << el;
    cout << "(f) File input " << el;
    cout << "(h) Homepage " << el;
    cout << "(x) Exit the program " << el;
}


// ---- MAIN LOOP FUNCTION ---- //
// MODES
// t. Terminal input
// f. File input
// h. Homepage
// x. Exit the program
//      else -> Repeat loop

loopfunction loop() {

    char mode;
    Grid g;

    cout << "Please enter a specified input (t/f/h/x): ";
    cin >> mode;

    switch (mode) {

        case 't': {
            cout << "\nTERMINAL INPUT\n";
            int n, m;

            cout << "Input grid rows    : ";
            cin >> n;

            cout << "Input grid columns : ";
            cin >> m;

            if (n <= 0) {
                cout << "ERROR: "
                     << "the number of rows must be greater than 0"
                     << el;

                break;
            }

            if (m <= 0) {
                cout << "ERROR: "
                     << "the number of columns must be greater than 0"
                     << el;

                break;
            }

            cout << "Type your grid down below\n|\nV\n";

            std::vector<std::string> __grd(n);

            cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            for (auto& row : __grd) {
                std::getline(cin, row);
            }

            StatusCode st = g.load(__grd);

            if (st != StatusCode::SUCCESS) {
                cout << "ERROR: "
                     << parseStatus(st)
                     << el;

                return repeatloop;
            }

            break;
        }

        case 'f': {
            std::string filedir;

            cout << "\nFILE INPUT\n";
            cout << "Enter file directory (.txt): ";

            // Clear the newline left by cin >> mode
            cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            std::getline(cin, filedir);

            std::ifstream file(filedir);

            if (!file) {
                cout << "ERROR: "
                     << "Failed to open file"
                     << el;

                return repeatloop;
            }

            StatusCode st = g.load_from_file(file);

            if (st != StatusCode::SUCCESS) {
                cout << "ERROR: "
                     << parseStatus(st)
                     << el;

                return repeatloop;
            }

            break;
        }

        case 'h': {
            printHomepage();
            return repeatloop;
        }

        case 'x': {
            return stoploop;
        }

        default: {
            cout << "Invalid mode query\n";
            return repeatloop;
        }
    }
    cout << el << el << "Your grid is " << el << el;
    cout << g.getGridString() << el;

    // ---- SOLVE MAZE ---- //
    Solution sl;

    sl.grid = g;
    sl.solve();

    std::vector<Dir> dr = sl.get_solution();

    if (dr.empty()) {
        cout << "No possible solution detected for this maze"
             << el;
    }
    else {
        cout << "Solution: ";
        for (auto d : dr) {
            cout << parseDirection(d) << " ";
        }
        cout << el;
    }


    // ---- CONTINUE ---- //
    cout << "Want to continue the program? (Y/n) ";
    char c;
    cin >> c;
    if (c == 'Y') {
        printHomepage();
        return repeatloop;
    }
    return stoploop;
}


// ---- MAIN FUNCTION ---- //

mainfunction main() {
    cout << "\tMULTI FLAG MAZE SOLVER\t" << el;
    bool cond = repeatloop;
    printHomepage();

    while (cond != stoploop) {
        cond = loop();
    }
}
