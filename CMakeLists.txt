cmake_minimum_required(VERSION 3.10)
project(SBXnative)


add_subdirectory(dependencies/GLFW)
add_executable(sbxn
    src/main.c
    src/sbx-args.c
)

add_library(test SHARED
    test/test_main.c
)

target_include_directories(test PUBLIC
    src/sbxn
)

target_link_libraries(sbxn PUBLIC glfw)