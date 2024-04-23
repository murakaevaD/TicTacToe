set(SOURCES
    main.cpp
    gameboard.cpp
)

set(HEADERS
    gameboard.h
)

add_library(core ${SOURCES} ${HEADERS})
target_link_libraries(core Qt${QT_VERSION_MAJOR}::Widgets)
