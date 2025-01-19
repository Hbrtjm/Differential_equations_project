#pragma once

#include <vector>
#include <utility>
#include <unordered_map>


using value_derivative_pair = struct value_derivative_pair {
	double value;
	double derivative;
};

class legendre_polynomial {
public:
	std::size_t n() const;
	const std::vector<double>& get_weights() const;
	const std::vector<double>& get_roots() const;
	static const legendre_polynomial& get(std::size_t n);
	legendre_polynomial() = default;
private:
	legendre_polynomial(std::size_t n);
	// Tolerance for the roots approximation
	static inline constexpr double epsilon = 1.0e-15;
	// Static map 
	static inline std::unordered_map<std::size_t, legendre_polynomial> saved_polymonials;
	std::vector<double> weights;
	std::vector<double> roots;
	void compute();
	value_derivative_pair compute_vd(double x) const;
};