cmake_minimum_required(VERSION 3.10)
project(xGraphics)

set(CMAKE_CXX_STANDARD 17)

include_directories(./src)

link_libraries(GL
               GLU
               GLEW
               glut)

set(sources src/x/core/io.cc
            src/x/core/string.cc
            src/x/graphics/opengl/shaders/standard.cc
            src/x/graphics/opengl/shaders/simple.cc
            src/x/graphics/opengl/shaders/coordinate.system.cc
            src/x/graphics/opengl/programs/standard.cc
            src/x/graphics/opengl/programs/simple.cc
            src/x/graphics/opengl/programs/coordinate.system.cc
            src/x/graphics/opengl/application.cc
            src/x/graphics/objects/cube.cc
            src/x/graphics/vector.cc
            src/x/graphics/application.cc
            src/x/graphics/buffer.cc
            src/x/graphics/matrix.cc
            src/x/graphics/primitive.cc
            src/x/graphics/complex.cc
            src/x/graphics/program.cc
            src/x/graphics/shader.cc
            src/x/graphics/vertices.cc
            src/x/graphics/object.cc
            src/x/graphics/reference.cc
            src/x/graphics/camera.cc
            src/x/graphics/light.cc
            src/x/graphics/matrix.cc
            src/x/graphics/color.cc
            src/x/graphics/surface.cc
            src/x/graphics/vertex.cc
            src/x/graphics/coordinate.cc
            src/x/graphics/util.cc
            src/x/graphics/projection.cc
            src/x/io/event/generator/epoll.cc)

set(headers src/x/core/io.hh
            src/x/core/string.hh
            src/x/array.hh
            src/x/bytes.hh
            src/x/collection.hh
            src/x/console.hh
            src/x/container.hh
            src/x/endian.hh
            src/x/exception.hh
            src/x/file.hh
            src/x/function.hh
            src/x/initializer.hh
            src/x/list.hh
            src/x/map.hh
            src/x/math.hh
            src/x/matrix.hh
            src/x/memory.hh
            src/x/node.hh
            src/x/page.hh
            src/x/pair.hh
            src/x/parameter.hh
            src/x/reference.hh
            src/x/set.hh
            src/x/single.hh
            src/x/space.hh
            src/x/stream.hh
            src/x/string.hh
            src/x/type.hh
            src/x/variable.hh
            src/x/vector.hh
            src/x/primitives/uinteger32.hh
            src/x/math/exponential.hh
            src/x/math/hyperbolic.hh
            src/x/math/other.hh
            src/x/math/rounding.hh
            src/x/math/trigometric.hh
            src/x/input/stream.hh
            src/x/graphics/application.hh
            src/x/graphics/buffer.hh
            src/x/graphics/camera.hh
            src/x/graphics/complex.hh
            src/x/graphics/coordinate.hh
            src/x/graphics/debug.hh
            src/x/graphics/light.hh
            src/x/graphics/matrix.hh
            src/x/graphics/object.hh
            src/x/graphics/opengl.hh
            src/x/graphics/position.hh
            src/x/graphics/primitive.hh
            src/x/graphics/program.hh
            src/x/graphics/shader.hh
            src/x/graphics/type.hh
            src/x/graphics/vector.hh
            src/x/graphics/vertex.hh
            src/x/graphics/vertices.hh
            src/x/graphics/object.hh
            src/x/graphics/opengl/application.hh
            src/x/graphics/opengl/shaders/standard.hh
            src/x/graphics/objects/triangle.hh
            src/x/graphics/objects/cube.hh
            src/x/io/event/generator/epoll.hh)

add_library(xGraphics ${sources})

# add_executable(xGraphicsSample ${sources} src/x/graphics/main.cc)
