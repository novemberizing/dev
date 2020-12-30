cmake_minimum_required(VERSION 3.10)
project(homeworld2)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

link_libraries(xCore
               glut
               GLEW
               GL
               GLU)

set(sources Homeworld2/Graphics/ReferenceFile.cc
            Homeworld2/Graphics/Reference.cc
            Homeworld2/Graphics/Material.cc
            Homeworld2/Graphics/Texture.cc
            Homeworld2/Graphics/Multimesh.cc
            Homeworld2/Graphics/Singlemesh.cc
            Homeworld2/Graphics/Primitive.cc
            Homeworld2/Graphics/Goblinmesh.cc
            Homeworld2/Graphics/Joint.cc
            Homeworld2/Graphics/Engineshape.cc
            Homeworld2/Graphics/Engineburn.cc
            Homeworld2/Graphics/Navlight.cc
            Homeworld2/Graphics/Objects/Joint.cc
            Homeworld2/Graphics/Objects/Lod.cc
            Homeworld2/Graphics/Objects/Multi.cc
            Homeworld2/Graphics/Objects/Root.cc
            Homeworld2/Graphics/Objects/Base.cc
            Homeworld2/Graphics/Objects/Single.cc
            Homeworld2/Resource.cc
            Homeworld2/Senario.cc
            Homeworld2/Senarios/Unit.cc)

add_library(homeworld2 ${sources})

# add_executable(homeworld2sample main.cc)
# target_link_libraries(homeworld2sample homeworld2)
