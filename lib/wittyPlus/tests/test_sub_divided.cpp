/**
 * */

#include "../SubDivided.hpp"

#include <vector>
#include <algorithm>

#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>

struct Fixture {
    std::string abc = "abc";
    std::string abc2 = "abc";
    std::string abcd = "abcd";
    std::string abd = "abd";

    std::string path = "/path/to/somewhere/";
    wittyPlus::DelimitedPart<std::string> part = wittyPlus::lazySplit(path, '/');
};

BOOST_FIXTURE_TEST_SUITE( sub_divided_suite , Fixture );

BOOST_AUTO_TEST_CASE( comparison ) {

    // Test comparison operators

    using wittyPlus::make_part;

    BOOST_CHECK(make_part(abc) == make_part(abc2));
    BOOST_CHECK(make_part(abc) <= make_part(abc2));
    BOOST_CHECK(make_part(abc) >= make_part(abc2));

    BOOST_CHECK(make_part(abc) < make_part(abcd));
    BOOST_CHECK(make_part(abc) < make_part(abd));
    BOOST_CHECK(make_part(abc) <= make_part(abcd));
    BOOST_CHECK(make_part(abc) <= make_part(abd));

    BOOST_CHECK(make_part(abcd) > make_part(abc));
    BOOST_CHECK(make_part(abd) > make_part(abc));
    BOOST_CHECK(make_part(abcd) >= make_part(abc));
    BOOST_CHECK(make_part(abd) >= make_part(abc));

    BOOST_CHECK(make_part(abd) != make_part(abc));
    BOOST_CHECK(make_part(abcd) != make_part(abc));
}

BOOST_AUTO_TEST_CASE( lazy_splitting ) {

    // Test splitting

    BOOST_CHECK_EQUAL("path", part);
    ++part;
    BOOST_CHECK_EQUAL("to", part++);
    BOOST_CHECK_EQUAL("somewhere", part++);
    BOOST_CHECK_EQUAL(wittyPlus::Part<std::string>(), part);
    BOOST_CHECK_EQUAL("", part);
}

BOOST_AUTO_TEST_CASE( lazy_splitting_strings ) {
    // Does it work with strings ?
    part = wittyPlus::lazySplit(path, '/');

    BOOST_CHECK_EQUAL(std::string("path"), part++);
    BOOST_CHECK_EQUAL(std::string("to"), part++);
    BOOST_CHECK_EQUAL(std::string("somewhere"), part++);
}

BOOST_AUTO_TEST_CASE( sorting ) {
    // Can you sort them ?
    std::vector<decltype(part)> parts;
    part = wittyPlus::lazySplit(path, '/');
    while (part)
        parts.push_back(part++);
    std::sort(parts.begin(), parts.end());

    BOOST_CHECK_EQUAL("path", parts[0]);
    BOOST_CHECK_EQUAL("somewhere", parts[1]);
    BOOST_CHECK_EQUAL("to", parts[2]);
}

BOOST_AUTO_TEST_SUITE_END()
