/// Our DIY simple testing library
#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

void _assert(bool pred, int line, const char* file, const std::string& msg="") {
    if (!pred) {
        std::stringstream out;
        out << "Assertion Failure: " << file << ":" << line << ": '" << msg;
        throw std::runtime_error(out.str());
    }
}

template <typename T1, typename T2>
void _assertEqual(const T1& a, const T2& b, int line, const char* file, const std::string& msg="") {
    if (a != b) {
        std::stringstream out;
        out << "Assertion Failure: " << file << ":" << line << ": '" << a << "' != '" << b << "': " << msg;
        throw std::runtime_error(out.str());
    }
}

#define assertEqual(a,b) _assertEqual(a, b, __LINE__, __FILE__)
#define assertEqualMsg(a,b,msg) _assertEqual(a, b, __LINE__, __FILE__, msg)
#define assert(a) _assert(a, __LINE__, __FILE__)
#define assertMsg(a,msg) _assert(a, __LINE__, __FILE__, msg)
