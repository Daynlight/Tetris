cmake_minimum_required(VERSION 3.10)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "output/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "output/")

### VCPKG vendor location and tiplet
if(WIN32)
  set(VCPKG_TARGET_TRIPLET "x64-mingw-static" CACHE PATH "")
  set(VCPKG_INSTALLED_DIR "${CMAKE_SOURCE_DIR}/vendor" CACHE PATH "")
  set(ZLIB_USE_STATIC_LIBS ON CACHE BOOL "Use static zlib") 
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vendor/x64-mingw-static")
endif()

file(GLOB_RECURSE files 
  "Tetris/**.cpp" 
  "Tetris/**.h" 
  "Tetris/**.hpp")

list(FILTER files EXCLUDE REGEX "Tetris/vendor/.*")

project(Tetris VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

if(WIN32)
  enable_language(RC)
  add_executable(Tetris WIN32 ${files} "Tetris/assets/icons.rc")
else()
  add_executable(Tetris ${files})
endif()

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(PNG REQUIRED)
find_package(Freetype REQUIRED)
find_package(PNG REQUIRED)
find_package(BZip2 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(unofficial-brotli CONFIG QUIET)
add_subdirectory(Tetris/vendor/Data)

target_link_libraries(Tetris PRIVATE
  $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
  $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
  $<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>
  PNG::PNG
  Freetype::Freetype
  PNG::PNG
  BZip2::BZip2
  $<TARGET_NAME_IF_EXISTS:unofficial::brotli::brotlidec>
  $<TARGET_NAME_IF_EXISTS:unofficial::brotli::brotlicommon>
  ZLIB::ZLIB
  Data
)

target_include_directories(Tetris PRIVATE 
  ${SDL2_INCLUDE_DIRS} 
  ${SDL2_TTF_INCLUDE_DIRS}
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Tetris)
set_property(TARGET Tetris PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}$<CONFIG>")
