#include "hash.hpp"
#include "filetools.cpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <future>
#include <mutex>
#include <exception>

std::mutex output;

// Compare Hashes with expected or output
void comparingHashes(std::map<Hashes, std::vector<file>> files) {
    std::vector<Hashes> all_hashes { Hashes::MD5, Hashes::CRC32, Hashes::SHA256 };
    std::vector<std::future<std::string>> futures;
    std::vector<unsigned char> string;
    std::string got_string;
    
    for (Hashes algorithm : all_hashes) {
        for (file current : files[algorithm]) {
            string = getBytesFromFile(current.filename);
            futures.push_back(std::async(HashFactory::hash, string.data(), string.size(), algorithm));
        }
    }
    for (Hashes algorithm : all_hashes) {
        if (files[algorithm].empty()) continue;
        std::cout << std::endl << algorithmToText(algorithm) << std::endl << std::endl;
        for (file current : files[algorithm]) {
            futures.front().wait();
            got_string = futures.front().get();

            if (current.expected_hash.compare(std::string("")) == 0) {
                std::cout << current.filename << " hash: " << got_string << std::endl;
                continue;
            }

            output.lock();
            std::cout << "File " << current.filename;
            if (current.expected_hash.compare(got_string)) {      
                std::cout << " is corrupted!" << std::endl;
                std::cout << "Expected hash: " << current.expected_hash << std::endl;
                std::cout << "Got hash: " << got_string << std::endl;
            } else {
                std::cout << " is complete!" << std::endl;
            }

            std::cout << std::endl;
            output.unlock();
            futures.erase(futures.begin());
        }
    }
}

int main(int argc, const char** argv) {
    if (std::filesystem::exists("Checksum.ini")) {
        comparingHashes(parseChecksum("Checksum.ini"));
    }

    if (argc < 4 && !std::filesystem::exists("Checksum.ini")) std::cout << "Usage: " << argv[0] << " filenames -a (crc32/md5/sha256)" << std::endl;
    else if (argc >= 4) {
        comparingHashes(parseArguments(argc, argv));
    }

    return 0;
}