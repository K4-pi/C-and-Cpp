cmake_minimum_required(VERSION 3.10.0)
project(OpenGL-learn VERSION 0.1.0 LANGUAGES C CXX)

add_executable(OpenGL-learn 
    main.cpp
    src/glad.c
)

target_include_directories(OpenGL-learn PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(OpenGL-learn PRIVATE
    glfw 
    GL 
    X11 
    pthread 
    Xrandr 
    Xi 
    dl
)

include(CTest)
enable_testing()

