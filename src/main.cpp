/** Main program for the footprint security website **/

#include "App.hpp"

int main(int argc, char** argv) {
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env){ return new footprint::App(env); });
}
