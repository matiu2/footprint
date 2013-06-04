project (tests)

ADD_DEFINITIONS( -fno-access-control ) # So tests can access private members of the classes they're testing
ADD_DEFINITIONS( -DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN ) # So boost generates the main func for every test suite

set(EXTRA_TEST_LIBS wittyPlus base_db_sqlite)

boost_test(
    urls
    empty
    simple
    triple
    full
)

boost_test(
    sub_divided
    comparison
    lazy_splitting
    lazy_splitting_strings
    sorting
)
