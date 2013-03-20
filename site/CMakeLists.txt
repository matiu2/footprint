project(src)

file(COPY resources DESTINATION .)

add_subdirectory(images)
add_subdirectory(widgets)

add_executable( footprint main.cpp )
target_link_libraries( footprint footprint_site_widgets ${COMMON_LIBS} )

# Dev run env

file(COPY run.sh DESTINATION .)
configure_file(wt_config.xml.in wt_config.xml)

# Installation

install(TARGETS footprint
        RUNTIME DESTINATION bin)
