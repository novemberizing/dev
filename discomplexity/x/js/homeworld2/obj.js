import Obj from '../x/graphics/obj.js';
import Matrix from '../x/graphics/matrix.js';

export default class Homeworld2Object extends Obj
{
    constructor(name, level, status)
    {
        super(name, level, status);
        this.__version = 0;
        this.__category = "";
        this.__materials = new Map();
        this.__textures = new Map();
        this.__multimesh = new Map();
        this.__goblinmesh = new Map();
        this.__joints = new Map();
        this.__root = null;
    }

    init(gl) {
        console.log("homeworld2 object init");
        console.log({version: this.__version, category: this.__category});

        this.__multimesh.forEach(multimesh => {
            multimesh.init(gl);
        });

        this.__goblinmesh.forEach(goblinmesh => {
            goblinmesh.init(gl);
        });
    }

    get name() { return this.__name; }
    get program() { return this.__program; }
    get buffer(){ return this.__buffer; }
    get multimesh(){ return this.__multimesh; }
    get goblinmesh(){ return this.__goblinmesh; }
    get joints(){ return this.__joints; }

    set mode(v){ this.__vertices.mode = v; }
    set target(v){ this.__buffer.target = v; }
    set usage(v){ this.__buffer.usage = v; }
    set program(o){ this.__program = o; }
    set root(o){ this.__root = o; }

    render(gl)
    {
        this.__root.render(gl, Matrix.identity(), 0);

        // this.__multimesh.forEach(multimesh => {
        //     multimesh.render(gl);
        // });
        // this.__goblinmesh.forEach(goblinmesh => {
        //     goblinmesh.render(gl);
        // });
    }
}
