cmake_minimum_required(VERSION 3.22)
project(Lumina)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/out/bin)

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
add_compile_definitions(DEBUG)

include_directories(
    ${LUMINA_DIR}/vendor/spdlog/include
)

add_subdirectory(Lumina)
add_subdirectory(Sandbox)
