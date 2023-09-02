cmake_minimum_required(VERSION 3.22)
project(Lumina)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER clang++)

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
    ${LUMINA_DIR}/src
)

file(GLOB LUMINA_SOURCE 
    ${LUMINA_DIR}/src/*.cpp
    ${LUMINA_DIR}/src/Lumina/*.cpp
)

file(GLOB SPDLOG_SOURCE ${LUMINA_DIR}/vendor/spdlog/src/*.cpp)

add_library(lumina SHARED ${LUMINA_SOURCE})
add_library(spdlog ${SPDLOG_SOURCE})
target_include_directories(lumina PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR})

file(GLOB SANDBOX_SOURCE ${SANDBOX_DIR}/src/*.cpp)

add_executable(Sandbox ${SANDBOX_SOURCE})
target_link_libraries(Sandbox PRIVATE lumina spdlog)