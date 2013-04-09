#include <sstream>
#include <string>

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

#include "../Urls_impl.hpp"

#include <Wt/WSignal>

struct Fixture {
    Wt::Signal<std::string> pathChanged;
    wittyPlus::Urls urls = {nullptr, pathChanged};
};

BOOST_FIXTURE_TEST_SUITE( urls_suite , Fixture );

BOOST_AUTO_TEST_CASE( empty ) {
    // Just check that it can be created and destroyed without error
}

BOOST_AUTO_TEST_CASE( simple ) {
    bool called = false;
    auto callBack = [&](const std::string& url) { called = true; };
    urls.addPath("products", callBack);
    auto& root = urls._impl->registry;
    auto found = root.find("products");
    if (found == root.end())
        BOOST_FAIL("No node added to registry");
    wittyPlus::UrlTreeBranch* branch = found->second;
    branch->onSelected("products");
    BOOST_REQUIRE(called);
}

BOOST_AUTO_TEST_CASE( urls_test ) {

    std::stringstream events;
    std::stringstream expected;

    urls.addPath("products/cameras/edit", [&](const std::string& url) {
        events.clear();
        events << "edit: " << url;});
    urls.addPath("products/cameras", [&](const std::string& url) {
        events.clear();
        events << "show: " << url;});

    auto check = [&](const std::string& url, const std::string& action) {
        events.clear();
        expected.clear();
        expected << action << ": " << url;
        pathChanged(url);
        BOOST_CHECK_EQUAL(expected.str(), events.str());
    };

    const char *show = "show",
               *edit = "edit";


    check("/products/cameras/1", show);
    check("/products/cameras/edit", edit);
    check("/products/cameras/edit/1", edit);
}

BOOST_AUTO_TEST_SUITE_END()
