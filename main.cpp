#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>

int main() {
    std::ofstream file("test.txt");

    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    for (int i = 0; i < 1000; ++i) {
        file << "Line " << i << std::endl;
        file.flush();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    file.close();
    return 0;
}