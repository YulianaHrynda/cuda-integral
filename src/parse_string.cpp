//
// Created by gllekk on 24.02.25.
//

#include "parse_string.h"


std::string removeComm(const std::string &line) {
    size_t pos = line.find('#');
    return (pos != std::string::npos) ? line.substr(0, pos) : line;
}

std::string trim(const std::string &str) {
    size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, last - first + 1);
}

int validateConf(std::map<std::string, double> &conf) {
    if (conf["x_start"] >= conf["x_end"] || conf["y_start"] >= conf["y_end"]) {
        std::cerr << "Error: Start must be greater than end" << std::endl;
        return 5;
    }
    if (conf["init_steps_x"] < 10 || conf["init_steps_y"] < 10) {
        std::cerr << "Error: Too few init_steps" << std::endl;
        return 5;
    }
    if (conf["max_iter"] < 3) {
        std::cerr << "Error: Too small max_iters" << std::endl;
        return 5;
    }
    if (conf["max_iter"] > 30) {
        std::cerr << "Error: Too large max_iters" << std::endl;
        return 5;
    }
    if (conf["abs_err"] <= 0 || conf["rel_err"] <= 0) {
        std::cerr << "Error: Errors should be positive" << std::endl;
        return 5;
    }
    return 0;
}

std::map<std::string, double> readParse(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return {};
    }
    std::map<std::string, double> result;
    while (std::getline(file, line)) {
        line = trim(removeComm(line));
        if (line.empty()) continue;
        size_t pos = line.find('=');
        if (pos == std::string::npos) {
            std::cerr << "Invalid config line (missing '='): " << line << std::endl;
            continue;
        }
        std::pair<std::string, double> res;
        auto key = trim(line.substr(0, pos));
        auto value = std::stod(trim(line.substr(pos + 1)));

        result[key] = value;;
    }
    if (validateConf(result) != 0) {
        return {};
    }
    return result;
}
