// import Primitive from '../../../primitive.js';
import Rectangle from './rectangle.js';
// import Vertex from '../../../vertex.js';
// import Vertices from '../../../vertices.js';
// import Buffer from '../../../buffer.js';
// import Matrix from '../../../matrix.js';

export default class SimpleLoadingBox extends Rectangle
{
    static load(name, program, application, options)
    {
        return new Promise((resolve, reject) => {
            let o = new SimpleLoadingBox(name, 0, application.programs.get(program), options);
            o.serialize();
            application.object(o);
            resolve(o);
        });
    }

    constructor(name, level, program, options)
    {
        super(name, level, program, options);

        this.min = 0;
        this.max = 0;
        this.__progress = 0;
        this.__current = 0;
        this.__idx = 0;

        this.__vertices.each(vertex => {
            this.min = Math.min(vertex.location[0], this.min);
            this.max = Math.max(vertex.location[0], this.max);
        });
    }

    get name() { return this.__name; }
    get program() { return this.__program; }
    get buffer(){ return this.__buffer; }

    set mode(v){ this.__vertices.mode = v; }
    set target(v){ this.__buffer.target = v; }
    set usage(v){ this.__buffer.usage = v; }
    set program(o){ this.__program = o; }


    bind(application, name, value, model, level)
    {
        if(!super.bind(application, name, value, model, level))
        {
            const gl = application.gl;

            if(name === "progress")
            {
                let total = this.max - this.min;
                if(this.__current < application.progress)
                {
                    this.__current += 0.01;
                }
                if(application.progress < this.__current)
                {
                    this.__current = application.progress;
                }
                gl.uniform1f(value, this.min + this.__current * total);
            }
            if(name === "idx")
            {
                let total = this.max - this.min;
                if(application.progress === this.__current)
                {
                    this.__idx += 0.01;
                    if(this.__current < this.__idx)
                    {
                        if(this.__current === 1)
                        {
                            application.finish = true;
                            // application.current = 1;
                        }
                        this.__idx = 0;
                    }
                }
                gl.uniform1f(value, this.min + this.__idx * total);
            }
        }
    }

    get name() { return this.__name; }
    get program() { return this.__program; }
    get buffer(){ return this.__buffer; }

    set mode(v){ this.__vertices.mode = v; }
    set target(v){ this.__buffer.target = v; }
    set usage(v){ this.__buffer.usage = v; }
    set program(o){ this.__program = o; }
}
