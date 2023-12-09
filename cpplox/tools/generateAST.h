#pragma once

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

void defineAst(const std::string outputDir, const std::string baseName,
               const std::vector<std::string> types);
void defineType(std::ofstream &file, const std::string baseName,
                const std::string className, const std::string fieldList);
std::vector<std::string> split(const std::string &inputString,
                               std::string delimiter = " ");
std::string trim(const std::string &str);
