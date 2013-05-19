project(widgets)

add_library(footprint_widgets SHARED MainWindow.cpp Auth.cpp)
target_link_libraries( footprint_widgets ${WT} ${BOOST_LIBS} )

install(TARGETS footprint_widgets
        LIBRARY DESTINATION lib)
