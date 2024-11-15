cmake_minimum_required(VERSION 3.10)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "output/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "output/")
set(CMAKE_PREFIX_PATH "$ENV{MINGW_PREFIX}")

file(GLOB_RECURSE files 
  "Tetris/**.cpp" 
  "Tetris/**.h" 
  "Tetris/**.hpp")

project(Tetris VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
add_executable(Tetris ${files})

find_package(SDL2 REQUIRED)
target_link_libraries(Tetris PRIVATE ${SDL2_LIBRARIES})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Tetris)
set_property(TARGET Tetris PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}$<CONFIG>")