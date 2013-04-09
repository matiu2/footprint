#include "Auth.hpp"

#include <stdexcept>

#include "Session_impl.hpp"
#include "Server_auth.hpp"
#include "App.hpp"

namespace wittyPlus {

struct Auth::Impl : public Wt::WObject {
    const Server::Auth* services;
    Session::Impl* session_impl;
    Auth* _auth;
    Impl(Auth* parent, App* app) : Wt::WObject(parent) {
        if (app == nullptr)
            throw std::logic_error("Can't get the session from the running app");
        services = Server::Auth::instance();
        if (services == nullptr)
            throw std::logic_error("Couldn't find a wittyPlus server");
        Session* session = app->session();
        session_impl = session->impl();
    }
};

Auth::Auth(Wt::WApplication* app) {
    _impl = new Impl(this, dynamic_cast<App*>(app));
}

const Wt::Auth::AuthService* Auth::authService() {
    return &_impl->services->authService;
}

const Wt::Auth::PasswordService* Auth::passwordService() {
    return &_impl->services->passwordService;
}

Wt::Auth::AbstractUserDatabase* Auth::users() {
    return &_impl->session_impl->users;
}

Wt::Auth::Login* Auth::login() {
    return &_impl->session_impl->login;
}

Auth* Auth::instance() {
    App* app = dynamic_cast<App*>(Wt::WApplication::instance());
    return app->auth();
}

}
