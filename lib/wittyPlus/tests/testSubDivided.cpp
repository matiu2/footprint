/**
 * */

#include "../SubDivided.hpp"
#include "Testing.hpp"

#include <vector>
#include <algorithm>

int main(int, char**) {
    std::string path = "/path/to/somewhere/";

    auto part = wittyPlus::split(path, '/');

    assertEqual("path", part);
    ++part;
    assertEqual("to", part++);
    assertEqual("somewhere", part++);
    assertEqual(wittyPlus::Part<std::string>(), part);
    assertEqual("", part);

    // Does it work with strings ?
    part = wittyPlus::split(path, '/');

    assertEqual(std::string("path"), part++);
    assertEqual(std::string("to"), part++);
    assertEqual(std::string("somewhere"), part++);

    // Can you sort them ?
    std::vector<decltype(part)> parts;
    part = wittyPlus::split(path, '/');
    while (part)
        parts.push_back(part++);
    std::sort(parts.begin(), parts.end());

    assertEqual("path", parts[0]);
    assertEqual("somewhere", parts[1]);
    assertEqual("to", parts[2]);

}
