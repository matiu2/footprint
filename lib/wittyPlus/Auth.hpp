/// Interface to everything auth related
#pragma once

#include <Wt/WObject>
#include <Wt/WApplication>
#include <Wt/Auth/AuthService>
#include <Wt/Auth/AbstractUserDatabase>

namespace wittyPlus {

class Auth : public Wt::WObject {
private:
    class Impl;
    Impl* _impl;
public:
    Auth(Wt::WApplication* app);
    const Wt::Auth::AuthService* authService();
    const Wt::Auth::AbstractUserDatabase* users();
};

}
