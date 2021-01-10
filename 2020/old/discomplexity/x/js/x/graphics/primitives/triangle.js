import Primitive from '../primitive.js';
import Vertex from '../vertex.js';
import Vertices from '../vertices.js';
import Buffer from '../buffer.js';

export default class Triangle extends Primitive
{
    static load(name, program, application)
    {
        return new Promise((resolve, reject) => {
            let o = new Triangle(name, 0, 1, application.programs.get(program));
            o.serialize();
            application.objects.add(o);
            resolve(o);
        });
    }

    constructor(name, level, status, program)
    {
        super(name, level, status);

        this.mode = Vertices.triangle;
        this.target = Buffer.array;
        this.usage = [Buffer.statical, Buffer.draw];
        this.program = program;

        this.push(new Vertex([ 0.0, 0.5, 0.0, 1.0], [ 0.0,  0.0,  1.0, 0.0]));
        this.push(new Vertex([-0.5,-0.5, 0.0, 1.0], [ 0.0,  0.0,  1.0, 0.0]));
        this.push(new Vertex([ 0.5,-0.5, 0.0, 1.0], [ 0.0,  0.0,  1.0, 0.0]));


    }

    get name() { return this.__name; }
    get program() { return this.__program; }
    get buffer(){ return this.__buffer; }

    set mode(v){ this.__vertices.mode = v; }
    set target(v){ this.__buffer.target = v; }
    set usage(v){ this.__buffer.usage = v; }
    set program(o){ this.__program = o; }

    render(gl)
    {
        console.log(this.program.id);
        console.log("render");
        gl.useProgram(this.program.id);
        this.program.uniforms.forEach((value, name) => {
            // ["mvp", "cameraPos", "lightColor", "lightPos", "ambientStrength"]
            // console.log(name);
        });
        this.program.attributes.forEach((value, name) => {
            console.log(name);
            gl.enableVertexAttribArray(value);
            this.buffer.bind(gl);
            if(name === "vertexPosition")
            {
                gl.vertexAttribPointer(value, 4, gl.FLOAT, false, Vertex.stride, 0);
                console.log("position");
            }
            else if(name === "vertexNormal")
            {
                gl.vertexAttribPointer(value, 4, gl.FLOAT, false, Vertex.stride, 4 * 4);
                console.log("normal");
            }
        });
        gl.drawArrays(gl.TRIANGLES, 0, this.__vertices.size);
    }
}
