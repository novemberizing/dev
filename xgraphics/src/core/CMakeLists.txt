cmake_minimum_required(VERSION 3.10)
project(core)

set(CMAKE_CXX_STANDARD 17)

set(sources x/io/event/generator/epoll.cc
            x/json/value.cc
            x/json/object.cc
            x/json/array.cc
            x/json/string.cc
            x/json/number.cc
            x/reality/vector.cc
            x/reality/matrix.cc
            x/reality/color.cc
            x/reality/coordinate.cc
            x/reality/light.cc
            x/reality/camera.cc
            x/reality/projection.cc
            x/reality/world.cc
            x/reality/object.cc
            x/reality/reference.cc
            x/graphics/shader.cc
            x/graphics/program.cc
            x/graphics/vertex.cc
            x/graphics/vertices.cc
            x/graphics/buffer.cc
            x/graphics/object.cc
            x/graphics/reference.cc
            x/graphics/primitive.cc
            x/graphics/layer.cc
            x/graphics/surface.cc
            x/graphics/image.cc
            x/graphics/mipmap.cc
            x/graphics/texture.cc
            x/graphics/application.cc
            x/graphics/environment.cc
            x/graphics/primitives/rectangle.cc
            x/graphics/primitives/triangle.cc
            x/graphics/primitives/cube.cc
            x/graphics/primitives/image.cc
            x/graphics/objects/base.cc
            x/graphics/objects/root.cc
            x/graphics/objects/joint.cc
            x/graphics/objects/single.cc
            x/graphics/objects/multi.cc
            x/graphics/images/dds.cc
            x/graphics/images/bitmap.cc
            x/graphics/opengl.cc
            x/graphics/opengl/application.cc

            x/graphics/opengl/shaders/coordinate.system.cc
            x/graphics/opengl/shaders/simple.cc
            x/graphics/opengl/shaders/standard.cc
            x/graphics/opengl/shaders/image.cc
            x/graphics/opengl/programs/coordinate.system.cc
            x/graphics/opengl/programs/simple.cc
            x/graphics/opengl/programs/standard.cc
            x/graphics/opengl/programs/image.cc
            x/physics/force.cc
            x/physics/friction.cc
            x/physics/direction.cc
            x/physics/object.cc
            x/physics/reference.cc)

add_library(xCore ${sources})
