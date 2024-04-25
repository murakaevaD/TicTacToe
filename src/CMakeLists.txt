set(SOURCES
    gameboard.cpp
)

set(HEADERS
    gameboard.h
)

add_library(core ${SOURCES} ${HEADERS})
target_link_libraries(core Qt6::Widgets)
