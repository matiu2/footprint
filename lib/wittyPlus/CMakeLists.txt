project (wittyPlus)

add_library(wittyPlus SHARED Auth.cpp Server.cpp Session.cpp)
target_link_libraries( wittyPlus ${COMMON_LIBS} )
