project(base_db)

# Postgres
find_library(POSTGRES_LIBRARY pq)


if ( ${DEBUG} )
    find_library( WT_DBO NAMES wtdbod wtdbo )
    find_library( WT_DBO_POSTGRES NAMES wtdbopostgresd wtdbopostgres )
    find_library( WT_DBO_SQLITE NAMES wtdbosqlite3d wtdbosqlite3 )
else()
    find_library( WT_DBO NAMES wtdbo )
    find_library( WT_DBO_POSTGRES NAMES wtdbopostgres )
    find_library( WT_DBO_SQLITE NAMES wtdbosqlite3 )
endif()

option(USE_POSTGRES "Use postgres instead of sqlite" Off )

if (${USE_POSTGRES})
    add_library(base_db_postgres SHARED base_db_postgres.cpp)
    TARGET_LINK_LIBRARIES(base_db_postgres ${WT_DBO} ${POSTGRES_LIBRARY} ${WT_DBO_POSTGRES} )

    add_library(base_db_sqlite SHARED base_db_sqlite.cpp)
    TARGET_LINK_LIBRARIES(base_db_sqlite ${WT_DBO} ${SQLITE_LIBRARY} ${WT_DBO_SQLITE} )
else()
    add_library(base_db_sqlite SHARED base_db_sqlite.cpp)
    TARGET_LINK_LIBRARIES(base_db_sqlite ${WT_DBO} ${SQLITE_LIBRARY} ${WT_DBO_SQLITE} )
endif()
