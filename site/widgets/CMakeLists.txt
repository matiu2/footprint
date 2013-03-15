project(widgets)

add_library(footprint_site_widgets SHARED MainWindow.cpp)

install(TARGETS footprint_site_widgets
        LIBRARY DESTINATION lib)
