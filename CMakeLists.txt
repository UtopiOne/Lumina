cmake_minimum_required(VERSION 3.22)
project(Lumina)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

set(LUMINA_DIR ${PROJECT_SOURCE_DIR}/Lumina)
set(SANDBOX_DIR ${PROJECT_SOURCE_DIR}/Sandbox)

if(UNIX)
    add_compile_definitions(LU_PLATFORM_LINUX)
    add_compile_definitions(LU_BUILD_SO)
endif(UNIX)

if(WIN32)
    add_compile_definitions(LU_PLATFORM_WINDOWS)
    add_compile_definitions(LU_BUILD_DLL)
endif(WIN32)

add_compile_definitions(SPDLOG_COMPILED_LIB)

include_directories(
    ${LUMINA_DIR}/vendor/spdlog/include
    ${LUMINA_DIR}/vendor/GLFW/include
    ${LUMINA_DIR}/src
)

file(GLOB LUMINA_SOURCE 
    ${LUMINA_DIR}/src/*.cpp
    ${LUMINA_DIR}/src/Lumina/*.cpp
    ${LUMINA_DIR}/src/Platform/Linux/*.cpp
)

file(GLOB SPDLOG_SOURCE 
    ${LUMINA_DIR}/vendor/spdlog/src/*.cpp
)

file(GLOB GLFW_SOURCE
    ${LUMINA_DIR}/vendor/GLFW/src/*.c
)

add_library(lumina SHARED ${LUMINA_SOURCE})
add_library(spdlog STATIC ${SPDLOG_SOURCE})
# add_library(GLFW STATIC ${GLFW_SOURCE})
target_include_directories(lumina PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR})

target_precompile_headers(lumina
    PUBLIC
    ${LUMINA_DIR}/src/LuPCH.hpp
)

file(GLOB SANDBOX_SOURCE ${SANDBOX_DIR}/src/*.cpp)

add_executable(Sandbox ${SANDBOX_SOURCE})
target_link_libraries(Sandbox PRIVATE lumina GL glfw spdlog)