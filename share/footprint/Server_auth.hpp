/// Internal file -- holds the auth services singleton collection
#pragma once
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

struct Server::Auth {
    Wt::Auth::AuthService authService;
    Wt::Auth::PasswordService passwordService;
    std::vector<const Wt::Auth::OAuthService*> oAuthServices;
    Auth() : passwordService(authService) {
        // Configure the services
        authService.setAuthTokensEnabled(true, "footprint_auth");
        authService.setEmailVerificationEnabled(true);
        auto verifier = new Wt::Auth::PasswordVerifier();
        verifier->addHashFunction(new Wt::Auth::BCryptHashFunction(7));
        passwordService.setVerifier(verifier);
        passwordService.setAttemptThrottlingEnabled(true);
        passwordService.setStrengthValidator(new Wt::Auth::PasswordStrengthValidator());

        if (Wt::Auth::GoogleService::configured())
            oAuthServices.push_back(new Wt::Auth::GoogleService(authService));
    }
    static const Server::Auth* instance() { return Server::instance()->_auth.get(); }
};

}
