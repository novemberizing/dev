
export default class Program
{
    static load(name, shaders, uniforms, attributes, application)
    {
        return new Promise((resolve, reject) => {
            let o = new Program(name, shaders, uniforms, attributes);
            if(!application.programs.get(name))
            {
                application.programs.set(name, o);
                resolve(o);
            }
            else
            {
                reject(new Error());
            }
        });
    }

    constructor(name, shaders, uniforms, attributes)
    {
        this.__name = name;
        this.__id = 0;
        this.__shaders = shaders || new Array();
        this.__uniforms = uniforms ? new Map(uniforms.map(o => [o, null])) : new Map();
        this.__attributes = attributes ? new Map(attributes.map(o => [o, null])) : new Map();
    }

    create(gl, application)
    {
        if(!this.__id)
        {
            this.__id = gl.createProgram();
            this.__shaders.forEach(name => {
                let o = application.shaders.get(name);
                o.attach(gl, this.__id);
            });
            gl.linkProgram(this.__id);
            if(gl.getProgramParameter(this.__id, gl.LINK_STATUS))
            {
                this.__shaders.forEach(name => {
                    let o = application.shaders.get(name);
                    o.detach(gl, this.__id);
                });
                return this;
            }
            else
            {
                throw new Error();
            }
        }
        else
        {
            throw new Error();
        }
    }

    init(gl)
    {
        this.__attributes.forEach((value, name) => this.__attributes.set(name, gl.getAttribLocation(this.__id, name)));
        this.__uniforms.forEach((value, name) => this.__uniforms.set(name, gl.getUniformLocation(this.__id, name)));
    }

    get id(){ return this.__id; }
    get attributes(){ return this.__attributes; }
    get uniforms(){ return this.__uniforms; }
}
