#pragma once

#include <string>

enum class StatusCode {
    GENERAL_ERROR,
    MISUSED_CHARACTER_ERROR,
    VARIABLE_VECTOR_SIZE_ERROR,
    MULTIPLE_START_ERROR,
    MULTIPLE_FINISH_ERROR,
    NO_START_ERROR,
    NO_FINISH_ERROR,
    FILE_ERROR,
    EMPTY_GRID_ERROR,

    SUCCESS
};

inline std::string parseStatus(StatusCode st){
    switch (st) {
        case StatusCode::SUCCESS:
            return "SUCCESS";
        case StatusCode::GENERAL_ERROR:
            return "GENERAL_ERROR";
        case StatusCode::MISUSED_CHARACTER_ERROR:
            return "MISUSED_CHARACTER_ERROR - Only use # . X S G F";
        case StatusCode::VARIABLE_VECTOR_SIZE_ERROR:
            return "VARIABLE_VECTOR_SIZE_ERROR";
        case StatusCode::MULTIPLE_START_ERROR:
            return "MULTIPLE_START_ERROR";
        case StatusCode::MULTIPLE_FINISH_ERROR:
            return "MULTIPLE_FINISH_ERROR";
        case StatusCode::NO_START_ERROR:
            return "NO_START_ERROR";
        case StatusCode::FILE_ERROR:
            return "FILE_ERROR";
        case StatusCode::EMPTY_GRID_ERROR:
            return "EMPTY_GRID_ERROR";
    }
    return "0";
}