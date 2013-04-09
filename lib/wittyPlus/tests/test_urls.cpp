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
    BOOST_REQUIRE(branch);
    branch->onSelected("products");
    BOOST_REQUIRE(called);
}

BOOST_AUTO_TEST_CASE( triple ) {
    std::string result="";
    auto callBack = [&](const std::string& url) { result = url; };
    urls.addPath("products/edit/attributes", callBack);
    auto& root = urls._impl->registry;
    // First Level exists "products"
    auto found = root.find("products");
    if (found == root.end())
        BOOST_FAIL("No node added to registry");
    wittyPlus::UrlTreeBranch* branch = found->second;
    BOOST_REQUIRE(branch);
    // Second level exists "edit"
    found = branch->children.find("edit");
    if (found == root.end())
        BOOST_FAIL("No second node");
    branch = found->second;
    BOOST_REQUIRE(branch);
    // Second level exists "attributes"
    found = branch->children.find("attributes");
    if (found == root.end())
        BOOST_FAIL("No third node");
    branch = found->second;
    BOOST_REQUIRE(branch);
    // Should be here now
    branch->onSelected("products/edit/attributes/4");
    BOOST_CHECK_EQUAL(result, "products/edit/attributes/4");
}

BOOST_AUTO_TEST_CASE( full ) {

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
