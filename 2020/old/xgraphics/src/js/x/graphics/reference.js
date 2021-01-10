import Vector from './vector.js';
import Matrix from './matrix.js';

export default class Reference
{
    constructor(name, object, location, rotation, scale, axis)
    {
        this.__name = name;
        this.__location = Vector.four(location, 0.0);
        this.__rotation = Vector.four(rotation, 0.0);
        this.__scale = Vector.four(scale || [1, 1, 1, 0], 0.0);
        this.__axis = Vector.four(axis, 0.0);
        this.__model = Matrix.identity();
        this.__level = 0;
        this.__objects = new Map();
        this.__children = new Map();

        if(object)
        {
            this.__objects.set(object.name, object);
        }
    }

    render(application, model, level)
    {
        const gl = application.gl;

        this.__model = Matrix.translate(model, this.__location);
        if(this.__axis[0] !== 0)
        {
            this.__model = Matrix.rotate(this.__model, this.__axis[0], [1, 0, 0, 0]);
        }
        if(this.__axis[1] !== 0)
        {
            this.__model = Matrix.rotate(this.__model, this.__axis[1], [0, 1, 0, 0]);
        }
        if(this.__axis[2] !== 0)
        {
            this.__model = Matrix.rotate(this.__model, this.__axis[2], [0, 0, 1, 0]);
        }

        if(this.__rotation[0] !== 0)
        {
            this.__model = Matrix.rotate(this.__model, this.__rotation[0], [1, 0, 0, 0]);
        }
        if(this.__rotation[1] !== 0)
        {
            this.__model = Matrix.rotate(this.__model, this.__rotation[1], [0, 1, 0, 0]);
        }
        if(this.__rotation[2] !== 0)
        {
            this.__model = Matrix.rotate(this.__model, this.__rotation[2], [0, 0, 1, 0]);
        }

        this.__model = Matrix.scale(this.__model, this.__scale);

        this.__objects.forEach((object, name) => {
            // console.log(object);
            object.render(application, this.__model, level);
        });

        this.__children.forEach((reference, name) => {
            reference.render(application, this.__model, level);
        });
    }

    get name(){ return this.__name; }
    get objects(){ return this.__objects; }
    get children(){ return this.__children; }
}
