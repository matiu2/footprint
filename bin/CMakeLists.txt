project(bin)

configure_file(debug.in debug)

configure_file(footprint.in footprint)

install(PROGRAMS ${CMAKE_CURRENT_BUILD_DIR}/footprint
        DESTINATION bin/footprint)

configure_file(footprint.in footprint)
