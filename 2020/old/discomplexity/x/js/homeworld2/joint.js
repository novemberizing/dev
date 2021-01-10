import Matrix from '../x/graphics/matrix.js';

export default class Joint
{
    constructor(name, parent, position, rotation, scale, axis, freedom)
    {
        this.__name = name;
        this.__parent = parent;
        this.__position = position;
        this.__rotation = rotation;
        this.__scale = scale;
        this.__axis = axis;
        this.__freedom = freedom;
        this.__children = new Map();
        this.__objects = new Array();
        this.__model = Matrix.identity();
    }

    get name(){ return this.__name; }
    get parent(){ return this.__parent; }
    get children(){ return this.__children; }
    get objects(){ return this.__objects; }

    render(gl, model, level)
    {
        this.__model = Matrix.translate(model, this.__position);
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
            this.__model = Matrix.rotate(this.__model, (this.__position[0] > 0 ? this.__rotation[1] : -this.__rotation[1]), [1, 0, 0, 0]);
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

        this.__objects.forEach(o => {
            o.render(gl, this.__model, level);
        });
        this.__children.forEach(o => {
            o.render(gl, this.__model, level);
        });
    }
}
