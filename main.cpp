#include <iostream>
#include <cstdlib>
#include <cmath>

#include "options_parser.h"
#include "parse_string.h"
#include "riemann_sum_cuda.h"
#include "timeMeasurement.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Error: Incorrect number of arguments." << std::endl
                  << "Usage: ./cuda_integrate method_number cfg_file_path" << std::endl;
        return 1;
    }

    const int func_no = atoi(argv[1]);
    const std::string fileName = argv[2];

    std::map<std::string, double> params = readParse(fileName);
    if (params.empty()) {
        std::cerr << "Failed to parse parameters from config file." << std::endl;
        return 5;
    }

    const double abs_err = params.at("abs_err");
    const double rel_err = params.at("rel_err");
    const double x1 = params.at("x_start");
    const double x2 = params.at("x_end");
    const double y1 = params.at("y_start");
    const double y2 = params.at("y_end");
    size_t steps_x = static_cast<size_t>(params.at("init_steps_x"));
    size_t steps_y = static_cast<size_t>(params.at("init_steps_y"));
    const size_t max_iter = static_cast<size_t>(params.at("max_iter"));

    double integral = 0.0, prev_int = 0.0, Err_abs = 0.0, Err_rel = 0.0;

    const auto start = get_current_time_fenced();

    for (size_t iter = 0; iter < max_iter; iter++) {
        prev_int = integral;

        // Виклик обчислення на GPU
        integral = riemman_return(x1, x2, y1, y2, steps_x, func_no);

        Err_abs = fabs(integral - prev_int);
        Err_rel = Err_abs / fabs(integral);

        if (Err_abs < abs_err || Err_rel < rel_err) {
            break;
        }

        steps_x *= 2;
        steps_y *= 2;
    }

    const auto end = get_current_time_fenced();

    std::cout << integral << std::endl;
    std::cout << Err_abs << std::endl;
    std::cout << Err_rel << std::endl;
    std::cout << to_ms(end - start) << std::endl;

    return 0;
}

