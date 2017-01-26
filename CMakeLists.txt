###
# CMake entry point
###
cmake_minimum_required (VERSION 2.8)
project (Server)


###
# Predefines to block make at the root
###
if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
    message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
    message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()


## trying to disable
## raknet static lib, still no success
option(RAKNET_ENABLE_DLL "Generate the DLL project if true." OFF)
option(RAKNET_ENABLE_SAMPLES "" OFF)
option(OSG_GL_LIBRARY_STATIC "" ON)
SET(RAKNET_ENABLE_DLL OFF CACHE BOOL "Generate the DLL project if true.")
SET(OSG_GL_LIBRARY_STATIC ON CACHE BOOL "Set to ON to statically link with OpenGL/GLES library.")
ADD_DEFINITIONS(-DOSG_LIBRARY_STATIC)

###
# Compile vendor dependencies
###
add_subdirectory(vendor/RakNet)
add_subdirectory(vendor/libuv)
add_subdirectory(vendor/squirrel-lang)
add_subdirectory(vendor/bgfx.cmake)

###
# Custom building flags
###
# IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
#   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
# ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

###
# Hacks
# On Visual 2005 and above, this module can set the debug working directory
###
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/vendor/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP
set(CMAKE_MACOSX_RPATH 1)

###
# Includes for libs and remote sources
###
include_directories(
    vendor/RakNet/
    # vendor/squirrel/include
    # vendor/squirrel/squirrel
    vendor/libuv/libuv/include
    shared/
    .
)

file(GLOB_RECURSE SERVER_FILES
  "${PROJECT_SOURCE_DIR}/server/*.cpp"
)

file(GLOB_RECURSE CLIENT_FILES
  "${PROJECT_SOURCE_DIR}/client/*.cpp"
)

# list(REMOVE_ITEM CLIENT_FILES "client/common/entry/entry_android.cpp")
# list(REMOVE_ITEM CLIENT_FILES "client/common/entry/entry_asmjs.cpp")
# list(REMOVE_ITEM CLIENT_FILES "client/common/entry/entry_glfw.cpp")
# list(REMOVE_ITEM CLIENT_FILES "client/common/entry/entry_nacl.cpp")
# list(REMOVE_ITEM CLIENT_FILES "client/common/entry/entry_noop.cpp")
# list(REMOVE_ITEM CLIENT_FILES "client/common/entry/entry_sdl.cpp")
# list(REMOVE_ITEM CLIENT_FILES "client/common/entry/entry_windows.cpp")
list(APPEND CLIENT_FILES "client/common/entry/entry_osx.mm")

###
# Includes for current source executable
###
add_executable(server
    ${SERVER_FILES}
)

add_executable(client-test
    client-test/main.cpp
)

add_executable(client
    ${CLIENT_FILES}
    client/main.cpp
    # client/main.cpp
)

###
# Linking libraries
###
target_link_libraries(server
    RakNetLibStatic
    uv
    squirrel
    # sqstdlib
)

target_include_directories(server PUBLIC
    vendor/RakNet/Source
    # vendor/squirrel/include
    # vendor/squirrel/squirrel
    # vendor/squirrel/squirrel
)

target_link_libraries(client-test
    RakNetLibStatic
)

target_link_libraries(client
    RakNetLibStatic
    bgfx
    mesa
    ib-compress
    forsyth-too
    glslang
    glcpp
    glsl-optimizer
    fcpp
    ocornut-imgui
)


target_include_directories(client-test PUBLIC
    vendor/RakNet/Source
)

target_include_directories(client PUBLIC
    vendor/RakNet/Source
    client/common
)

# Xcode and Visual working directories
set_target_properties(server PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/server/")
create_target_launcher(server WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/server/")


# SOURCE_GROUP(shared REGULAR_EXPRESSION ".*/shared/.*" )

# if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
# add_custom_command(
#    TARGET server POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/server${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/server/"
# )

# elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

# endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

