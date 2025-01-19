#include <gaussian_quadrature.hpp>
#include <legendre_polynomial.hpp>
#include <numbers>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <cmath>

legendre_polynomial::legendre_polynomial(std::size_t n):
	roots(n),
	weights(n) {
	compute();
}

const legendre_polynomial& legendre_polynomial::get(std::size_t n) 
{
	auto found = saved_polymonials.find(n);
	if (found != saved_polymonials.end()) 
	{
		return found->second;
	}
	// If the file exists, read and return 
	if (std::filesystem::exists("cached/" + std::to_string(n))) 
	{
		legendre_polynomial lpoly{};
		lpoly.roots = std::vector<double>(n);
		lpoly.weights = std::vector<double>(n);
		std::ifstream infile{"cached/" + std::to_string(n), std::ios::binary | std::ios::in};
		infile.read((char*)lpoly.weights.data(), n * sizeof(double));
		infile.read((char*)lpoly.roots.data(), n * sizeof(double));
		saved_polymonials.insert_or_assign(n, lpoly);
		return get(n);
	}
	legendre_polynomial lpoly{n};
	if (!std::filesystem::exists("cached")) 
	{
		std::filesystem::create_directory("cached");
	}
	// Calculate the polynomial
	std::ofstream outfile{"cached/" + std::to_string(n), std::ios::binary | std::ios::out};
	outfile.write((char*)lpoly.weights.data(), n * sizeof(double));
	outfile.write((char*)lpoly.roots.data(), n * sizeof(double));
	saved_polymonials.insert_or_assign(n, lpoly);
	return get(n);	
}

std::size_t legendre_polynomial::n() const 
{
	return roots.size();
}

const std::vector<double>& legendre_polynomial::get_weights() const 
{
	return weights;
}

const std::vector<double>& legendre_polynomial::get_roots() const 
{
	return roots;
}

value_derivative_pair legendre_polynomial::compute_vd(double x) const 
{
	value_derivative_pair result{x, 0.0};

	double value_old = 1.0;
	for (std::size_t i = 2; i <= n(); ++i) {
		// recursive formula for polynomial value
		double ith_value = ((2 * i - 1) * x * result.value - (i - 1) * value_old) / i;

		value_old = result.value;
		result.value = ith_value;
	}
	result.derivative = n() * 1/(x*x-1) * (x * result.value - value_old);

	return result;
}

void legendre_polynomial::compute() 
{
	for (std::size_t i = 0; i != n(); ++i) {
		// Root approximation formula
		double root = cos(std::numbers::pi_v<double> *((double)i - 0.25) / ((double)n() + 0.5));
		
		value_derivative_pair vd = compute_vd(root);
		double fdf_ratio;
		do 
		{
			fdf_ratio = vd.value / vd.derivative;
			root -= fdf_ratio;
			vd = compute_vd(root);
		}
		while (std::fabs(fdf_ratio) > epsilon);

		roots[n() - i - 1] = root;
		weights[n() - i - 1] = 2.0 / ((1 - root * root) * vd.derivative * vd.derivative);
	}
}