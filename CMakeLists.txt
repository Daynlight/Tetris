cmake_minimum_required(VERSION 3.10)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "output/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "output/")

file(GLOB_RECURSE files 
  "Tetris/**.cpp" 
  "Tetris/**.h" 
  "Tetris/**.hpp",
  "Tetris/**.o")

file(GLOB_RECURSE libs
  "Tetris/vendor/**.a")

project(Tetris VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

if(WIN32)
  add_executable(Tetris WIN32 ${files})
else()
  add_executable(Tetris ${files})
endif()

add_subdirectory(Tetris/vendor/SDL2)
add_subdirectory(Tetris/vendor/SDL2_ttf)

target_link_libraries(Tetris PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_ttf)

target_link_libraries(Tetris PRIVATE ${libs})
target_include_directories(Tetris PRIVATE 
  ${SDL2_INCLUDE_DIRS} 
  ${SDL2_TTF_INCLUDE_DIRS}
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Tetris)
set_property(TARGET Tetris PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}$<CONFIG>")