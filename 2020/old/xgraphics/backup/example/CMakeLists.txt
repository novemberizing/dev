cmake_minimum_required(VERSION 3.10)
project(example)

set(CMAKE_CXX_STANDARD 17)

link_libraries(xCore
               glut
               GLEW
               GL
               GLU)

add_executable(memory src/core/x.memory.cc)
add_executable(array src/core/x.array.cc)
add_executable(array.default.constructor src/core/x.array.default.constructor.cc)
add_executable(array.copy.constructor src/core/x.array.copy.constructor.cc)
add_executable(array.move.constructor src/core/x.array.move.constructor.cc)
add_executable(array.initializer.constructor src/core/x.array.initializer.constructor.cc)
add_executable(array.constructor.n.items src/core/x.array.constructor.n.items.cc)
add_executable(array.constructor.source src/core/x.array.constructor.source.cc)
add_executable(array.operator.assign.initializer src/core/x.array.operator.assign.initializer.cc)
add_executable(array.method.sub src/core/x.array.method.sub.cc)
add_executable(list src/core/x.list.cc)
add_executable(set src/core/x.set.cc)
add_executable(random src/core/x.random.cc)
add_executable(map src/core/x.map.cc)
add_executable(string src/core/x.string.cc)
add_executable(bytes src/core/x.bytes.cc)
add_executable(event src/core/x.event.cc)
add_executable(console src/core/x.console.cc)
add_executable(file src/core/x.file.cc)
add_executable(vector src/core/x.vector.cc)
add_executable(matrix src/core/x.matrix.cc)
add_executable(graphics.application src/core/x.graphics.application.cc)
add_executable(graphics.triangle src/core/x.graphics.triangle.cc)
add_executable(graphics.rectangle src/core/x.graphics.rectangle.cc)
add_executable(graphics.cube src/core/x.graphics.cube.cc)
add_executable(file.load src/core/x.file.load.cc)
add_executable(glClearColor src/opengl/glClearColor.cc)

add_executable(json src/core/x.json.cc)
