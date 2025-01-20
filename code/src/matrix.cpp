#include <matrix.hpp>

namespace matrixspace {
	void add_rows(matrix_t& matrix, vector_t& variables, uint32_t to_add_to, uint32_t added, double scalar) 
	{
		for (uint32_t i = 0; i != variables.size(); ++i) {
			matrix[to_add_to][i] += scalar * matrix[added][i];
		}
		variables[to_add_to] += scalar * variables[added];
	};

	void subtract_rows(matrix_t& matrix, vector_t& variables, uint32_t to_subtracted_from, uint32_t subtracted, double scalar) 
	{
		add_rows(matrix, variables, to_subtracted_from, subtracted, -scalar);
	};
}
