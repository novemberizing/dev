import Obj from '../x/graphics/obj.js';

export default class Goblinmesh extends Obj
{
    constructor(name, parent, status)
    {
        super(name, 0, status);

        this.__singlemesh = null;
        this.__parent = parent;
    }

    get singlemesh(){ return this.__singlemesh; }
    get status(){ return this.__status; }
    get name(){ return this.__name; }
    get parent(){ return this.__parent; }

    set singlemesh(o){ this.__singlemesh = o; }

    set status(v)
    {
        this.__status = v;
        this.__singlemesh.status = v;
    }

    render(gl, model, level)
    {
        this.__singlemesh.render(gl, model, level);

    }

    init(gl)
    {
        this.__singlemesh.init(gl);
    }
}
