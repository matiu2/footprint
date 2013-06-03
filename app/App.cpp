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
    auto db = auth->users();
    typedef Wt::Auth::AbstractUserDatabase::Transaction Transaction;
    std::unique_ptr<Transaction, std::function<void(Transaction*)>> t(
         db->startTransaction(), [](Transaction*p){delete p;});
    while (iPair) {
        auto pair = wittyPlus::lazySplit(iPair++, ':');
        std::string username = pair++;
        std::string email = pair++;
        auto user = db->findWithIdentity(Wt::Auth::Identity::LoginName, username);
        if (!user.isValid()) {
            // Send their password
            user = auth->users()->registerNew();
            auth->users()->addIdentity(user, Wt::Auth::Identity::LoginName, username);
            auth->authService()->verifyEmailAddress(user, email);
        }
    }
    t->commit();
}

App::App(const Wt::WEnvironment& env) : wittyPlus::App(env) {
    setTheme(new Wt::WCssTheme("polished", this));
    messageResourceBundle().use(appRoot() + "messages/MainWindow");
    useStyleSheet("/css/footprint.css");
    // Ensure that any users from the config file exist
    std::string users;
    readConfigurationProperty("users", users);
    ensureUsers(users);
    // Run!
    new widgets::MainWindow(root());
};

}
