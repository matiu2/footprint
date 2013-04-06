#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

namespace wittyPlus {

class NotFound : public std::exception {
private:
    std::string _what;
public:
    NotFound(const std::string& what) : _what(what) {}
    const std::string what() { return _what; }
};

}

#endif // EXCEPTIONS_HPP
