project (wittyPlus)

add_library(wittyPlus SHARED Auth.cpp Server.cpp Session.cpp Urls.cpp)
target_link_libraries( wittyPlus ${COMMON_LIBS} )

enable_testing()

add_subdirectory(tests)
