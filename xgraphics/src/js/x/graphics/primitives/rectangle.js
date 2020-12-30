import Primitive from '../primitive.js';
import Vertex from '../vertex.js';
import Vertices from '../vertices.js';
import Buffer from '../buffer.js';
import Matrix from '../matrix.js';

export default class Rectangle extends Primitive
{
    static load(name, program, application, options)
    {
        return new Promise((resolve, reject) => {
            let o = new Rectangle(name, 0, application.programs.get(program), options);
            o.serialize();
            application.object(o);
            resolve(o);
        });
    }

    constructor(name, level, program, options)
    {
        super(name, level, program);

        this.mode = Vertices.triangle;
        this.target = Buffer.array;
        this.usage = [Buffer.statical, Buffer.draw];

        this.push(new Vertex([-0.5, 0.5, 0.0, 1.0], [ 0.0,  0.0,  1.0, 0.0]));
        this.push(new Vertex([ 0.5, 0.5, 0.0, 1.0], [ 0.0,  0.0,  1.0, 0.0]));
        this.push(new Vertex([ 0.5,-0.5, 0.0, 1.0], [ 0.0,  0.0,  1.0, 0.0]));

        this.push(new Vertex([ 0.5,-0.5, 0.0, 1.0], [ 0.0,  0.0,  1.0, 0.0]));
        this.push(new Vertex([-0.5,-0.5, 0.0, 1.0], [ 0.0,  0.0,  1.0, 0.0]));
        this.push(new Vertex([-0.5, 0.5, 0.0, 1.0], [ 0.0,  0.0,  1.0, 0.0]));

        if(options)
        {
            if(options.scale)
            {
                this.__vertices.each(vertex => {
                    vertex.location = Matrix.vectorMultiply(Matrix.scale(Matrix.identity(), options.scale), vertex.location);
                });
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
