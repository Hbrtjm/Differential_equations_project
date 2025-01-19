#pragma once

#include <matrix.hpp>
#include <cstdint>

// Simple gaussian elimination, for each i-th row eliminate all of the rows below the place (i,i) in matrix 
void gaussian_elimination(matrix_t& matrix, vector_t& variables, int32_t n_limit = -1);
// Given the upper triangular form after Gaussian elimination, solve for i-th variable in the system of equations
vector_t solve_upper_triangle(matrix_t& matrix, vector_t& variables, int32_t n_limit = -1);
// Combines two functions above and solves the equation
vector_t solve_equation(matrix_t& matrix, vector_t& variables, int32_t n_limit);