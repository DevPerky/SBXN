cmake_minimum_required(VERSION 3.10)
project(SBXnative)


add_subdirectory(dependencies/GLFW)
add_executable(sbxn
    src/main.c
)

target_link_libraries(sbxn PUBLIC glfw)