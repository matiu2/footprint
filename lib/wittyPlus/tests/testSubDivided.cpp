/**
 * */

#include "../SubDivided.hpp"
#include "Testing.hpp"

int main(int, char**) {
    std::string path = "/path/to/somewhere/";

    auto part = wittyPlus::SubDivided<std::string>(path, '/');

    assertEqual("path", part);
    ++part;
    assertEqual("to", part++);
    assertEqual("somewhere", part++);
    assertEqual(wittyPlus::SubDivided<std::string>(), part);
    assertEqual("", part);

    part = wittyPlus::SubDivided<std::string>(path, '/');

    assertEqual(std::string("path"), part++);
    assertEqual(std::string("to"), part++);
    assertEqual(std::string("somewhere"), part++);

}
