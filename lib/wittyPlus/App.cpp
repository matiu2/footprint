#include "App.hpp"

#include "Services.hpp"

#include <Wt/WServer>

#include <signal.h>

namespace wittyPlus {

int WRun(int argc, char** argv, std::function<App*(const Wt::WEnvironment&)> createApp) {
    try {
        Services services; // Globalish var, used via Services::instance();
        Wt::WServer server(argv[0], "");
        server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);
        server.addEntryPoint(Wt::Application, createApp);
        if (server.start()) {
            int sig = Wt::WServer::waitForShutdown(argv[0]);
            std::cerr << "Shutdown (signal = " << sig << ")" << std::endl;
            server.stop();
            if (sig == SIGHUP)
                Wt::WServer::restart(argc, argv, environ);
        }
    } catch (Wt::WServer::Exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 2;
    }
    return 0;
}

}
