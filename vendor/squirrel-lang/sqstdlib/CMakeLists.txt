cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(sqstdlib VERSION 3.0.7 LANGUAGES CXX)

add_library(sqstdlib STATIC
    sqstdblob.cpp
    sqstdio.cpp
    sqstdstream.cpp
    sqstdmath.cpp
    sqstdsystem.cpp
    sqstdstring.cpp
    sqstdaux.cpp
    sqstdrex.cpp
)

target_include_directories(sqstdlib PRIVATE ../include)

if(MSVC)
    target_compile_definitions(sqstdlib PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(sqstdlib PRIVATE -Wall -O2 -fno-exceptions -fno-rtti -fno-strict-aliasing)
endif()

if(SQUIRREL_USE_WCHAR)
    target_compile_definitions(squirrel PRIVATE SQUNICODE $<$<BOOL:MSVC>:_CRT_NON_CONFORMING_SWPRINTFS>)
endif()
