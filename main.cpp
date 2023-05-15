#include "hash.hpp"
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

void parseChecksum() {
    std::ifstream in ("Checksum.ini");
    std::string current;
    size_t counter;
    Hashes algorithm;
    while (std::getline(in, current)) {
        if (';'  == current[0] || '\n' == current[0] || '\r' == current[0] ) {
            continue;
        }

        if ('[' == current[0]) {
            counter = 1;
            std::string string_alg;
            while (current[++counter] != ']') {
                string_alg = current.substr(1, counter - 1);
            }
            algorithm = parseAlgorithm(string_alg);
        }

        counter = 0;
        while (current[++counter] != '=') {}
        std::string filename = current.substr(0, counter);
        while (current[counter] != ' ' || current[counter] != '\n') {
            ++counter;
        }
        

    }

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