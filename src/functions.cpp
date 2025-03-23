//
// Created by gllekk on 25.02.25.
//

#include "functions.h"

double func_1(const double x, const double y) {
    double sums = 0.0;
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            sums += 1.0 / (5 * (i + 2) + j + 3 + std::pow(x - 16 * j, 6) + std::pow(y - 16 * i, 6));
        }
    }
    return 1.0 / (0.002 + sums);
}

double func_2(const double x, const double y) {
    const double a = 20.0;
    const double b = 0.2;
    const double c = 2 * M_PI;

    return -a * std::exp(-b * std::sqrt(0.5 * (x * x + y * y)))
           - std::exp(0.5 * (std::cos(c * x) + std::cos(c * y)))
           + a + std::exp(1.0);
}

double func_3(const double x, const double y) {
    double result = 0.0;
    const size_t m = 5;
    const std::vector<double> a1 = {1, 2, 1, 1, 5};
    const std::vector<double> a2 = {4, 5, 1, 2, 4};
    const std::vector<double> c = {2, 1, 4, 7, 2};

    for (size_t i = 0; i < m; i++) {
        double val = pow(x - a1[i], 2) + pow(y - a2[i], 2);
        result += c[i] * exp(-val / M_PI) * cos(M_PI * val);
    }
    return -result;
}

double additional_function(const double x, const double y) {
    size_t m = 5;
    double result1 = 0;
    double result2 = 0;

    for (size_t i = 1; i <= m; i++) {
        result1 += i * cos((i + 1) * x + 1);
        result2 += i * cos((i + 1) * y + 1);
    }

    return -(result1 * result2);
}
