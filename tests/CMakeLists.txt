cmake_minimum_required(VERSION 3.16)
project(TicTacToeTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "C:/Qt6/6.6.1/mingw_64")
find_package(Qt6 COMPONENTS Widgets Test REQUIRED)

add_subdirectory(googletest)
enable_testing()

add_library(game_logic ../src/gameboard.cpp)
target_include_directories(game_logic PUBLIC ../src)

add_executable(tictactoe_tests tictactoetests.cpp)
target_link_libraries(tictactoe_tests game_logic gtest gtest_main Qt6::Widgets Qt6::Test)

target_include_directories(tictactoe_tests PRIVATE ${gtest_SOURCE_DIR}/include)
