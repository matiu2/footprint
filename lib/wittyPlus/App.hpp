#ifndef WITTYPLUS_APP_HPP
#define WITTYPLUS_APP_HPP

#include <Wt/WApplication>

#include "Session.hpp"
#include "Auth.hpp"

namespace wittyPlus {

class App : public Wt::WApplication {
private:
    Session* _session;
    Auth* _auth;
public:
    App(const Wt::WEnvironment& env) : Wt::WApplication(env) {
        std::string db;
        readConfigurationProperty("db", db);
        _session = new Session(db);
        _auth = new Auth(this);
    }
    Session* session() { return _session; }
};

} // namespace wittyPlus

#endif // WITTYPLUS_APP_HPP
