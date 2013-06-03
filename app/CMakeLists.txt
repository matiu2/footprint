project(footprint)

add_subdirectory(widgets)

add_library( app SHARED App.cpp Colors.cpp )
target_link_libraries( app widgets )

add_subdirectory(app_root)
add_subdirectory(doc_root)
add_subdirectory(tests)

if (${USE_POSTGRES})
set( DB_LIB base_db_postgres )
else()
set( DB_LIB base_db_sqlite )
endif()

add_executable( footprint main.cpp )
target_link_libraries( footprint ${DB_LIB} app ${WT_HTTP} ) # DB_LIB must be first as wittyPlus session needs it

install(TARGETS footprint
        RUNTIME DESTINATION ${SHARE})
