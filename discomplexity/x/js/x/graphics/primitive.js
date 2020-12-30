import Vertices from './vertices.js';
import Buffer from './buffer.js';
import Obj from './obj.js';
import Matrix from './matrix.js';
import Vertex from './vertex.js';
import Indices from './indices.js';

export default class Primitive extends Obj
{
    constructor(name, level, status)
    {
        super(name, level, status);
        this.__vertices = new Vertices();
        this.__buffer = new Buffer();
        this.__program = null;
        this.__indices = null;
    }

    push(o)
    {
        this.__vertices.push(o);
    }

    serialize()
    {
        if(!this.__buffer.size)
        {
            this.__vertices.serialize(this.__buffer);
        }
    }

    init(gl)
    {
        this.__program.init(gl);
        if(this.__indices)
        {
            this.__indices.init(gl);
        }
        this.__buffer.init(gl);
    }

    render(gl, model, level){
        if(this.__status)
        {
            if(this.__level === level)
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
                        let view = Matrix.lookat([0, 0, 90, 1], [0, 0, 0, 0], [0, 1, 0, 0]);
                        // let model = Matrix.identity();
                        let mvp = Matrix.multiply(Matrix.multiply(model, view), projection);
                        gl.uniformMatrix4fv(value, false, new Float32Array(mvp));
                    }
                    else if(name === "cameraPos")
                    {
                        gl.uniform4fv(value, [0, 0, 90, 0]);
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
                // console.log(this.__vertices.size);
                this.buffer.bind(gl);
                if(this.__indices)
                {
                    this.__indices.bind(gl);
                    gl.drawElements(gl.TRIANGLES, this.__indices.size, gl.UNSIGNED_SHORT, 0);
                }
                else
                {
                    gl.drawArrays(gl.TRIANGLES, 0, this.__vertices.size);
                }
            }
        }
    }

    get name() { return this.__name; }
    get vertices() { return this.__vertices; }
    get buffer(){ return this.__buffer; }

    set mode(v){ this.__vertices.mode = v; }
    set target(v){ this.__buffer.target = v; }
    set usage(v){ this.__buffer.usage = v; }
    set indices(v){ this.__indices = new Indices(v); }
    set status(v){ this.__status = v; }
    set program(v){ this.__program = v; }
}
