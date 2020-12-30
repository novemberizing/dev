import Reference from '../x/graphics/reference.js';
import Matrix from '../x/graphics/matrix.js';

export default class Homeworld2Reference extends Reference
{
    constructor(name, location, rotation, scale, axis)
    {
        super(name, null, location, rotation, scale, axis);
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

        if(this.__rotation[1] !== 0)
        {
            this.__model = Matrix.rotate(this.__model, (this.__location[0] > 0 ? this.__rotation[1] : -this.__rotation[1]), [1, 0, 0, 0]);
        }
        if(this.__rotation[0] !== 0)
        {
            this.__model = Matrix.rotate(this.__model, this.__rotation[0], [0, 1, 0, 0]);
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
