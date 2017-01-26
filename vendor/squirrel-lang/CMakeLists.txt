cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(squirrel-lang VERSION 3.0.7)

option(SQUIRREL_BUILD_CONSOLE "Build squirrel console executable" OFF)
option(SQUIRREL_USE_DOUBLE "Use double precision for SQFloat" OFF)
option(SQUIRREL_USE_WCHAR "Use wide characters strings" OFF)

add_subdirectory(squirrel)
add_subdirectory(sqstdlib)

if(SQUIRREL_BUILD_CONSOLE)
    add_subdirectory(sq)
endif()
