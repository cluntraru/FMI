Cmake_minimum_required(VERSION 3.7)
project(tema)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-std=c++14")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# GLFW
add_subdirectory("lib/glfw")

include_directories("lib/glad/include" "lib/glm-0.9.9.6")

add_executable(tema "src/main.cpp" "src/tema2/tema2.cpp" "lib/glad/src/glad.c")

# GLFW Linking
target_link_libraries(tema glfw)

# YCM compile flags
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

