#pragma once

#include <legendre_polynomial.hpp>
#include <concepts>
#include <cstdint>


template<std::invocable<double> Fn>
double gaussian_quadrature(Fn fn, double a, double b, uint32_t n = 1000) {
	double sum = 0;
	const double mean = (a + b) / 2.0;
	const double half_width = (b - a) / 2.0;
	auto lpoly = legendre_polynomial::get(n);

	for (uint32_t i = 0; i != n; ++i) {
		sum += lpoly.get_weights()[i] * fn(half_width * lpoly.get_roots()[i] + mean);
	}

	return half_width * sum;
}