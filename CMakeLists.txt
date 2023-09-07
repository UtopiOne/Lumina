cmake_minimum_required(VERSION 3.22)
project(Lumina)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

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
add_compile_definitions(GLFW_INCLUDE_NONE)
add_compile_definitions(DEBUG)

include_directories(
    ${LUMINA_DIR}/vendor/spdlog/include
    ${LUMINA_DIR}/vendor/GLFW/include
    ${LUMINA_DIR}/vendor/GLAD/include
    ${LUMINA_DIR}/vendor/imgui
    ${LUMINA_DIR}/src
)

add_subdirectory(Lumina)
add_subdirectory(Sandbox)