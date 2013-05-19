
# A Function for integrating BOOST.TEST and CTEST a little bit
# if MAIN_NAME is 'number':
#   source file will be: test_number.cpp
#   executable file will be: test_number
# Any other args are the tests to run on it
function(boost_test MAIN_NAME)
    set(EXE_NAME test_${MAIN_NAME})
    ADD_EXECUTABLE(${EXE_NAME} test_${MAIN_NAME}.cpp)
    TARGET_LINK_LIBRARIES(${EXE_NAME} ${EXTRA_TEST_LIBS} test_base )
    FOREACH(TEST IN ITEMS ${ARGN})
        ADD_TEST(
            ${MAIN_NAME}.${TEST}
            ${EXE_NAME} -i -s --detect_fp_exceptions=y --log-level=all --run_test=${MAIN_NAME}_suite/${TEST})
        if (${RUN_MEM_TESTS})
            ADD_TEST(
                ${TEST}_valgrind
                valgrind --leak-check=full --log-file=valgrind_${TEST}.out.txt ./${EXE_NAME} -i -s
                         --detect_fp_exceptions=y --log-level=all DEBUG --run_test=${MAIN_NAME}_suite/${TEST})
        endif()
    endforeach()
endfunction()
