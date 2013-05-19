cmake_minimum_required( VERSION 2.8 )

project( footprint )

add_definitions(-std=c++11)

include(cmake/test_funcs.cmake)

# Decide if this is a debug build or not
string(REGEX MATCH Release HAS_RELEASE "${CMAKE_BUILD_TYPE}") # If the build type is set to debug, set the ${DEBUG} variable
string(COMPARE NOTEQUAL "${HAS_RELEASE}" Release DEBUG)

# Boost libraries
find_package( Boost COMPONENTS system signals program_options filesystem unit_test_framework )
include_directories(${Boost_INCLUDE_DIRS})
SET( BOOST_LIBS ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SIGNALS_LIBRARY} ${Boost_SYSTEM_LIBRARY} )

if(Boost_FOUND)
      include_directories(${Boost_INCLUDE_DIRS})
endif()

# Sqlite
find_library(SQLITE_LIBRARY sqlite3)

# Load the wt libraries, search for debug ones if appropriate
if ( ${DEBUG} )
    find_library( WT NAMES wtd wt )
    find_library( WT_HTTP NAMES wthttpd wthttp )
    find_library( WT_TEST NAMES wttestd wttest )
else()
    find_library( WT NAMES wt )
    find_library( WT_HTTP NAMES wthttp )
    find_library( WT_TEST NAMES wttest )
endif()

add_library(test_base empty.cpp)
TARGET_LINK_LIBRARIES(test_base ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${WT_TEST} ${SQLITE_LIBS})

enable_testing()

# User variables for the build/install 
set(ETC "etc" CACHE PATH "The config dir")
set(SHARE "share/footprint" CACHE PATH "The main install directory for the footprint website")
set(APP_ROOT "share/footprint/app_root" CACHE PATH "Where the c++ code loads resources from, not directly published to the web")
set(DOC_ROOT "share/footprint/doc_root" CACHE PATH "Where resources for serving directly to the web are found")
option(RUN_MEM_TESTS "Run tests slower using valgrind to check for memory leaks" Off )

# Use our own copy of wittyPlus for now
include_directories("lib")
add_subdirectory("lib/wittyPlus")

add_subdirectory(etc)
add_subdirectory(bin)
add_subdirectory(app)
#add_subdirectory(compass)
#add_subdirectory(tests)

# Nice work env
file(COPY work-live.sh on-file-change.sh DESTINATION .)
