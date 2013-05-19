#include "App.hpp"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <vector>

#include <Wt/Auth/Identity>

#include <wittyPlus/Auth.hpp>
#include <wittyPlus/SubDivided.hpp>


namespace footprint {

void ensureUsers(const std::string& users) {
    /// Make sure our users from the config file exist
    /// @param users a string in the format "username:email,username:email"
    auto auth = wittyPlus::Auth::instance();
    auto iPair = wittyPlus::lazySplit(users, ',');
    while (iPair) {
        auto pair = wittyPlus::lazySplit(iPair++, ':');
        std::string username = pair++;
        std::string email = pair++;
        auto user = auth->users()->findWithEmail(email);
        if (!user.isValid()) {
            // Create the user
            user = auth->users()->registerNew();
            auth->users()->addIdentity(user, Wt::Auth::Identity::LoginName, username);
            auth->authService()->verifyEmailAddress(user, email);
        }
    }
}

App::App(const Wt::WEnvironment& env) : wittyPlus::App(env) {
    setTheme(new Wt::WCssTheme("polished", this));
    messageResourceBundle().use(appRoot() + "messages/MainWindow");
    useStyleSheet("/css/footprint.css");
    std::string db;
    readConfigurationProperty("db", db);
    std::cerr << "DB is: " << db << std::endl;
    // Ensure that any users from the config file exist
    std::string users;
    readConfigurationProperty("users", users);
    ensureUsers(users);
    // Run!
    new widgets::MainWindow(root());
};

}
