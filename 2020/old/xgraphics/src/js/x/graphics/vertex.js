
export default class Vertex
{
    static get stride() { return 88; }

    constructor(location, normal, color)
    {
        this.location = location || [0, 0, 0, 1];
        this.normal   = normal || [0, 0, 0, 0];
        this.color    = color || [0, 0, 0, 1];
        this.texture  = [0, 0];
        this.tangent  = [0, 0, 0, 0];
        this.binormal = [0, 0, 0, 0];
    }
}
