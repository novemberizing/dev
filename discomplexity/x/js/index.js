import application from './x/graphics/application.js';
import ObjectFile from './homeworld2/object.file.js';
import Vertex from './x/graphics/vertex.js';
import Shader from './x/graphics/shader.js';
import Program from './x/graphics/program.js';
import Cube from './x/graphics/primitives/cube.js';
import Triangle from './x/graphics/primitives/triangle.js';
import Matrix from './x/graphics/matrix.js';

console.log(Matrix.scale(Matrix.identity(), [2, 2, 2, 0]));
console.log(Matrix.translate(Matrix.identity(), [2, 2, 2, 0]));
console.log(Matrix.rotate(Matrix.identity(), 45 * 0.01745329251994329576923690768489, [0, 1, 0, 0]));

application.init();

application.dispatch(Shader.load("/shader/simple.fragment.shader", "simple fragment", Shader.fragment, Shader.none, application));
application.dispatch(Shader.load("/shader/simple.vertex.shader", "simple vertex", Shader.vertex, Shader.none, application));
application.dispatch(Shader.load("/shader/standard.fragment.shader", "standard fragment", Shader.fragment, Shader.none, application));
application.dispatch(Shader.load("/shader/standard.vertex.shader", "standard vertex", Shader.vertex, Shader.none, application));

application.dispatch(Program.load("standard", ["standard fragment", "standard vertex"], ["mvp", "cameraPos", "lightColor", "lightPos", "ambientStrength"], ["vertexPosition", "vertexNormal"], application));
application.dispatch(Program.load("simple", ["simple fragment", "simple vertex"], [], ["vertexPosition"], application));

// application.dispatch(Triangle.load("triangle", "simple", application));
// application.dispatch(Cube.load("cube", "standard", application));
application.dispatch(ObjectFile.load("/sample.hod", "sample", application));

application.execute()
    .then(results => application.run())
    .catch(e => console.log(e));

console.log("hello world");
