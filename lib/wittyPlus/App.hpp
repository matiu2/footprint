#pragma once

#include <cassert>
#include <memory>

#include <Wt/WApplication>

#include "Session.hpp"
#include "Auth.hpp"
#include "Urls.hpp"

namespace wittyPlus {

class App : public Wt::WApplication {
private:
    std::unique_ptr<Session> _session;
    Auth* _auth = nullptr;
    Urls* _urls = nullptr;
public:
    App(const Wt::WEnvironment& env) : Wt::WApplication(env) {
        std::string db;
        readConfigurationProperty("db", db);
        if (!db.empty()) {
            _session.reset(new Session(db));
            _auth = new Auth(this);
        } else {
            log("WARN") << "No DB configuration property found. Unable to load auth, nor session";
        }
    }
    Session* session() {
        assert(_session);
        return _session.get();
    }
    Auth* auth() {
        assert(_auth);
        return _auth;
    }
    Urls* urls() {
        assert(_urls);
        return _urls;
    }
    static App* instance() { return dynamic_cast<App*>(Wt::WApplication::instance()); }
};

} // namespace wittyPlus
