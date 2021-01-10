cmake_minimum_required(VERSION 3.10)
project(xSpace)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

link_libraries(xCore
               glut
               GLEW
               GL
               GLU)


add_executable(triangle triangle.cc)
