#include "hash.hpp"
#include "filetools.cpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <mutex>
#include <exception>


std::mutex checksum;

void hashFile(const char* filename, const char* hash_function) {

}

std::string to_lower(std::string str) {
    for (auto &c: str) {
        c = tolower(c);
    }
    return str;
}

int main(int argc, char* argv[]) {
    if (std::filesystem::exists("Checksum.ini")) {
        parseChecksum();
    } else if (argc == 1) {
        std::cout << "Usage: " << argv[0] << " filenames (-a crc32/md5/sha256)" << std::endl;
        return 1;
    }

    return 0;
}