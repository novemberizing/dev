
export default class Vertex
{
    static get stride() { return 88; }

    constructor(position, normal, color)
    {
        this.position = position || [0, 0, 0, 1];
        this.normal   = normal || [0, 0, 0, 0];
        this.color    = color || [0, 0, 0, 1];
        this.texture  = [0, 0];
        this.tangent  = [0, 0, 0, 0];
        this.binormal = [0, 0, 0, 0];
    }
}
