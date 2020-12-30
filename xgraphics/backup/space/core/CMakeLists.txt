cmake_minimum_required(VERSION 3.10)
project(xSpace)

set(CMAKE_CXX_STANDARD 17)

include_directories(.
                    )

link_libraries(xCore
               homeworld2
               glut
               GLEW
               GL
               GLU)

set(sources x/Space/Application.cc
            x/Space/Resource.cc
            x/Space/Object.cc
            x/Space/Object/Camera.cc
            x/Space/Senario.cc
            x/Space/Senarios/Unit.cc
            x/Space/Layers/Game.cc
            x/Space/Layers/Front.cc
            x/Space/Objects/Radar.cc
            x/Space/Objects/Radars/Unit.cc
            x/Space/Scene.cc
            x/Space/Scenes/Intro.cc
            x/Space/Scenes/Lobby.cc
            x/Space/Scenes/Game.cc
            x/Space/Game/Me.cc)

add_executable(xSpace ${sources} main.cc)
