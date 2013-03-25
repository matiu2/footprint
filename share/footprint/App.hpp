/**
  The Wt Application object for the footprint website
*/

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WText>
#include <Wt/WCssTheme>

#include "Colors.hpp"

#include "../../widgets/MainWindow.hpp"

namespace footprint {

    /// The Application object for the footprint security website
    class App : public Wt::WApplication {
    public:
        App(const Wt::WEnvironment& env) : Wt::WApplication(env) {
            setTheme(new Wt::WCssTheme("polished", this));
            messageResourceBundle().use(appRoot() + "messages/MainWindow");
            useStyleSheet("/css/footprint.css");
            new widgets::MainWindow(root());
        };
        Colors colors;
    };

}
