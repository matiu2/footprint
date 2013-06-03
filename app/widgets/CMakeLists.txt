project(widgets)

add_library(widgets SHARED MainWindow.cpp Auth.cpp)
target_link_libraries(widgets wittyPlus)
