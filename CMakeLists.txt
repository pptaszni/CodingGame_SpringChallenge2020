cmake_minimum_required(VERSION 3.0.2)
project(CodingGame_Pacman CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -O -g -pthread")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin)

add_subdirectory(GameController)
add_subdirectory(tests)

add_executable(main main.cpp)
target_link_libraries(main GameController)
