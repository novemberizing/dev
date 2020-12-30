import Command from '../core/command.js';

export default class Program
{
    static get weight(){ return 1; }
    static load(name, shaders, uniforms, attributes, application)
    {
        return new Command((resolve, reject) => {
            let o = new Program(name, shaders, uniforms, attributes);
            if(!application.programs.get(name))
            {
                application.programs.set(name, o);
                application.__current += Program.weight;
                resolve(o);
            }
            else
            {
                reject(new Error());
            }
        }, Program.weight);
    }

    constructor(name, shaders, uniforms, attributes)
    {
        this.__name = name;
        this.__id = 0;
        this.__shaders = shaders || new Array();
        this.__uniforms = uniforms ? new Map(uniforms.map(o => [o, null])) : new Map();
        this.__attributes = attributes ? new Map(attributes.map(o => [o, null])) : new Map();
    }

    load(application)
    {
        const gl = application.gl;

        if(!this.__id)
        {
            this.__id = gl.createProgram();
            this.__shaders.forEach(name => {
                let o = application.shaders.get(name);
                o.load(application);
                gl.attachShader(this.__id, o.id);
            });
            gl.linkProgram(this.__id);
            if(gl.getProgramParameter(this.__id, gl.LINK_STATUS))
            {
                this.__shaders.forEach(name => {
                    let o = application.shaders.get(name);
                    o.unload(application);
                });
                this.__attributes.forEach((value, name) => this.__attributes.set(name, gl.getAttribLocation(this.__id, name)));
                this.__uniforms.forEach((value, name) => this.__uniforms.set(name, gl.getUniformLocation(this.__id, name)));
                return this;
            }
            else
            {
                throw new Error();
            }
        }
    }

    get name(){ return this.__name; }
    get id(){ return this.__id; }
    get attributes(){ return this.__attributes; }
    get uniforms(){ return this.__uniforms; }
}
