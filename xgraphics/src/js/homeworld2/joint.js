import Matrix from '../x/graphics/matrix.js';
import Homeworld2Reference from './reference.js';

export default class Joint
{
    constructor(name, parent, location, rotation, scale, axis, freedom)
    {
        this.__name = name;
        this.__parent = parent;
        this.__location = location;
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

    build(name)
    {
        let reference = new Homeworld2Reference(name, this.__location, this.__rotation, this.__scale, this.__axis);
        this.__objects.forEach(o => {
            // console.log(o);
            reference.objects.set(o.name, o);
        });
        this.__children.forEach(o => {
            reference.children.set(o.name, o.build(o.name));
        });
        return reference;
    }
}
