
export default class Obj
{
    static get enable() { return 1; }
    static get disable(){ return 0; }

    constructor(name, level, status)
    {
        this.__name = name;
        this.__level = level || 0;
        this.__status = status;
    }

    get name() { return this.__name; }

    set status(v){ this.__status = v; }

    render(gl, model, level) {
        console.log("render");
    }

    init(gl) {
        console.log("init");
    }
}
