#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "hash.hpp"

struct file {
    std::string filename;
    std::string expected_hash;
};

std::map<Hashes, std::vector<file>> parseChecksum() {
    std::ifstream in ("Checksum.ini");
    std::map<Hashes, std::vector<file>> parsedFiles;
    std::string current, filename;
    size_t pointer, hash_start;
    file current_file;
    Hashes algorithm;
    while (std::getline(in, current)) {
        // blank or comment
        if (';'  == current[0] || '\n' == current[0] || '\r' == current[0] ) {
            continue;
        }

        // new_algorithm
        if ('[' == current[0]) {
            pointer = 0;
            std::string string_alg;
            while (current[++pointer + 1] != ']') {}
            string_alg = current.substr(1, pointer);
            algorithm = parseAlgorithm(string_alg);
            continue;
        }

        pointer = 0;
        while (current[++pointer] != '=') {}    
        filename = current.substr(0, pointer);
        hash_start = pointer;
        if (current[pointer + 2] == 'x') hash_start += 2;
        pointer = 0;
        current_file.filename = filename;
        current_file.expected_hash = current.substr(hash_start + 1, current.size() - hash_start);
        parsedFiles[algorithm].push_back(current_file);
    }
    return parsedFiles;
}

// Testing
// int main() {
//     auto smth = parseChecksum();
//     for (auto files : smth[Hashes::MD5]) {
//         std::cout << files.filename << '\t' << files.expected_hash << std::endl;
//     }
//     // std::cout << smth[Hashes::CRC32].front().filename << '\t' << smth[Hashes::CRC32].front().expected_hash << std::endl;
//     return 0;
// }