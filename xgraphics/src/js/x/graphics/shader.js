import Command from '../core/command.js';

export default class Shader
{
    static get weight(){ return 1; }

    static get none() { return 0; }
    static get vertex() { return 1; }
    static get fragment() { return 2; }
    static get compute() { return 3; }
    static get geometry() { return 4; }
    static get tessellation() { return 5; }
    static get control() { return 1; }
    static get evaluation() { return 2; }

    static load(path, name, category, type, application)
    {
        return new Command((resolve, reject) => {
            let w = new Worker('/xgraphics/js/homeworld2/shader.load.js');
            w.postMessage({path});
            w.onmessage = (event) => {
                if(event.data.finish)
                {
                    if(!event.data.error)
                    {
                        let shader = application.shader(new Shader(name, category, type, event.data.code));
                        application.__current += Shader.weight;
                        resolve(shader);
                    }
                    else
                    {
                        reject(e);
                    }
                    w.terminate();
                    w = null;
                }
            };
        }, Shader.weight);
    }

    static type(gl, category, type)
    {
        switch(category)
        {
            case Shader.vertex:             return gl.VERTEX_SHADER;
            case Shader.fragment:           return gl.FRAGMENT_SHADER;
            case Shader.compute:            throw new Error();
            case Shader.geometry:           throw new Error();
            case Shader.tessellation:       throw new Error();
            default:                        throw new Error();
        }
    }

    constructor(name, category, type, code) {
        this.__name = name;
        this.__category = category;
        this.__type = type || Shader.none;
        this.__id = 0;
        this.__code = code;
    }

    get name(){ return this.__name; }
    get id(){ return this.__id; }

    load(application)
    {
        const gl = application.gl;

        if(!this.__id)
        {
            this.__id = gl.createShader(Shader.type(gl, this.__category, this.__type));
            gl.shaderSource(this.__id, this.__code);
            gl.compileShader(this.__id);
            if(!gl.getShaderParameter(this.__id, gl.COMPILE_STATUS))
            {
                console.log(gl.getShaderInfoLog(this.__id));
                throw new Error();
            }
            return this;
        }
        else
        {
            throw new Error();
        }
    }

    unload(application)
    {
        const gl = application.gl;

        if(this.__id)
        {
            gl.deleteShader(this.__id);
            this.__id = 0;
        }
    }
}
