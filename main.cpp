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
    std::future<std::string> smth;
    std::string got_string;
    
    for (Hashes algorithm : all_hashes) {
        for (file current : files[algorithm]) {
            smth = std::async(HashFactory::hash, (unsigned char*) current.filename.data(), current.filename.size(), algorithm);
            futures.push_back(smth);
        }
    }
    for (Hashes algorithm : all_hashes) {
        for (file current : files[algorithm]) {
            futures.back().wait();
            got_string = futures.back().get();
            if (!current.expected_hash.compare(got_string)) {
                output.lock();
                std::cout << "File " << current.filename << " is corrupted!" << std::endl << "Checked by " << algorithmToText(algorithm) << std::endl;
                std::cout << "Expected hash: " << current.expected_hash << std::endl;
                std::cout << "Got hash: " << got_string << std::endl;
                output.unlock();
            }
            futures.pop_back();

        }
    }
}

int main(int argc, const char** argv) {
    // if (std::filesystem::exists("Checksum.ini")) {
    // std::cout << parseChecksum("Checksum.ini")[Hashes::CRC32].front().filename << std::endl;
    comparingHashes(parseChecksum("Checksum.ini"));
    // // } else if (argc == 1) {
    //     std::cout << "Usage: " << argv[0] << " filenames (-a crc32/md5/sha256)" << std::endl;
    //     return 1;
    // }
    // std::vector<Hashes> all_hashes { Hashes::MD5, Hashes::CRC32, Hashes::SHA256 };
    // auto files = parseArguments(argc, argv);
    // for (Hashes algorithm : all_hashes) {
    //     for (file current : files[algorithm]) {
    //         std::cout << algorithmToText(algorithm) << '\t' << current.filename << std::endl;
    //     }
    // }

    return 0;
}