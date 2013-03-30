project(share-footprint)

add_executable( footprint main.cpp Colors.cpp )
target_link_libraries( footprint footprint_widgets ${COMMON_LIBS} )

install(TARGETS footprint
        RUNTIME DESTINATION ${SHARE})

add_subdirectory(app_root)
add_subdirectory(doc_root)
