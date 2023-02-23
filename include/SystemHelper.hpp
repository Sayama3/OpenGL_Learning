//
// Created by Sayama on 23/02/2023.
//

#pragma once
#include <string>
#include <sstream>
#include <fstream>

namespace Sayama::OpenGLLearning::SystemHelper {
    inline std::string ReadFile(std::string &path) {
        std::ifstream fileStream(path);
        std::stringstream file;
        std::string line;
        while (std::getline(fileStream, line)) {
            file << line << "\n";
        }
        return file.str();
    }
} // OpenGLLearning
