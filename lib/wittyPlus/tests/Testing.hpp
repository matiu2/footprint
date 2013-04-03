/// Our DIY simple testing library
#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

void assert(bool pred, const std::string& msg="") {
    if (!pred) {
        std::stringstream out;
        out << "Line " << __LINE__ << ": " << msg;
        throw std::runtime_error(out.str());
    }
}

template <typename T1, typename T2>
void assertEqual(const T1& a, const T2& b, const std::string& msg="") {
    if (a != b) {
        std::stringstream out;
        out << "Line " << __LINE__ << ": '" << a << "' != '" << b << "': " << msg;
        throw std::runtime_error(out.str());
    }
}
