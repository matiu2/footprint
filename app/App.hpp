#pragma once
/**
  The Wt Application object for the footprint website
*/

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WText>
#include <Wt/WCssTheme>

#include <wittyPlus/App.hpp>


#include "Colors.hpp"

#include "widgets/MainWindow.hpp"

namespace footprint {

/// The Application object for the footprint security website
class App : public wittyPlus::App {
public:
    App(const Wt::WEnvironment& env);
    Colors colors;
};

}
