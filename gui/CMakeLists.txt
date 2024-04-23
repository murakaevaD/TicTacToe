set(SOURCES
    mainwindow.cpp
)

set(HEADERS
    mainwindow.h
)

set(UI
    mainwindow.ui
)

qt_wrap_ui(UI_HEADERS ${UI})

add_executable(gui ${SOURCES} ${HEADERS} ${UI_HEADERS}
    main.cpp)
target_link_libraries(gui core Qt${QT_VERSION_MAJOR}::Widgets)
target_include_directories(gui PRIVATE ${CMAKE_SOURCE_DIR}/src)
