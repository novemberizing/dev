import Obj from './obj.js';

export default class Complex extends Obj
{
    constructor(name, level)
    {
        super(name, level);

        this.__children = new Array();
    }

    add(o)
    {
        this.__children.push(o);
    }

    render(application, model, level)
    {
        const gl = application.gl;

        this.__children.forEach(o => {
            o.render(application, model, level);
        });
    }

    load(application) {
        this.__children.forEach(o => {
            o.load(application);
        });
        this.__load = true;
    }

    unload(application) {
        this.__children.forEach(o => {
            o.unload(application);
        });
        this.__load = false;
    }
}
