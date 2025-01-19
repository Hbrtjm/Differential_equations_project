
#pragma once

#include <vector>
#include <unordered_map>
#include <ranges>
#include <algorithm>
#include <cstdint>

using vector_t = std::vector<double>;
using matrix_t = std::vector<vector_t>;

namespace matrixspace {
    // Adds rows of matrix matrix and vector variables
    void add_rows(matrix_t& matrix, vector_t& variables, uint32_t to_add_to, uint32_t added, double scalar = 1.0);
    // Subtract rows of matrix matrix and vector variables, simply uses add_rows with a scalar set to -scalar
    void subtract_rows(matrix_t& matrix, vector_t& variables, uint32_t to_subtract_from, uint32_t subtracted, double scalar = 1.0);
}
