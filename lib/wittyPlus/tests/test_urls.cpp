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
    wittyPlus::UrlTreeBranch* branch = found->second.get();
    BOOST_REQUIRE(branch);
    BOOST_REQUIRE(branch->onSelected);
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
    wittyPlus::UrlTreeBranch* branch = found->second.get();
    BOOST_REQUIRE(branch);
    // Second level exists "edit"
    found = branch->children.find("edit");
    if (found == root.end())
        BOOST_FAIL("No second node");
    branch = found->second.get();
    BOOST_REQUIRE(branch);
    // Second level exists "attributes"
    found = branch->children.find("attributes");
    if (found == root.end())
        BOOST_FAIL("No third node");
    branch = found->second.get();
    BOOST_REQUIRE(branch);
    // Should be here now
    BOOST_REQUIRE(branch->onSelected);
    branch->onSelected("products/edit/attributes/4");
    BOOST_CHECK_EQUAL(result, "products/edit/attributes/4");
}

BOOST_AUTO_TEST_CASE( full ) {

    std::string whatWasCalled = "Nothing";
    std::string urlReturned = "";

    urls.addPath("products/cameras/edit", [&](const std::string& url) {
        whatWasCalled = "Edit";
        urlReturned = url;
    });
    urls.addPath("products/cameras", [&](const std::string& url) {
        whatWasCalled = "Show";
        urlReturned = url;
    });
    auto check = [&](const std::string& expectedUrl, const std::string& expectedCall) {
        whatWasCalled = "Nothing";
        urlReturned = "";
        pathChanged(expectedUrl);
        BOOST_CHECK_EQUAL(expectedUrl, urlReturned);
        if (expectedCall != whatWasCalled) {
            std::stringstream msg;
            msg << "For url: '" << expectedUrl << "' "
                << "we expected '" << expectedCall << "' to be called "
                << "but '" << whatWasCalled << "' was called instead";
            BOOST_ERROR(msg.str());
        }
    };

    check("/products/cameras", "Show");
    check("/products/cameras/1", "Show");
    check("/products/cameras/1/2/3", "Show");
    check("/products/cameras/1/2/3?a=b&c=d", "Show");
    check("/products/cameras/edit", "Edit");
    check("/products/cameras/edit/1", "Edit");
    check("/products/cameras/edit/1/2/3", "Edit");
    check("/products/cameras/edit/1/2/3?a=b&c=d", "Edit");
}

BOOST_AUTO_TEST_SUITE_END()
