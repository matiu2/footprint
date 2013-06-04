/// Internal file -- holds the auth services singleton collection
#pragma once

#include <Wt/Auth/AuthService>
#include <Wt/Auth/HashFunction>
#include <Wt/Auth/PasswordService>
#include <Wt/Auth/PasswordStrengthValidator>
#include <Wt/Auth/PasswordVerifier>
#include <Wt/Auth/OAuthService>
#include <Wt/Auth/GoogleService>
#include <Wt/Auth/FacebookService>

namespace wittyPlus {

struct Services {
    static const Services* instance() { return _instance; }
    static Services* _instance;
    Wt::Auth::AuthService authService;
    Wt::Auth::PasswordService passwordService;
    Services() : passwordService(authService) {
        assert(_instance == nullptr); // This is a global singleton
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
        _instance = this;
    }
    ~Services() {
        _instance = nullptr;
    }
    std::vector<const Wt::Auth::OAuthService*> oAuthServices;
};

}
