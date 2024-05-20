cmake_minimum_required(VERSION 3.16)
project(TicTacToeTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "C:/Qt6/6.6.1/mingw_64")

find_package(Qt6 COMPONENTS Widgets Test REQUIRED)

enable_testing()

add_executable(TicTacToeTests
    tictactoetests.cpp
    tictactoetests.h
    ../src/gameboard.cpp
    ../src/gameboard.h
)
install(TARGETS TicTacToeTests DESTINATION tests)
target_link_libraries(TicTacToeTests Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Test)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/gui)

add_test(NAME TicTacToeTest COMMAND TicTacToeTests)
