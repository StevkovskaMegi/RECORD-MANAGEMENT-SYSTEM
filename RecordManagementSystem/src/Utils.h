#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <limits>
#include <iostream>

namespace Utils {
    inline void clearInputBuffer() {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    inline std::string getLine(const std::string& prompt) {
        std::cout << prompt;
        std::string s;
        std::getline(std::cin, s);
        return s;
    }

    inline int getInt(const std::string& prompt, int minVal = std::numeric_limits<int>::min(), int maxVal = std::numeric_limits<int>::max()) {
        while (true) {
            std::cout << prompt;
            int val;
            if (std::cin >> val) {
                if (val >= minVal && val <= maxVal) {
                    clearInputBuffer();
                    return val;
                } else {
                    std::cout << "Value out of range! (" << minVal << "-" << maxVal << ")\n";
                }
            } else {
                std::cout << "Invalid integer, try again.\n";
                clearInputBuffer();
            }
        }
    }

    inline std::string getNonEmpty(const std::string& prompt) {
        while (true) {
            std::string s = getLine(prompt);
            if (!s.empty()) return s;
            std::cout << "Input cannot be empty!\n";
        }
    }
}

#endif // UTILS_H