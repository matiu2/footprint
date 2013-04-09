cmake_minimum_required( VERSION 2.8 )

project( footprint )

add_definitions(-std=c++11)

# Decide if this is a debug build or not
string(COMPARE EQUAL "${CMAKE_BUILD_TYPE}" "Debug" DEBUG) # If the build type is set to debug, set the ${DEBUG} variable

# Boost libraries
find_package( Boost COMPONENTS system signals program_options filesystem unit_test_framework )
include_directories(${Boost_INCLUDE_DIRS})
SET( BOOST_LIBS ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SIGNALS_LIBRARY} ${Boost_SYSTEM_LIBRARY} )

if(Boost_FOUND)
      include_directories(${Boost_INCLUDE_DIRS})
endif()

# Postgres
find_library(POSTGRES_LIBRARY pq)

# Sqlite
find_library(SQLITE_LIBRARY sqlite3)

# Load the wt libraries, search for debug ones if appropriate
if ( ${DEBUG} )
    find_library( WT NAMES wtd wt )
    find_library( WT_HTTP NAMES wthttpd wthttp )
    find_library( WT_DBO NAMES wtdbod wtdbo )
    find_library( WT_DBO_POSTGRES NAMES wtdbopostgresd wtdbopostgres )
    find_library( WT_DBO_SQLITE NAMES wtdbosqlite3d wtdbosqlite3 )
    find_library( WT_TEST NAMES wttestd wttest )
else()
    find_library( WT NAMES wt )
    find_library( WT_HTTP NAMES wthttp )
    find_library( WT_DBO NAMES wtdbo )
    find_library( WT_DBO_POSTGRES NAMES wtdbopostgres )
    find_library( WT_DBO_SQLITE NAMES wtdbosqlite3 )
    find_library( WT_TEST NAMES wttest )
endif()
SET( WT_LIBS ${WT} ${WT_HTTP} )
SET( POSTGRES_LIBS ${WT_DBO} ${POSTGRES_LIBRARY} ${WT_DBO_POSTGRES} )
SET( SQLITE_LIBS ${WT_DBO} ${SQLITE_LIBRARY} ${WT_DBO_SQLITE} )

# Basically everything will link against ${COMMON_LIBS} (except DB)
SET( COMMON_LIBS ${WT_LIBS} ${BOOST_LIBS} )

enable_testing()

# User variables for the build/install 
set(ETC "etc" CACHE PATH "The config dir")
set(SHARE "share/footprint" CACHE PATH "The main install directory for the footprint website")
set(APP_ROOT "share/footprint/app_root" CACHE PATH "Where the c++ code loads resources from, not directly published to the web")
set(DOC_ROOT "share/footprint/doc_root" CACHE PATH "Where resources for serving directly to the web are found")
option(RUN_MEM_TESTS "Run tests slower using valgrind to check for memory leaks" Off )
option(USE_POSTGRES "Use postgres instead of sqlite" Off )

if (${USE_POSTGRES})
add_definitions( -D USE_POSTGRES )
set( DB_LIBS ${POSTGRES_LIBS} )
else()
set( DB_LIBS ${SQLITE_LIBS} )
endif()

message( "Using DB Libs: ${DB_LIBS}" )

# Use our own copy of wittyPlus for now
include_directories("lib")
add_subdirectory("lib/wittyPlus")

SET( COMMON_LIBS wittyPlus ${COMMON_LIBS} )

add_subdirectory(widgets)
add_subdirectory(etc)
add_subdirectory(bin)
add_subdirectory(share/footprint)
#add_subdirectory(compass)
#add_subdirectory(tests)

# Nice work env
file(COPY work-live.sh on-file-change.sh DESTINATION .)
