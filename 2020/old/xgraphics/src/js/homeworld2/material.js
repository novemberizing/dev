
export default class Material
{
    constructor(name, shader, diffuse, glow)
    {
        this.__name = name;
        this.__shader = shader;
        this.__diffuse = diffuse;
        this.__glow = glow;
    }
    
    get shader(){ return this.__shader; }
    get diffuse(){ return this.__diffuse; }
}
