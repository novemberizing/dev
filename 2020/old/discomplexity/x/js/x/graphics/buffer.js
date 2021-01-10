
export default class Buffer
{
    static get none() { return 0; }
    static get array() { return 1; }
    static get atomic_counter() { return 2; }
    static get copy_read() { return 3; }
    static get copy_write() { return 4; }
    static get dispatch_indirect() { return 5; }
    static get draw_indirect() { return 6; }
    static get element_array() { return 7; }
    static get pixel_pack() { return 8; }
    static get pixel_unpack() { return 9; }
    static get query() { return 10; }
    static get shader_storage() { return 11; }
    static get texture() { return 12; }
    static get transform_feedback() { return 13; }
    static get uniform() { return 14; }

    static get stream(){ return 1; }
    static get statical(){ return 2; }
    static get dynamical(){ return 3; }

    static get draw(){ return 1; }
    static get read(){ return 2; }
    static get copy(){ return 3; }

    static targetFromStr(s)
    {
        if(s === "array")
        {
            s = Buffer.array;
        }
        else
        {
            throw new Error();
        }
        return s;
    }

    static usageFromStr(s)
    {
        if(s[0] === "statical")
        {
            s[0] = Buffer.statical;
        }
        else
        {
            throw new Error();
        }

        if(s[1] === "draw")
        {
            s[1] = Buffer.draw;
        }
        else
        {
            throw new Error();
        }

        return s;
    }

    static getTarget(gl, target)
    {
        switch(target)
        {
            case Buffer.array:  return gl.ARRAY_BUFFER;
            default:            throw new Error();
        }
    }

    static getUsage(gl, usage)
    {
        switch(usage[0])
        {
            case Buffer.statical:   switch(usage[1])
                                    {
                                    case Buffer.draw:   return gl.STATIC_DRAW;
                                    default:            throw new Error();
                                    }
            default:                throw new Error();
        }
    }

    constructor()
    {
        this.__data = null;
        this.__target = Buffer.none;
        this.__usage = [Buffer.none, Buffer.none];
        this.__id = 0;
    }

    set target(v){ this.__target = v; }
    set usage(v){ this.__usage = v; }
    set data(v){ this.__data = v; }

    get data() { return this.__data; }
    get size() { return this.__data ? this.__data.length : 0; }

    init(gl)
    {
        if(!this.__id)
        {
            this.__id = gl.createBuffer();
            gl.bindBuffer(Buffer.getTarget(gl, this.__target), this.__id);
            gl.bufferData(Buffer.getTarget(gl, this.__target), this.__data, Buffer.getUsage(gl, this.__usage));
        }
    }

    bind(gl)
    {
        gl.bindBuffer(Buffer.getTarget(gl, this.__target), this.__id);
    }
}
