import Matrix from './matrix.js';

export default class Projection
{
    constructor(fovy, aspect, near, far)
    {
        // TODO: 0.01745329251994329576923690768489 TO CONST VARIABLE
        this.__fovy = fovy || (45 * 0.01745329251994329576923690768489);
        this.__aspect = aspect || 1;
        this.__near = near || 0.1;
        this.__far = far || 10000.0;
        this.__matrix = Matrix.perspective(this.__fovy, this.__aspect, this.__near, this.__far);
    }

    get matrix(){ return this.__matrix; }
}
