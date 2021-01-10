import Reference from './reference.js';

export default class Obj
{
    constructor(name, level)
    {
        this.__name = name;
        this.__level = level || 0;
        this.__load = false;
    }

    get name(){ return this.__name; }

    set status(v){ this.__status = v; }

    render(gl, model, level)
    {
        console.log("render");
    }

    load(gl)
    {
        this.__load = true;
    }

    unload(gl)
    {
        this.__load = false;
    }

    build(name)
    {
        return new Reference(name, this);
    }
}
