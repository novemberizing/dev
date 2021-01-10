import Primitive from '../x/graphics/primitive.js';
import Indices from '../x/graphics/indices.js';

export default class Homeworld2Primitive extends Primitive
{
    constructor(name, level)
    {
        super(name, level, null);

        this.__material = null;
        this.__texture = null;
    }

    bind(application, name, value, model, level)
    {
        const gl = application.gl;

        if(!super.bind(application, name, value, model, level))
        {
            if(name == "textureSampler")
            {
                gl.activeTexture(gl.TEXTURE0);
                gl.bindTexture(gl.TEXTURE_2D, this.__texture.id);
                gl.uniform1i(value, 0);
            }
            else
            {
                throw new Error();
            }
        }
    }

    get name() { return this.__name; }
    get vertices() { return this.__vertices; }
    get buffer(){ return this.__buffer; }
    get program() { return this.__program; }
    get material(){ return this.__material; }
    get texture(){ return this.__texture; }

    set mode(v){ this.__vertices.mode = v; }
    set target(v){ this.__buffer.target = v; }
    set usage(v){ this.__buffer.usage = v; }
    set indices(v){ this.__indices = new Indices(v); }
    set status(v){ this.__status = v; }
    set program(v){ this.__program = v; }
    set material(v){ this.__material = v; }
    set texture(v){ this.__texture = v; }
}
