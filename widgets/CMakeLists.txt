project(widgets)

add_library(footprint_widgets SHARED MainWindow.cpp)

install(TARGETS footprint_widgets
        LIBRARY DESTINATION lib)
