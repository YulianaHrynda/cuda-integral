//
// Created by gllekk on 24.02.25.
//

#ifndef PARSE_STRING_H
#define PARSE_STRING_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

std::string removeComm(const std::string &line);

std::string trim(const std::string &str);

int validateConf(std::map<std::string, double> &conf);

std::map<std::string, double> readParse(const std::string &filename);

#endif //PARSE_STRING_H
