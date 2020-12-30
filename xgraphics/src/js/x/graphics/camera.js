import Vector from './vector.js';
import Matrix from './matrix.js';

export default class Camera
{
    constructor(location, center, up)
    {
        this.__center = Vector.four(center, 0.0);
        this.__up = Vector.four(up, 0.0);
        this.__location = Vector.four(location, 1.0);
        this.__matrix = Matrix.lookat(this.__location, this.__center, this.__up);
    }

    get matrix(){ return this.__matrix; }
    get location(){ return this.__location; }
}
