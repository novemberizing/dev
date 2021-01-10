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

    render(application, model, level)
    {
        this.__singlemesh.render(application, model, level);

    }

    load(application)
    {
        this.__singlemesh.load(application);
        this.__load = true;
    }


    unload(application)
    {
        this.__singlemesh.unload(application);
        this.__load = false;
    }
}
