import Obj from './obj.js';
import Vertices from './vertices.js';
import Buffer from './buffer.js';
import Indices from './indices.js';
import Vertex from './vertex.js';
import Matrix from './matrix.js';

export default class Primitive extends Obj
{
    constructor(name, level, program)
    {
        super(name, level);

        this.__vertices = new Vertices();
        this.__buffer = new Buffer();
        this.__program = program;
        this.__indices = new Indices();
    }

    push(o)
    {
        this.__vertices.push(o);
    }

    load(application)
    {
        if(!this.__load)
        {
            if(!this.__buffer.size)
            {
                this.__vertices.serialize(this.__buffer);
            }

            this.__program.load(application);
            this.__indices.load(application);
            this.__vertices.load(application);
            this.__buffer.load(application);
            this.__load = true;
        }
    }

    unload(application)
    {
        if(this.__load)
        {
            this.__program.unload(application);
            this.__indices.unload(application);
            this.__vertices.unload(application);
            this.__buffer.unload(application);
            this.__load = false;
        }
    }

    bind(application, name, value, model, level)
    {
        const gl = application.gl;
        if(name === "mvp")
        {
            const camera = application.camera;
            const projection = application.projection;
            // console.log(model)
            let mvp = Matrix.multiply(Matrix.multiply(model, camera.matrix), projection.matrix);
            gl.uniformMatrix4fv(value, false, new Float32Array(mvp));
            return true;
        }
        else if(name === "cameraPos")
        {
            const camera = application.camera;
            gl.uniform4fv(value, camera.location);
            return true;
        }
        else if(name === "lightColor")
        {
            const light = application.light;
            gl.uniform4fv(value, light.color);
            return true;
        }
        else if(name === "lightPos")
        {
            const light = application.light;
            gl.uniform4fv(value, light.location);
            return true;
        }
        else if(name === "ambientStrength")
        {
            const light = application.light;
            gl.uniform1f(value, light.ambient);
            return true;
        }
        else
        {
            return false;
        }
    }

    render(application, model, level)
    {
        if(this.__level === level)
        {
            const gl = application.gl;

            gl.useProgram(this.__program.id);
            this.__program.uniforms.forEach((value, name) => {
                this.bind(application, name, value, model, level);
            });
            this.__program.attributes.forEach((value, name) => {
                if(value >= 0)
                {
                    gl.enableVertexAttribArray(value);
                    this.buffer.bind(application);
                    if(name === "vertexPosition")
                    {
                        gl.vertexAttribPointer(value, 4, gl.FLOAT, false, Vertex.stride, 0);
                    }
                    else if(name === "vertexNormal")
                    {
                        gl.vertexAttribPointer(value, 4, gl.FLOAT, false, Vertex.stride, 4 * 4);
                    }
                    else if(name === "vertexUV")
                    {
                        gl.vertexAttribPointer(value, 4, gl.FLOAT, false, Vertex.stride, 12 * 4);
                    }
                }
            });
            this.buffer.bind(application);
            if(this.__indices.size)
            {
                this.__indices.bind(application);
                // TODO: REMOVE TRIANGLES
                gl.drawElements(gl.TRIANGLES, this.__indices.size, gl.UNSIGNED_SHORT, 0);
            }
            else
            {
                // TODO: REMOVE TRIANGLES
                gl.drawArrays(gl.TRIANGLES, 0, this.__vertices.size);
            }
        }
    }

    get name() { return this.__name; }
    get vertices() { return this.__vertices; }
    get buffer(){ return this.__buffer; }
    get program() { return this.__program; }

    set mode(v){ this.__vertices.mode = v; }
    set target(v){ this.__buffer.target = v; }
    set usage(v){ this.__buffer.usage = v; }
    set indices(v){ this.__indices = new Indices(v); }
    set status(v){ this.__status = v; }
    set program(v){ this.__program = v; }
}
