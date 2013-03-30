project(widgets)

add_library(footprint_widgets SHARED MainWindow.cpp)
target_link_libraries( footprint_widgets ${COMMON_LIBS} )

install(TARGETS footprint_widgets
        LIBRARY DESTINATION lib)
