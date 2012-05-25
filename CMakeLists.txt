cmake_minimum_required( VERSION 2.8 )

project( footprint )

add_definitions(-std=c++11)

# Decide if this is a debug build or not
string(COMPARE EQUAL "${CMAKE_BUILD_TYPE}" "Debug" DEBUG) # If the build type is set to debug, set the ${DEBUG} variable

# Boost libraries
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_COMPILER "-gcc46")
find_package( Boost 1.49 COMPONENTS system program_options filesystem )
include_directories(${Boost_INCLUDE_DIRS})
SET( BOOST_LIBS ${BOOST_SYSTEM_LIB} ${BOOST_PROGRAM_OPTIONS_LIB} ${BOOST_FILESYSTEM_LIB} )

# Load the wt libraries, search for debug ones if appropriate
if ( ${DEBUG} )
    find_library( WT NAMES wtd wt )
    find_library( WT_HTTP NAMES wthttpd wthttp )
    find_library( WT_DBO NAMES wtdbod wtdbo )
    find_library( WT_DBO_POSTGRES NAMES wtdbopostgresd wtdbopostgres )
else()
    find_library( WT NAMES wt )
    find_library( WT_HTTP NAMES wthttp )
    find_library( WT_DBO NAMES wtdbo )
    find_library( WT_DBO_POSTGRES NAMES wtdbopostgres )
endif()
SET( WT_LIBS ${WT} ${WT_HTTP} ${WT_DBO} ${WT_DBO_POSTGRES} )

# Basically everything will link against ${COMMON_LIBS}
SET( COMMON_LIBS ${BOOST_LIBS} ${WT_LIBS} )

add_subdirectory(src)
