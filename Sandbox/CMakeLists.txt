cmake_minimum_required(VERSION  3.22)

file(GLOB SANDBOX_SOURCE ${SANDBOX_DIR}/src/*.cpp)

add_executable(Sandbox ${SANDBOX_SOURCE})
target_link_libraries(Sandbox PRIVATE lumina imgui)
