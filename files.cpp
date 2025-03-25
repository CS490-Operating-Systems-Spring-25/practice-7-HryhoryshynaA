#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <thread>
#include <chrono>

int main() {
    const int fileCount = 100;
    std::vector<std::ofstream> files;

    for (int i = 0; i < fileCount; ++i) {
        std::ostringstream filename;
        filename << "Files/file_" << i << ".txt";

        files.emplace_back(filename.str());

        if (!files.back().is_open()) {
            std::cerr << "Error opening file: " << filename.str() << std::endl;
            return 1;
        }

        files.back() << "This is file " << i << std::endl;
        files.back().flush();
    }
    std::this_thread::sleep_for(std::chrono::seconds(30));

    return 0;
}