project(widgets)

add_library(widgets STATIC MainWindow.cpp Auth.cpp)
target_link_libraries(widgets wittyPlus)
