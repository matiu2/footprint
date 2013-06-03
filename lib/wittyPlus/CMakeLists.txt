project (wittyPlus)


add_library(wittyPlus SHARED Auth.cpp Server.cpp Session.cpp SubDivided.cpp Urls.cpp Urls_impl.cpp)
target_link_libraries(wittyPlus ${WT} ${BOOST_LIBS})

enable_testing()

add_subdirectory(base_db)
add_subdirectory(tests)
