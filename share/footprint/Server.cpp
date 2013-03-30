#include "Server.hpp"

#include <Wt/Auth/AuthService>
#include <Wt/Auth/HashFunction>
#include <Wt/Auth/PasswordService>
#include <Wt/Auth/PasswordStrengthValidator>
#include <Wt/Auth/PasswordVerifier>
#include <Wt/Auth/OAuthService>
#include <Wt/Auth/GoogleService>
#include <Wt/Auth/FacebookService>

namespace footprint {

class Server::Auth {
public:
    Wt::Auth::AuthService authService;
    Wt::Auth::PasswordService passwordService;
    std::vector<const Wt::Auth::OAuthService*> oAuthService;
    Auth() : passwordService(authService) {}
    ~Auth() {}
};

Server::Server(const std::string &wtApplicationPath, const std::string &wtConfigurationFile)
    : Wt::WServer(wtApplicationPath, wtConfigurationFile), _auth(new Auth()) {

}

Server::~Server() {}

}
