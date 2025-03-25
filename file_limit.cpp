#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>
#include <filesystem>

int main() {
    const int totalFiles = 100000;
    const int batchSize = 1000;
    const int sleepTime = 1;

    std::vector<std::ofstream> files;
    std::filesystem::create_directory("FileLimitTest");

    for (int i = 0; i < totalFiles; i++) {
        std::ostringstream filename;
        filename << "FileLimitTest/file_" << i << ".txt";

        files.emplace_back(filename.str());

        if (!files.back().is_open()) {
            std::cerr << "Error opening file: " << filename.str() << std::endl;
            std::cerr << "System file descriptor limit!" << std::endl;
            break;
        }

        files.back() << "This is file " << i << std::endl;
        files.back().flush();

        if (i % batchSize == 0) {
            std::cout << "Opened " << i << " files" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(sleepTime));
        }
    }

    std::cout << "File opening attempt finished. Sleeping for 30 sec" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(30));

    return 0;
}