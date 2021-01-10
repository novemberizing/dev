import Vector from './vector.js';

export default class Light
{
    constructor(location, color, ambient) {
        this.__location = Vector.four(location, 1);
        this.__color = Vector.four(color, 1);
        this.__ambient = ambient || 1;
    }

    get location(){ return this.__location; }
    get color(){ return this.__color; }
    get ambient(){ return this.__ambient; }
}
