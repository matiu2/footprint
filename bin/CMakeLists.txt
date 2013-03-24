project(bin)

set(ETC_DBG ${CMAKE_BINARY_DIR}/${ETC})
set(SHARE_DBG ${CMAKE_BINARY_DIR}/${SHARE})
set(APP_ROOT_DBG ${CMAKE_BINARY_DIR}/${APP_ROOT})
set(DOC_ROOT_DBG ${CMAKE_BINARY_DIR}/${DOC_ROOT})

configure_file(debug.in debug)

set(ETC ${CMAKE_INSTALL_PREFIX}/${ETC})
set(SHARE ${CMAKE_INSTALL_PREFIX}/${SHARE})
set(APP_ROOT ${CMAKE_INSTALL_PREFIX}/${APP_ROOT})
set(DOC_ROOT ${CMAKE_INSTALL_PREFIX}/${DOC_ROOT})

configure_file(footprint.in footprint)

install(PROGRAMS ${CMAKE_CURRENT_BUILD_DIR}/footprint
        DESTINATION bin/footprint)

configure_file(footprint.in footprint)
