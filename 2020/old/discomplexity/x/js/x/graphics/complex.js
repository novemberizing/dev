import Obj from './obj.js';

export default class Complex extends Obj
{
    constructor(name, level, status)
    {
        super(name, level, status);

        this.__children = new Array();
    }

    add(o)
    {
        this.__children.push(o);
    }

    set status(v)
    {
        this.__status = v;
        this.__children.forEach(o => { o.status = v; });
    }

    render(gl, model, level)
    {
        this.__children.forEach(o => {
            o.render(gl, model, level);
        });
    }

    init(gl) {
        this.__children.forEach(o => {
            o.init(gl);
        });
    }
}
