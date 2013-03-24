/**
  The Wt Application object for the footprint website
*/

#include <Wt/WApplication>
#include <Wt/WEnvironment>
#include <Wt/WText>
#include <Wt/WBootstrapTheme>
#include "widgets/MainWindow.hpp"

namespace footprint {

    /// The Application object for the footprint security website
    class App : public Wt::WApplication {
    public:
        App(const Wt::WEnvironment& env) : Wt::WApplication(env) {
            setTheme(new Wt::WBootstrapTheme(this));
            messageResourceBundle().use(docRoot() + 'messages/MainWindow');
            new widgets::MainWindow(root());
        };
    };

}
