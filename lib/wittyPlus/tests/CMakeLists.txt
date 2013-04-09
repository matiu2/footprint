project (tests)

ADD_DEFINITIONS( -fno-access-control ) # So tests can access private members of the classes they're testing
ADD_DEFINITIONS( -DBOOST_TEST_DYN_LINK -DBOOST_TEST_MAIN ) # So boost generates the main func for every test suite

# A Function for integrating BOOST.TEST and CTEST a little bit
# if MAIN_NAME is 'number':
#   source file will be: test_number.cpp
#   executable file will be: test_number
# Any other args are the tests to run on it
function(boost_test MAIN_NAME)
    set(EXE_NAME test_${MAIN_NAME})
    ADD_EXECUTABLE(${EXE_NAME} test_${MAIN_NAME}.cpp)
    TARGET_LINK_LIBRARIES(${EXE_NAME} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${WT_TEST} ${COMMON_LIBS} ${DB_LIBS} wittyPlus)
    FOREACH(TEST IN ITEMS ${ARGN})
        ADD_TEST(
            ${TEST}
            ${EXE_NAME} -i -s --detect_fp_exceptions=y --log-level=all --run_test=${MAIN_NAME}_suite/${TEST})
        if (${RUN_MEM_TESTS})
            ADD_TEST(
                ${TEST}_valgrind
                valgrind --leak-check=yes --log-file=valgrind_${TEST}.out.txt ./${EXE_NAME} -i -s
                         --detect_fp_exceptions=y --log-level=all DEBUG --run_test=${MAIN_NAME}_suite/${TEST})
        endif()
    endforeach()
endfunction()

boost_test(
    urls
    empty
    simple
    urls_test
)

boost_test(
    sub_divided
    comparison_operators
    lazy_splitting
    lazy_splitting_strings
    sorting
)
