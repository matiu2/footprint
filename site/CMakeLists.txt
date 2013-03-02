project(src)

add_subdirectory(images)
add_subdirectory(widgets)

add_executable( footprint main.cpp )
target_link_libraries( footprint footprint_site_widgets ${COMMON_LIBS} )

install(TARGETS footprint
        RUNTIME DESTINATION bin)
