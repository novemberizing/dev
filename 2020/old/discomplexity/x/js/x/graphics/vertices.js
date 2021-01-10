
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

    push(v)
    {
        this.__vertices.push(v);
    }

    set(v)
    {
        this.__vertices = v;
    }

    serialize(buffer)
    {
        let array = [];
        let total = 0;

        this.__vertices.forEach(vertex => {
            let result = [];
            array.push(new Float32Array(result.concat(vertex.position,
                                                      vertex.normal,
                                                      vertex.color,
                                                      vertex.texture,
                                                      vertex.tangent,
                                                      vertex.binormal)));
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
