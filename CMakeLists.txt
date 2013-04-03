cmake_minimum_required( VERSION 2.8 )

project( footprint )

add_definitions(-std=c++11)

# Decide if this is a debug build or not
string(COMPARE EQUAL "${CMAKE_BUILD_TYPE}" "Debug" DEBUG) # If the build type is set to debug, set the ${DEBUG} variable

# Boost libraries
find_package( Boost COMPONENTS system signals program_options filesystem )
include_directories(${Boost_INCLUDE_DIRS})
SET( BOOST_LIBS ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SIGNALS_LIBRARY} ${Boost_SYSTEM_LIBRARY} )

if(Boost_FOUND)
      include_directories(${Boost_INCLUDE_DIRS})
endif()

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

find_library(POSTGRES_LIBRARY pq)

# Basically everything will link against ${COMMON_LIBS}
SET( COMMON_LIBS ${WT_LIBS} ${BOOST_LIBS} ${POSTGRES_LIBRARY} )

enable_testing()

# Use our own copy of wittyPlus for now
include_directories("lib")
add_subdirectory("lib/wittyPlus")

SET( COMMON_LIBS wittyPlus ${COMMON_LIBS} )

# User variables for the build/install 
set(ETC "etc" CACHE PATH "The config dir")
set(SHARE "share/footprint" CACHE PATH "The main install directory for the footprint website")
set(APP_ROOT "share/footprint/app_root" CACHE PATH "Where the c++ code loads resources from, not directly published to the web")
set(DOC_ROOT "share/footprint/doc_root" CACHE PATH "Where resources for serving directly to the web are found")

add_subdirectory(widgets)
add_subdirectory(etc)
add_subdirectory(bin)
add_subdirectory(share/footprint)
#add_subdirectory(compass)
#add_subdirectory(tests)

# Nice work env
file(COPY work-live.sh on-file-change.sh DESTINATION .)
