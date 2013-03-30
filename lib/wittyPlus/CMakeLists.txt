project (wittyPlus)

add_library(wittyPlus Auth.cpp Server.cpp Session.cpp)
target_link_libraries( wittyPlus ${COMMON_LIBS} )
