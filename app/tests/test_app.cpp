#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/filesystem.hpp>

#include <Wt/Test/WTestEnvironment>
#include <Wt/Auth/Identity>
#include <wittyPlus/Server.hpp>

#include "../App.hpp"

namespace fs = boost::filesystem;

class Fixture {
private:
    std::unique_ptr<Wt::Test::WTestEnvironment> _env;
    std::map<std::string, std::string> properties;
    void writeConfigFile() {
        config_file << "<server>\n"
                    << "  <application-settings location=\"*\">\n"
                    << "    <properties>\n";
        for (auto property : properties) {
            config_file << "<property name=\""
                        << property.first
                        << "\">"
                        << property.second
                        << "</property>\n";
        }
        config_file << "    </properties>\n"
                    << "  </application-settings>\n"
                    << "</server>\n";
        config_file.close();
    }
public:
    fs::path temp_dir;
    std::fstream config_file;
    Fixture() : temp_dir(fs::unique_path()) {
        fs::create_directories(temp_dir);
        std::cout << config_file_name().string() << std::endl;
        config_file.open(config_file_name().string(), std::ios_base::out);
        setProperty("db", temp_dir.string() + "/db");
    }
    ~Fixture() {
        _env.reset(nullptr); // Delete the env first, while it can still read the temp dir
        fs::remove_all(temp_dir); // Delete the temp dir, after the 'env' is destroyed
    }
    fs::path config_file_name() { return temp_dir / "wt_config.xml"; }
    void setProperty(const std::string& name, const std::string& value) {
        if (_env)
            throw std::runtime_error("Can't set config file props");
        properties[name] = value;
    }
    Wt::Test::WTestEnvironment* env() {
        if (!_env) {
            writeConfigFile();
            // TODO: Move this to wittyPlus
            _env.reset(new Wt::Test::WTestEnvironment(
                           temp_dir.string(),  config_file_name().string(),
                           Wt::EntryPointType::Application,
                           new wittyPlus::Server(temp_dir.string(), temp_dir.string() + "/wt_config.xml")));
        }
        return _env.get();
    } };

BOOST_FIXTURE_TEST_SUITE( app_suite , Fixture );

BOOST_AUTO_TEST_CASE( empty ) {
    // Just check that it can be created and destroyed without error
}

BOOST_AUTO_TEST_CASE( ensureUsers ) {
    /// Test that 'ensureUsers is called on app creation, and can parse the config correctly
    // TODO: This test sits waiting for a non-existent thread when SocketNotifier's destructor joining a thread
    setProperty("users", "matiu:msherborne@gmail.com,happy:msherborne+happy@gmail.com");
    footprint::App app(*env());
    auto auth = wittyPlus::Auth::instance();
    std::vector<std::pair<std::string, std::string>> expected = {
        {"matiu", "msherborne@gmail.com"},
        {"happy", "msherborne+happy@gmail.com"}
    };
    const auto& USER_NAME = Wt::Auth::Identity::LoginName;
    for (const auto& pair : expected) {
        auto user = auth->users()->findWithIdentity(USER_NAME, pair.first);
        BOOST_REQUIRE(user.isValid());
        BOOST_CHECK_EQUAL(Wt::Auth::User::EmailTokenRole::VerifyEmail, user.emailTokenRole());
        BOOST_CHECK_EQUAL(pair.first, user.identity(Wt::Auth::Identity::LoginName)); // Check username
        BOOST_CHECK_EQUAL(pair.second, user.unverifiedEmail()); // Check unverified email
    }
}

BOOST_AUTO_TEST_SUITE_END()
