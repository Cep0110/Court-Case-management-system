 #include "InputValidator.h"
#include <iostream>
#include <regex>
#include <limits>

int InputValidator::getInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid integer.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

std::string InputValidator::getNonEmptyString(const std::string& prompt) {
    std::string input;
    do {
        std::cout << prompt;
        getline(std::cin, input);
        if (input.empty())
            std::cout << "Input cannot be empty. Try again.\n";
    } while (input.empty());
    return input;
}

std::string InputValidator::getDate(const std::string& prompt) {
    std::regex dateRegex(R"(\d{4}-\d{2}-\d{2})");
    std::string date;
    do {
        std::cout << prompt;
        getline(std::cin, date);
        if (!std::regex_match(date, dateRegex))
            std::cout << "Please enter date in YYYY-MM-DD format.\n";
    } while (!std::regex_match(date, dateRegex));
    return date;
}

int InputValidator::getMenuChoice(int min, int max, const std::string& prompt) {
    int choice;
    while (true) {
        std::cout << prompt;
        std::cin >> choice;
        if (std::cin.fail() || choice < min || choice > max) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Try again.\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
    }
}
