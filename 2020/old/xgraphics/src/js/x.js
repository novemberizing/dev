import application from './x/graphics/application.js';
import ObjectFile from './homeworld2/object.file.js';
import Vertex from './x/graphics/vertex.js';
import Shader from './x/graphics/shader.js';
import Program from './x/graphics/program.js';
import Reference from './x/graphics/reference.js';
import Triangle from './x/graphics/primitives/triangle.js';
import Rectangle from './x/graphics/primitives/rectangle.js';
import SimpleLoadingBox from './x/graphics/primitives/simple.loading.box.js';
import Command from './x/core/command.js';

const __simple_fragment_code = `void main(){
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}`;

const __simple_vertex_code = `attribute vec4 vertexPosition;

void main(){
    gl_Position = vertexPosition;
}`;

application.shader(new Shader("simple fragment", Shader.fragment, Shader.none, __simple_fragment_code));
application.shader(new Shader("simple vertex", Shader.vertex, Shader.none, __simple_vertex_code));
application.program(new Program("simple", ["simple fragment", "simple vertex"], [], ["vertexPosition", "vertexNormal"]));

const __loading_simple_box_fragment_code = `precision mediump float;
uniform float progress;
uniform float idx;
varying vec2 vTexCoord;

void main() {
    if(vTexCoord.x < progress)
    {
        if(vTexCoord.x < idx)
        {
            gl_FragColor = vec4(1.0, 1.0, 1.0, 0.5);
        }
        else
        {
            gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
        }
    }
    else
    {
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}`;

const __loading_simple_box_vertex_code = `attribute vec4 vertexPosition;
precision mediump float;
uniform float progress;
uniform float idx;
varying vec2 vTexCoord;

void main(){
    gl_PointSize = 1.0;
    gl_Position = vertexPosition;

    vTexCoord = vertexPosition.xy;
}`;

application.shader(new Shader("loading simple box fragment", Shader.fragment, Shader.none, __loading_simple_box_fragment_code));
application.shader(new Shader("loading simple box vertex", Shader.vertex, Shader.none, __loading_simple_box_vertex_code));
application.program(new Program("loading simple box", ["loading simple box fragment", "loading simple box vertex"], ["progress", "idx"], ["vertexPosition", "vertexNormal"]));

application.object(new Triangle("triangle", 0, application.programs.get("simple")));
application.object(new Rectangle("rectangle", 0, application.programs.get("simple")));
application.object(new SimpleLoadingBox("loading", 0, application.programs.get("loading simple box"), { scale: [300/application.width, 20/application.height, 1.0, 0.0]}));

application.reference(new Reference("loading", application.objects.get("loading")));

application.loading([
    Shader.load("/xgraphics/shader/standard.fragment.shader", "standard fragment", Shader.fragment, Shader.none, application),
    Shader.load("/xgraphics/shader/standard.vertex.shader", "standard vertex", Shader.vertex, Shader.none, application),
    Shader.load("/xgraphics/res/homeworld2/shader/ship/fragment.shader", "homeworld2 ship fragment", Shader.fragment, Shader.none, application),
    Shader.load("/xgraphics/res/homeworld2/shader/ship/vertex.shader", "homeworld2 ship vertex", Shader.vertex, Shader.none, application),
    Program.load("standard", ["standard fragment", "standard vertex"], ["mvp", "cameraPos", "lightColor", "lightPos", "ambientStrength"], ["vertexPosition", "vertexNormal"], application),
    Program.load("ship", ["homeworld2 ship fragment", "homeworld2 ship vertex"], ["mvp", "cameraPos", "lightColor", "lightPos", "ambientStrength", "textureSampler"], ["vertexPosition", "vertexNormal", "vertexUV"], application),
    ObjectFile.load("/xgraphics/sample.hod", "sample", application)
]).then(o => {
    application.run(() => {
        application.reference(application.objects.get("sample").build("sample"));
        // application.reference(new Reference("sample", ));
        console.log("running");
    });
    console.log("success");
})
.catch(e => {
    console.log(e);
});

console.log("hello world");
