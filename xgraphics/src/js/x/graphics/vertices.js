import Vertor from './vector.js';

export default class Vertices
{
    static get none(){ return 0; }
    static get point(){ return 1; }
    static get line(){ return 2; }
    static get patch(){ return 3; }
    static get triangle(){ return 4; }

    static get strip(){ return 1; }
    static get loop(){ return 2; }
    static get fan(){ return 3; }

    static get adjacent(){ return 1; }

    static modeFromStr(s)
    {
        if(s === "triangle")
        {
            return Vertices.triangle;
        }
        else
        {
            throw new Error();
        }
        return s;
    }

    constructor()
    {
        this.__mode = Vertices.none;
        this.__type = Vertices.none;
        this.__adjacency = Vertices.none;
        this.__id = Vertices.none;
        this.__vertices = [];
    }

    each(f)
    {
        this.__vertices.forEach(f);
    }

    push(v)
    {
        this.__vertices.push(v);
    }

    set(v)
    {
        this.__vertices = v;
    }

    load(application)
    {
        // console.log("vertices load");

        const gl = application.gl;
    }

    unload(application)
    {
        console.log("vertices unload");

        const gl = application.gl;
    }

    bind(application)
    {
        console.log("vertices bind");

        const gl = application.gl;
    }

    serialize(buffer)
    {
        console.log("serialize");
        let array = [];
        let total = 0;

        this.__vertices.forEach(vertex => {
            let result = [];
            array.push(new Float32Array(result.concat(Vertor.four(vertex.location, 1.0),
                                                      Vertor.four(vertex.normal, 0.0),
                                                      Vertor.four(vertex.color, 1.0),
                                                      Vertor.two(vertex.texture),
                                                      Vertor.four(vertex.tangent, 0.0),
                                                      Vertor.four(vertex.binormal, 0.0))));
            total += array[array.length - 1].length;
        });
        let o = new Float32Array(total);
        total = 0;
        array.forEach(value => {
            o.set(value, total);
            total += value.length;
        });
        buffer.data = o;
    }

    get size(){ return this.__vertices.length; }
    set mode(v){ this.__mode = v; }
}
