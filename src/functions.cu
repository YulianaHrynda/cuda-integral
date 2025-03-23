//
// Created by gllekk on 25.02.25.
//

#include "functions.h"

__device__ double func_1(const double x, const double y) {
    double sums = 0.0;
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            sums += 1.0 / (5 * (i + 2) + j + 3 + std::pow(x - 16 * j, 6) + std::pow(y - 16 * i, 6));
        }
    }
    return 1.0 / (0.002 + sums);
}

__device__ double func_2(const double x, const double y) {
    const double a = 20.0;
    const double b = 0.2;
    const double c = 2 * M_PI;

    return -a * std::exp(-b * std::sqrt(0.5 * (x * x + y * y)))
           - std::exp(0.5 * (std::cos(c * x) + std::cos(c * y)))
           + a + std::exp(1.0);
}

__device__ double func_3(const double x, const double y) {
    const int m = 5;
    const double a1[m] = {1, 2, 1, 1, 5};
    const double a2[m] = {4, 5, 1, 2, 4};
    const double c[m]  = {2, 1, 4, 7, 2};

    double result = 0.0;

    for (int i = 0; i < m; ++i) {
        double val = (x - a1[i]) * (x - a1[i]) + (y - a2[i]) * (y - a2[i]);
        result += c[i] * exp(-val / M_PI) * cos(M_PI * val);
    }

    return -result;
}

