/**
  The Wt Application object for the footprint website
*/

#include <map>
#include <functional>

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WText>
#include <Wt/WCssTheme>

#include <wittyPlus/App.hpp>


#include "Colors.hpp"

#include "../../widgets/MainWindow.hpp"

namespace footprint {

/// The Application object for the footprint security website
class App : public wittyPlus::App {
private:
    std::map<std::string, std::function<void(const std::string&)>> _urlMapper;
    void onUrlChange(const std::string& url);
public:
    App(const Wt::WEnvironment& env);
    Colors colors;
    void mapUrl(const std::string url, std::function<void(const std::string&)> func) { _urlMapper[url] = func; }
};

}
