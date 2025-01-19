#include <linear_solution.hpp>
#include <iostream>

void gaussian_elimination(matrix_t& matrix, vector_t& variables, int32_t n_limit) 
{
	uint32_t n = variables.size();
	if (n_limit != (uint32_t)-1) 
	{
		n = n_limit;
	}

	uint32_t last_percent = 0;
	for (uint32_t row = 0; row != n; ++row) 
	{
		// Subtracting only next row, due to the shape of the given matrix
		uint32_t sub_row_id = row + 1; 
		if (sub_row_id != n) 
		{
			double scalar = matrix[sub_row_id][row] / matrix[row][row];
			matrixspace::subtract_rows(matrix, variables, sub_row_id, row, scalar);
		}
	}
}

vector_t solve_upper_triangle(matrix_t& matrix, vector_t& variables, int32_t n_limit) 
{
	uint32_t n = variables.size();
	if (n_limit != (uint32_t)-1) 
	{
		n = n_limit;
	}
	vector_t result(n);

	// Subtracts one row upwards
	for (uint32_t row = n - 1; row != (uint32_t)-1; --row)
	 {
		result[row] = variables[row];
		for (uint32_t row2 = row + 1; row2 != n; ++row2) 
		{
			result[row] -= variables[row2] * matrix[row][row2];
		}
		result[row] /= matrix[row][row];
		variables[row] = result[row];
	}
	for (uint32_t i = n; i != n; ++i) 
	{
		result[i] = variables[i];
	}

	return result;
}

vector_t solve_equation(matrix_t& matrix, vector_t& variables, int32_t n_limit)
{
	gaussian_elimination(matrix, variables, n_limit);
	return solve_upper_triangle(matrix, variables, n_limit);
}