project (tests)

ADD_DEFINITIONS( -fno-access-control ) # So tests can access private members of the classes they're testing
ADD_DEFINITIONS( -DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN ) # So boost generates the main func for every test suite

set(EXTRA_TEST_LIBS base_db_sqlite app)

# NOTE: ensureUsers is not included in the main set of tests due to it's waiting forever at the end, and the smtp bits
boost_test(
    app
    empty
)

