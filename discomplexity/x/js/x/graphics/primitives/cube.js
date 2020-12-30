import Primitive from '../primitive.js';
import Vertex from '../vertex.js';
import Vertices from '../vertices.js';
import Buffer from '../buffer.js';
import Matrix from '../matrix.js';
import Vector from '../vector.js';

export default class Cube extends Primitive
{
    static load(name, program, application)
    {
        return new Promise((resolve, reject) => {
            let o = new Cube(name, 0, 1, application.programs.get(program));
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
        this.__program = program;

        this.push(new Vertex([-1.0,-1.0,-1.0, 1.0], [-1.0,  0.0,  0.0, 0.0]));
        this.push(new Vertex([-1.0,-1.0, 1.0, 1.0], [-1.0,  0.0,  0.0, 0.0]));
        this.push(new Vertex([-1.0, 1.0, 1.0, 1.0], [-1.0,  0.0,  0.0, 0.0]));

        this.push(new Vertex([ 1.0, 1.0,-1.0, 1.0], [ 0.0,  0.0, -1.0, 0.0]));
        this.push(new Vertex([-1.0,-1.0,-1.0, 1.0], [ 0.0,  0.0, -1.0, 0.0]));
        this.push(new Vertex([-1.0, 1.0,-1.0, 1.0], [ 0.0,  0.0, -1.0, 0.0]));

        this.push(new Vertex([ 1.0,-1.0, 1.0, 1.0], [ 0.0, -1.0,  0.0, 0.0]));
        this.push(new Vertex([-1.0,-1.0,-1.0, 1.0], [ 0.0, -1.0,  0.0, 0.0]));
        this.push(new Vertex([ 1.0,-1.0,-1.0, 1.0], [ 0.0, -1.0,  0.0, 0.0]));

        this.push(new Vertex([ 1.0, 1.0,-1.0, 1.0], [ 0.0,  0.0, -1.0, 0.0]));
        this.push(new Vertex([ 1.0,-1.0,-1.0, 1.0], [ 0.0,  0.0, -1.0, 0.0]));
        this.push(new Vertex([-1.0,-1.0,-1.0, 1.0], [ 0.0,  0.0, -1.0, 0.0]));

        this.push(new Vertex([-1.0,-1.0,-1.0, 1.0], [-1.0,  0.0,  0.0, 0.0]));
        this.push(new Vertex([-1.0, 1.0, 1.0, 1.0], [-1.0,  0.0,  0.0, 0.0]));
        this.push(new Vertex([-1.0, 1.0,-1.0, 1.0], [-1.0,  0.0,  0.0, 0.0]));

        this.push(new Vertex([ 1.0,-1.0, 1.0, 1.0], [ 0.0, -1.0,  0.0, 0.0]));
        this.push(new Vertex([-1.0,-1.0, 1.0, 1.0], [ 0.0, -1.0,  0.0, 0.0]));
        this.push(new Vertex([-1.0,-1.0,-1.0, 1.0], [ 0.0, -1.0,  0.0, 0.0]));

        this.push(new Vertex([-1.0, 1.0, 1.0, 1.0], [ 0.0,  0.0,  1.0, 0.0]));
        this.push(new Vertex([-1.0,-1.0, 1.0, 1.0], [ 0.0,  0.0,  1.0, 0.0]));
        this.push(new Vertex([ 1.0,-1.0, 1.0, 1.0], [ 0.0,  0.0,  1.0, 0.0]));

        this.push(new Vertex([ 1.0, 1.0, 1.0, 1.0], [ 1.0,  0.0,  0.0, 0.0]));
        this.push(new Vertex([ 1.0,-1.0,-1.0, 1.0], [ 1.0,  0.0,  0.0, 0.0]));
        this.push(new Vertex([ 1.0, 1.0,-1.0, 1.0], [ 1.0,  0.0,  0.0, 0.0]));

        this.push(new Vertex([ 1.0,-1.0,-1.0, 1.0], [ 1.0,  0.0,  0.0, 0.0]));
        this.push(new Vertex([ 1.0, 1.0, 1.0, 1.0], [ 1.0,  0.0,  0.0, 0.0]));
        this.push(new Vertex([ 1.0,-1.0, 1.0, 1.0], [ 1.0,  0.0,  0.0, 0.0]));

        this.push(new Vertex([ 1.0, 1.0, 1.0, 1.0], [ 0.0,  1.0,  0.0, 0.0]));
        this.push(new Vertex([ 1.0, 1.0,-1.0, 1.0], [ 0.0,  1.0,  0.0, 0.0]));
        this.push(new Vertex([-1.0, 1.0,-1.0, 1.0], [ 0.0,  1.0,  0.0, 0.0]));

        this.push(new Vertex([ 1.0, 1.0, 1.0, 1.0], [ 0.0,  1.0,  0.0, 0.0]));
        this.push(new Vertex([-1.0, 1.0,-1.0, 1.0], [ 0.0,  1.0,  0.0, 0.0]));
        this.push(new Vertex([-1.0, 1.0, 1.0, 1.0], [ 0.0,  1.0,  0.0, 0.0]));

        this.push(new Vertex([ 1.0, 1.0, 1.0, 1.0], [ 0.0,  0.0,  1.0, 0.0]));
        this.push(new Vertex([-1.0, 1.0, 1.0, 1.0], [ 0.0,  0.0,  1.0, 0.0]));
        this.push(new Vertex([ 1.0,-1.0, 1.0, 1.0], [ 0.0,  0.0,  1.0, 0.0]));
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
        gl.useProgram(this.__program.id);
        this.__program.uniforms.forEach((value, name) => {
            if(name === "mvp")
            {
                let fovy = 45 * 0.01745329251994329576923690768489;
                let aspect = gl.canvas.width / gl.canvas.height;
                let near = 0.1;
                let far = 1000;
                let projection = Matrix.perspective(fovy, aspect, near, far);
                let view = Matrix.lookat([4, 3, 3, 0], [0, 0, 0, 0], [0, 1, 0, 0]);
                let model = Matrix.identity();
                let mvp = Matrix.multiply(Matrix.multiply(model,view), projection);
                gl.uniformMatrix4fv(value, false, new Float32Array(mvp));
            }
            else if(name === "cameraPos")
            {
                gl.uniform4fv(value, [4, 3, 3, 0]);
            }
            else if(name === "lightColor")
            {
                gl.uniform4fv(value, [1, 1, 1, 1]);
            }
            else if(name === "lightPos")
            {
                gl.uniform4fv(value, [18, 4, 3, 1]);
            }
            else if(name === "ambientStrength")
            {
                gl.uniform1f(value, 0.8);
            }
            else
            {
                throw new Error();
            }
        });
        this.__program.attributes.forEach((value, name) => {
            if(value >= 0)
            {
                gl.enableVertexAttribArray(value);
                this.buffer.bind(gl);
                if(name === "vertexPosition")
                {
                    gl.vertexAttribPointer(value, 4, gl.FLOAT, false, Vertex.stride, 0);
                }
                else if(name === "vertexNormal")
                {
                    gl.vertexAttribPointer(value, 4, gl.FLOAT, false, Vertex.stride, 4 * 4);
                }
            }
        });
        gl.drawArrays(gl.TRIANGLES, 0, this.__vertices.size);
    }
}
