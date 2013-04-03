#include "App.hpp"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdexcept>

#include <Wt/Auth/Identity>
#include <wittyPlus/Auth.hpp>


namespace footprint {

void ensureUsers(App* app) {
    /// Make sure our users from the config file exist
    std::string input;
    app->readConfigurationProperty("users", input);
    // It's in the format: "username:email,username:email"
    std::string id_pair;
    auto auth = wittyPlus::Auth::instance();
    auto prev = input.begin();
    decltype(prev) next;
    auto readString = [&] (char delim) -> std::string {
        next = std::find(prev, input.end(), delim);
        if (next == input.end())
            return "";
        std::string out;
        out.reserve(next - prev);
        std::copy(prev, next-1, std::back_inserter(out));
        prev = next+1;
        return out;
    };
    while (1) {
        // Read the username
        std::string username = readString(':');
        // Read the email address
        std::string email =  readString(',');
        if (email.empty())
            break; // Nothing read
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
    // Run!
    new widgets::MainWindow(root());
};

void App::onUrlChange(const std::string& url) {
    // Split it into parts
    std::string part;
    auto delim = std::find(url.begin(), url.end(), '/');
    while (delim != url.end()) {
    }
}


}
