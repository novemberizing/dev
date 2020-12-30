cmake_minimum_required(VERSION 3.10)
project(xSpace)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

link_libraries(xCore
               homeworld2
               glut
               GLEW
               GL
               GLU)

set(sources xSpace/Application.cc
            xSpace/Object.cc
            xSpace/Objects/Unit.cc
            xSpace/Objects/Units/Ship.cc
            xSpace/Resource.cc
            xSpace/Scene.cc
            xSpace/Layer.cc
            xSpace/Game/Scene.cc
            xSpace/Game/Layer/World.cc
            xSpace/Demo/Scene.cc)

add_executable(xSpace ${sources} main.cc)
