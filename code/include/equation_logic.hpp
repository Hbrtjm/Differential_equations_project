
#pragma once
#include <type_traits>
#include <cstdint>

namespace equation_logic {
	
	// Constants
	inline uint32_t n;
	inline uint32_t integration_steps = 10000;
	constexpr const double a = 0;
	constexpr const double b = 2;
	// Dirichlet condition at u(b)
	constexpr const double u_b = 0;

	// Elements functions
	double x_i(uint32_t i);
	double e_i(uint32_t i, double x);
	double de_i(uint32_t i, double x);
	double shift(double x);
	double dshift(double x);

	
	// Main components, from the top
	// B, B(w,v) - left-hand side of the equation, matrix is created out of it. We calculate its integral using gaussian quadrature
	// B_shift, B(\bar u, v) - the $\bar u$ part, it is on the right-hand side of the equation in the vector along with the matrix(v) component
	double B(uint32_t i, uint32_t j);
	double L(uint32_t i);
	double B_shift(uint32_t i);
}
