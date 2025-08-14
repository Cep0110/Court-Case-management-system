 #ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <string>

class InputValidator {
public:
    static int getInt(const std::string& prompt);
    static std::string getNonEmptyString(const std::string& prompt);
    static std::string getDate(const std::string& prompt);
    static int getMenuChoice(int min, int max, const std::string& prompt);
};

#endif
