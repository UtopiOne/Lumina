cmake_minimum_required(VERSION 3.22)

add_subdirectory(vendor/GLFW) 

file(GLOB LUMINA_SOURCE
    src/*.cpp
    src/Lumina/*.cpp
    src/Lumina/ImGui/*.cpp
    src/Lumina/Renderer/*.cpp
    src/Platform/Linux/*.cpp
    src/Platform/OpenGL/*.cpp
)

file(GLOB SPDLOG_SOURCE
    vendor/spdlog/src/*.cpp
)

file(GLOB GLFW_SOURCE
    vendor/GLFW/src/*.c
    vendor/GLFW/src/*.h
)

file(GLOB GLAD_SOURCE 
    vendor/GLAD/src/*.c
)

file(GLOB IMGUI_SOURCE
    vendor/imgui/*.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC)
target_include_directories(imgui PUBLIC ${PROJECT_SOURCE_DIR}/Lumina/vendor/imgui)
target_sources(imgui PRIVATE ${IMGUI_SOURCE})
target_link_libraries(imgui PUBLIC GL glfw)

add_library(spdlog STATIC)
target_include_directories(spdlog PUBLIC vendor/spdlog/include)
target_sources(spdlog PRIVATE ${SPDLOG_SOURCE})

add_library(glad STATIC)
target_include_directories(glad PUBLIC vendor/GLAD/include)
target_sources(glad PRIVATE ${GLAD_SOURCE})

add_subdirectory(vendor/glm)

set(CMAKE_CXX_COMPILER clang++-18)
set(CMAKE_C_COMPILER clang-18)

add_library(lumina STATIC ${LUMINA_SOURCE})
target_link_libraries(lumina PRIVATE GL glfw spdlog glad imgui)
target_include_directories(lumina PUBLIC ${PROJECT_SOURCE_DIR}/Lumina/src)

target_precompile_headers(lumina
        PUBLIC
        ${LUMINA_DIR}/src/LuPCH.hpp
)
