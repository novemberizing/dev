import Complex from '../x/graphics/complex.js';
import Obj from '../x/graphics/complex.js';

export default class Singlemesh extends Complex
{
    constructor(level, status)
    {
        super("", level, status);
    }

    get level(){ return this.__level; }

    set status(v)
    {
        this.__status = v;
        this.__children.forEach(o => o.status = v);
    }
}
