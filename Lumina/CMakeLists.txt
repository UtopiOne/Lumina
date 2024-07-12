cmake_minimum_required(VERSION 3.22)

file(GLOB LUMINA_SOURCE 
    src/*.cpp
    src/Lumina/*.cpp
    src/Lumina/ImGui/*.cpp
    src/Platform/Linux/*.cpp
    src/Platform/OpenGL/*.cpp
)

file(GLOB SPDLOG_SOURCE 
    vendor/spdlog/src/*.cpp
)

file(GLOB GLFW_SOURCE
    vendor/GLFW/src/*.c
)

file(GLOB GLAD_SOURCE 
    vendor/GLAD/src/*.c
)

file(GLOB IMGUI_SOURCE
    vendor/imgui/*.cpp
    vendor/imgui/backends/imgui_impl_glfw.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCE})
add_library(lumina SHARED ${LUMINA_SOURCE}
        src/Lumina/KeyCodes.hpp)
add_library(spdlog STATIC ${SPDLOG_SOURCE})
# add_library(GLFW STATIC ${GLFW_SOURCE})
add_library(glad STATIC ${GLAD_SOURCE}
        src/Lumina/MouseButtonCodes.hpp)
target_include_directories(lumina PUBLIC ${PROJECT_BINARY_DIR} ${PROJECT_SOURCE_DIR})

target_precompile_headers(lumina
    PUBLIC
    ${LUMINA_DIR}/src/LuPCH.hpp
)