#include <equation_logic.hpp>
#include <gaussian_quadrature.hpp>
#include <iostream>
#include <cmath>
#include <functional>

namespace equation_logic {

	// Given E function

	double E(double x) 
	{
		if (x <= 1.0) {
			return 3;
		}
		else {
			return 5;
		}
	}


	// Elements functions

	double x_i(uint32_t i) 
	{
		return (b - a) / (double)n * (double)i + a;
	}

	double xin(uint32_t i, uint32_t _n) 
	{
		return (b - a) / (double)_n * (double)i + a;
	}

	double e_i(uint32_t i, double x) 
	{
		if (i == 0) {
			if (x_i(i) <= x && x <= x_i(i + 1)) {
				return (x_i(i + 1) - x) / (x_i(i + 1) - x_i(i));
			}
			else {
				return 0;
			}
		}
		else if (i == n + 1) {
			if (x_i(i - 1) <= x && x <= x_i(i)) {
				return (x - x_i(i - 1)) / (x_i(i) - x_i(i - 1));
			}
			else {
				return 0;
			}
		}
		else {
			if (x_i(i) <= x && x <= x_i(i + 1)) {
				return (x_i(i + 1) - x) / (x_i(i + 1) - x_i(i));
			}
			else if (x_i(i - 1) <= x && x <= x_i(i)) {
				return (x - x_i(i - 1)) / (x_i(i) - x_i(i - 1));
			}
			else {
				return 0;
			}
		}
	}

	double de_i(uint32_t i, double x) 
	{
		if (i == 0) {
			if (x_i(i) <= x && x <= x_i(i + 1)) {
				return -1.0 / (x_i(i + 1) - x_i(i));
			}
			else {
				return 0;
			}
		}
		else if (i == n + 1) {
			if (x_i(i - 1) <= x && x <= x_i(i)) {
				return 1.0 / (x_i(i) - x_i(i - 1));
			}
			else {
				return 0;
			}
		}
		else {
			if (x_i(i) <= x && x <= x_i(i + 1)) {
				return -1.0 / (x_i(i + 1) - x_i(i));
			}
			else if (x_i(i - 1) <= x && x <= x_i(i)) {
				return 1.0 / (x_i(i) - x_i(i - 1));
			}
			else {
				return 0;
			}
		}
	}

	double shift(double x) 
	{
		return u_b * e_i(n + 1, x);
	}
	
	double dshift(double x) 
	{
		return u_b * de_i(n + 1, x);
	}

	// Main components, from the top
// B, B(w,v) - left-hand side of the equation, matrix is created out of it. We calculate its integral using gaussian quadrature
// B_shift, B(\bar u, v) - the $\bar u$ part, it is on the right-hand side of the equation in the vector along with the matrix(v) component

	double B(uint32_t i, uint32_t j) 
	{
		auto integrand = [&](double x) -> double {
			return de_i(i, x) * de_i(j, x) * E(x);
		};
		return gaussian_quadrature(integrand, a, b, integration_steps) - e_i(i, a) * e_i(j, a) * E(a);
	}

	double L(std::uint32_t i) 
	{
		return -10 * E(a) * e_i(i, a);
	}

	double B_shift(uint32_t i) 
	{
		if (std::fabs(u_b) < 1.0e-15) {
			return 0;
		}

		auto integrand = [&](double x) -> double {
			return dshift(x) * de_i(i, x) * E(x);
		};

		return gaussian_quadrature(integrand, a, b, integration_steps) - e_i(i, a) * shift(a) * E(a);
	}
}
