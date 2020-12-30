
export default class Indices
{
    constructor(indices)
    {
        this.__data = null;
        this.__id = null;
        this.__indices = indices;
    }

    load(application)
    {
        const gl = application.gl;

        if(this.__indices)
        {
            if(!this.__id)
            {
                if(!this.__data)
                {
                    this.__data = new Uint16Array(this.__indices);
                }
                this.__id = gl.createBuffer();
                gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.__id);
                gl.bufferData(gl.ELEMENT_ARRAY_BUFFER, this.__data, gl.STATIC_DRAW);
            }
        }
    }

    unload(application)
    {
        const gl = application.gl;
    }

    bind(application)
    {
        const gl = application.gl;

        gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, this.__id);
    }

    get size() { return this.__indices ? this.__indices.length : 0; }
}
