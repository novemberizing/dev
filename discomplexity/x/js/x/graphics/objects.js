
export default class Objects
{
    constructor()
    {
        this.__objects = new Map();
    }

    add(o)
    {
        this.__objects.set(o.name, o);
    }

    init(gl)
    {
        this.__objects.forEach(o => {
            o.init(gl);

        });
    }

    render(gl, model, level)
    {
        this.__objects.forEach(o => {
            o.render(gl, model, level);
        });
    }
}
