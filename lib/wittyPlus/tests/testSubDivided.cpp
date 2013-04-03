/**
 * */

#include "../SubDivided.hpp"
#include "Testing.hpp"

int main(int, char**) {
    std::string path = "/path/to/somewhere/";

    auto broken = wittyPlus::split(path, '/');

    assertEqual(3, broken.size(), "Need 3 members");
    assertEqual("path", broken[0]);
    assertEqual("to", broken[1]);
    assertEqual("somewhere", broken[2]);

    std::string part("path");

    assertEqual(broken[0], part);
}
