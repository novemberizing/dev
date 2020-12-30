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
            Homeworld2/Graphics/Basicmesh.cc
            Homeworld2/Graphics/Description.cc
            Homeworld2/Graphics/Box.cc
            Homeworld2/Graphics/Sphere.cc
            Homeworld2/Graphics/Triangle.cc
            Homeworld2/Graphics/Subdivision.cc
            Homeworld2/Graphics/Boundary.cc
            Homeworld2/Graphics/Collision.cc
            Homeworld2/Graphics/Engineburn.cc
            Homeworld2/Graphics/Engineshape.cc
            Homeworld2/Graphics/Goblinmesh.cc
            Homeworld2/Graphics/Singlemesh.cc
            Homeworld2/Graphics/Information.cc
            Homeworld2/Graphics/Joint.cc
            Homeworld2/Graphics/Keyframe.cc
            Homeworld2/Graphics/Marker.cc
            Homeworld2/Graphics/Material.cc
            Homeworld2/Graphics/Multimesh.cc
            Homeworld2/Graphics/Navlight.cc
            Homeworld2/Graphics/Reference.cc
            Homeworld2/Graphics/Texture.cc
            Homeworld2/Graphics/Primitive.cc
            Homeworld2/Graphics/Object.cc
            Homeworld2/Physics/Reference.cc
            Homeworld2/Physics/ReferenceFile.cc
            Homeworld2/Resource.cc
            Homeworld2/Reference.cc
            Homeworld2/Unit.cc
            Homeworld2/Unit/Camera.cc
            Homeworld2/Units/Ship.cc)



add_executable(homeworld2 ${sources} Homeworld2/main.cc)
