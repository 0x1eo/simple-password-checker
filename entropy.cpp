#include <iostream>
#include <math.h>

float calculateCharset(std::string password) {
    int charset = 0;

    for (char c : password) {
        if (c >= '0' && c <= '9') {
            charset += 10;  // Numbers
        }
        if (c >= 'a' && c <= 'z') {
            charset += 26;  // Lowercase letters
        }
        if (c >= 'A' && c <= 'Z') {
            charset += 26;  // Uppercase letters
        }
        if (c < '0' || (c > '9' && c < 'A') || (c > 'Z' && c < 'a') || c > 'z') {
            charset += 33;  // Special characters, rough estimation
        }
    }

    return static_cast<float>(charset);
}

float calculateEntropy(std::string password) {

    float charset = calculateCharset(password);
    int length = password.length();

    return length * log2(charset);
}

std::string getStrength(float entropy) {
    if (entropy < 28.0) {
        return "Weak";
    } else if (entropy < 36.0) {
        return "Moderate";
    } else if (entropy < 60.0) {
        return "Strong";
    } else {
        return "Very Strong";
    }
}