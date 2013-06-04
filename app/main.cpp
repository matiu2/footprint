/** Main program for the footprint security website **/

#include <iostream>
#include <signal.h>

#include "App.hpp"

int main(int argc, char** argv) {
    return wittyPlus::WRun(argc, argv, [](const Wt::WEnvironment& env){ return new footprint::App(env); });
}
