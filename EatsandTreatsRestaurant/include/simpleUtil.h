#pragma once

#include <iomanip>
#include <sstream>

class Util {
public:
    static std::string formatFloat(float value) {
        std::ostringstream stream;
        stream << std::fixed << std::setprecision(2) << value;  // Show 2 digits after the decimal
        return stream.str();
    }
};
