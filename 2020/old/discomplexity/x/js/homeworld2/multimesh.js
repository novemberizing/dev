import Obj from '../x/graphics/obj.js';

export default class Multimesh extends Obj
{
    constructor(name, parent, status)
    {
        super(name, 0, status);
        this.__parent = parent;
        this.__singlemesh = new Map();
    }

    get singlemesh(){ return this.__singlemesh; }
    get status(){ return this.__status; }
    get name(){ return this.__name; }
    get parent(){ return this.__parent; }

    set status(v)
    {
        this.__status = v;
        this.__singlemesh.forEach(singlemesh => { singlemesh.status = v; });
    }

    render(gl, model, level)
    {
        this.__singlemesh.forEach((singlemesh, index) => {
            if(level === index)
            {
                singlemesh.render(gl, model, level);
            }
        });
    }

    init(gl)
    {
        this.__singlemesh.forEach(singlemesh => {
            singlemesh.init(gl);
        });
    }
}
