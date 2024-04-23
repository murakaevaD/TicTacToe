set(SOURCES
    mainwindow.cpp
)

set(HEADERS
    mainwindow.h
)

set(UI
    mainwindow.ui
)


add_executable(gui ${SOURCES} ${HEADERS} ${UI_HEADERS})
target_link_libraries(gui core Qt${QT_VERSION_MAJOR}::Widgets)
