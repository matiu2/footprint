#ifndef WITTYPLUS_APP_HPP
#define WITTYPLUS_APP_HPP

#include <Wt/WApplication>

#include "Session.hpp"
#include "Auth.hpp"
#include "Urls.hpp"

namespace wittyPlus {

class App : public Wt::WApplication {
private:
    Session* _session;
    Auth* _auth;
    Urls* _urls;
public:
    App(const Wt::WEnvironment& env) : Wt::WApplication(env) {
        std::string db;
        readConfigurationProperty("db", db);
        if (!db.empty()) {
            _session = new Session(db);
            _auth = new Auth(this);
        }
    }
    Session* session() { return _session; }
    Auth* auth() { return _auth; }
    Urls* urls() { return _urls; }
    static App* instance() { return dynamic_cast<App*>(Wt::WApplication::instance()); }
};

} // namespace wittyPlus

#endif // WITTYPLUS_APP_HPP
