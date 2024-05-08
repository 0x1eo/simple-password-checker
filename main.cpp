#include "entropy.cpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

bool isPasswordInDictionary(const std::string& password, const std::string& dictionary_path) {
    std::ifstream dictionary(dictionary_path);
    std::string word;
    while (dictionary >> word) {
        if (word == password) {
            return true;
        }
    }
    return false;
}

bool isPasswordCommon(const std::string& password, const std::string& common_passwords_path) {
    std::ifstream common_passwords(common_passwords_path);
    std::string common_password;
    while (common_passwords >> common_password) {
        if (common_password == password) {
            return true;
        }
    }
    return false;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv, argv + argc);
    std::string password;

    if (args.size() == 1) {
        std::cout << "Enter a password: ";
        std::cout.flush();
        std::getline(std::cin, password);
    } else if (args.size() == 2) {
        password = args[1];
    } else {
        std::cout << "Usage: password-strength [password]" << std::endl;
        std::exit(1);
    }

    password = password.substr(0, password.find_last_not_of(" \t\n\r\f\v") + 1);

    if (password.empty()) {
        std::cout << "Password cannot be empty." << std::endl;
        std::exit(1);
    }

    std::string dictionary_path = "data/dictionary.txt";
    std::string common_passwords_path = "data/common-passwords.txt";

    if (isPasswordInDictionary(password, dictionary_path) || isPasswordCommon(password, common_passwords_path)) {
        std::cout << "Password is weak: It matches a common password or dictionary word." << std::endl;
    } else {
        double entropy = calculateEntropy(password);
        std::cout << "Password strength: " << getStrength(entropy) << std::endl;
        std::cout << "Entropy score: " << entropy << std::endl;
    }

    return 0;
}