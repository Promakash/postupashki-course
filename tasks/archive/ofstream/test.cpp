#include "ofstream.h"

#include <fstream>
#include <sstream>

#include <iostream>
#include <catch2/catch_test_macros.hpp>

#include "fd_balance_checker.h"

#include <filesystem>

std::string FetchFileData(const std::filesystem::path& path) {
    chdir("../tasks/filesystem/ofstream");
    std::ifstream stream(path);
    std::stringstream buffer;
    buffer << stream.rdbuf();
    return buffer.str();
}

TEST_CASE("base test") {
    Utils::FDBalanceChecker fd_checker;
    chdir("../tasks/filesystem/ofstream");
    std::filesystem::path test_path_1 = "output/test_1.txt";
    OFStream stream(test_path_1);

    std::string test_string_1 = "oxxxymiron";
    stream.Write(test_string_1.c_str(), test_string_1.size());

    stream.Flush();

    REQUIRE(FetchFileData(test_path_1) == test_string_1);
}

TEST_CASE("auto flash") {
    Utils::FDBalanceChecker fd_checker;
    chdir("../tasks/filesystem/ofstream");
    std::filesystem::path test_path_1 = "output/test_2.txt";
    OFStream stream(test_path_1);

    std::string test_string_1 = "Never gonna give you up";
    stream.Write(test_string_1.c_str(), test_string_1.size());

    stream.Close();

    REQUIRE(FetchFileData(test_path_1) == test_string_1);


    std::filesystem::path test_path_2 = "output/test_3.txt";
    std::string test_string_2 = "Never gonna give you up";
    {
        OFStream stream(test_path_2);
        stream << test_string_2;
    }

    REQUIRE(FetchFileData(test_path_2) == test_string_2);
}

TEST_CASE("buffer 1024 check") {
    Utils::FDBalanceChecker fd_checker;
    chdir("../tasks/filesystem/ofstream");
    std::filesystem::path test_path = "output/test_5.txt";
    OFStream stream(test_path);

    std::string test_string = FetchFileData("input/test_1.txt");

    std::string expected_string = "";

    for (int i = 0; i < test_string.size(); ++i) {
        stream << test_string[i];

        if ((i + 1) % 1024 == 0 && i != 0) {
            size_t limit = std::min(test_string.size(), expected_string.size() + 1024ul);
            for (size_t i = expected_string.size(); i < limit; ++i) {
                expected_string += test_string[i];
            }
        }

        REQUIRE(FetchFileData(test_path) == expected_string);
    } 

    stream.Flush();

    REQUIRE(FetchFileData(test_path) == test_string);
}