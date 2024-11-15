cmake_minimum_required(VERSION 3.0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "output/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "output/")

set(GLOB_RECURSE files 
  "Tetris/**.cpp" 
  "Tetris/**.h" 
  "Tetris/**.hpp")

project(Tetris VERSION 1.0 LANGUAGE CXX)
add_executable(Tetris ${files})
set(CXX_STANDARD 20)


set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Tetris)
set_property(TARGET Tetris PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}$<CONFIG>")