#include "Auth.hpp"

#include <Wt/Auth/AuthWidget>
#include <Wt/Auth/PasswordService>

#include <wittyPlus/Auth.hpp>

namespace footprint {
namespace widgets {

Auth::Auth(Wt::WContainerWidget* parent) : Wt::WContainerWidget(parent) {
    wittyPlus::Auth* auth = wittyPlus::Auth::instance();
    Wt::Auth::AuthWidget* widget = new Wt::Auth::AuthWidget(
        *auth->authService(), *auth->users(), *auth->login());
    widget->model()->addPasswordAuth(auth->passwordService());
    widget->setRegistrationEnabled(true);
    widget->processEnvironment();
    addWidget(widget);
}

} // namespace widgets
} // namespace footprint
