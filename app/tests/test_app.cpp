#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <boost/filesystem.hpp>

#include <Wt/Test/WTestEnvironment>

#include "../App.hpp"

namespace fs = boost::filesystem;

class Fixture {
private:
    std::unique_ptr<Wt::Test::WTestEnvironment> _env;
    std::map<std::string, std::string> properties;
    void writeConfigFile() {
        config_file << "<server>\n"
                    << "<properties>\n";
        for (auto property : properties) {
            config_file << "<property name=\""
                        << property.first
                        << "\">"
                        << property.second
                        << "</property>\n";
        }
        config_file << "</properties>\n"
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
        setProperty("db", ":memory:");
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
            _env.reset(new Wt::Test::WTestEnvironment(temp_dir.string(), config_file_name().string()));
        }
        return _env.get();
    }
};

BOOST_FIXTURE_TEST_SUITE( app_suite , Fixture );

BOOST_AUTO_TEST_CASE( empty ) {
    // Just check that it can be created and destroyed without error
}

BOOST_AUTO_TEST_CASE( ensureUseres ) {
    /// Test that 'ensureUsers is called on app creation, and can parse the config correctly
    setProperty("users", "matiu:msherborne@gmail.com,happy:msherborne+happy@gmail.com");
    footprint::App app(*env());
    auto auth = wittyPlus::Auth::instance();
    std::vector<std::pair<std::string, std::string>> expected = {
        {"matiu", "msherborne@gmail.com"},
        {"happy", "msherborne+happy@gmail.com"}
    };
    for (const auto& pair : expected) {
        auto user = auth->users()->findWithEmail(pair.second);
        BOOST_CHECK_EQUAL(Wt::Auth::User::EmailTokenRole::VerifyEmail, user.emailTokenRole());
        BOOST_CHECK_EQUAL(pair.first, user.id());
    }
}

BOOST_AUTO_TEST_SUITE_END()
