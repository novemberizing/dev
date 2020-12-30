cmake_minimum_required(VERSION 3.10)
project(xEvent)

set(CMAKE_CXX_STANDARD 17)

include_directories(src
                    ../x/src)

link_libraries(xGraphics)

#link_libraries(GL
#               GLU
#               GLEW
#               glut
#               xGraphics)
#
#set(sources src/Homeworld2/ObjectFile.cc
#            src/Homeworld2/Object.cc
#            src/Homeworld2/Material.cc
#            src/Homeworld2/Texture.cc
#            src/Homeworld2/Multimesh.cc
#            src/Homeworld2/Singlemesh.cc
#            src/Homeworld2/Goblinmesh.cc
#            src/Homeworld2/Engineshape.cc
#            src/Homeworld2/Primitive.cc
#            src/Homeworld2/Joint.cc)
#
#set(headers src/Homeworld2/ObjectFile.hh
#            src/Homeworld2/Object.hh
#            src/Homeworld2/Material.hh
#            src/Homeworld2/Texture.hh
#            src/Homeworld2/Multimesh.hh
#            src/Homeworld2/Singlemesh.hh
#            src/Homeworld2/Primitive.hh)

add_executable(vector src/vector.cc)
add_executable(application src/application.cc)
add_executable(cube src/cube.cc)
