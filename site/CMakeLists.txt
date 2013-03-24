project(src)

file(COPY resources DESTINATION .)

add_subdirectory(images)
add_subdirectory(widgets)

add_executable( footprint main.cpp )
target_link_libraries( footprint footprint_site_widgets ${COMMON_LIBS} )

# Dev run env

set(APP_ROOT "../${APP_ROOT}")

configure_file(run.sh.in run.sh)
file(COPY messages DESTINATION ${APP_ROOT})
configure_file(wt_config.xml.in ${APP_ROOT}/wt_config.xml)

# Installation

install(TARGETS footprint
        RUNTIME DESTINATION bin)
file(INSTALL ${CMAKE_CURRENT_BINARY_DIR}/run.sh DESTINATION bin/footprint_run)
