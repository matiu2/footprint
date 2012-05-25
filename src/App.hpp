/**
  The Wt Application object for the footprint website
*/

#include <Wt/WApplication>
#include <Wt/WEnvironment>

namespace footprint {

    /// The Application object for the footprint security website
    class App : public Wt::WApplication {
    public:
        App(const Wt::WEnvironment& env) : Wt::WApplication(env) {}
    };

}
