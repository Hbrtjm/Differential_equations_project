#include <gaussian_quadrature.hpp>
#include <legendre_polynomial.hpp>
#include <iostream>
#include <iomanip>
#include <linear_solution.hpp>
#include <numbers>
#include <equation_logic.hpp>
#include <fstream>

int main(int argc, char** argv) {
	using equation_logic::n;

	if (argc < 3) {
		if (argc < 2) {
			std::cout << "Wpisz ilość elementów skończonych: ";
			std::cin >> n;
		}
		std::cout << "Wpisz ilość punków całkowania (stopień wielomianu Legendre): ";
		std::cin >> equation_logic::integration_steps;
	}
	if (argc > 1) {
		n = std::atoi(argv[1]);
		if (argc > 2) {
			equation_logic::integration_steps = std::atoi(argv[2]);
		}
	}

	uint32_t last_percent = 0;

	std::cout << "Tworzenie macierzy\n";
	matrix_t B_matrix(n + 1, vector_t(n + 1));
	vector_t L_vector(n + 1);

	std::cout << "Wpisywanie wartości do macierzy i wektora prawej strony\n";
	// Creating the matrix, as defined in the derivation document
	for (uint32_t i = 0; i != n; ++i) {
		B_matrix[i][i] = equation_logic::B(i, i);
		L_vector[i] = equation_logic::L(i) - equation_logic::B_shift(i);
		
		if (i + 1 != n) {
			B_matrix[i][i + 1] = equation_logic::B(i, i + 1);
			B_matrix[i + 1][i] = B_matrix[i][i + 1];
		}
	}
	
	B_matrix[n][n] = 1.0;
	L_vector[n] = equation_logic::u_b;

	std::cout << "Rozwiązywanie równania\n";
	vector_t result = solve_equation(B_matrix, L_vector, n);

	// Solution to the equation
	auto u = [&](double x) -> double {
		double sum = equation_logic::shift(x);
		for (uint32_t i = 0; i != result.size(); ++i) {
			// Element * weight
			sum += equation_logic::e_i(i, x) * result[i];
		}
		return sum;
	};

	std::ofstream file{"result.csv"};
	file << "x;u(x)\n";
	std::cout << "Zapisywanie do pliku result.csv\n";
	for (uint32_t i = 0; i != n + 1; ++i) {
		file << equation_logic::x_i(i) << ';' << u(equation_logic::x_i(i)) << '\n';
	}
}