import Obj from '../x/graphics/obj.js';
import Matrix from '../x/graphics/matrix.js';
import Homeworld2Reference from './reference.js';

export default class Homeworld2Object extends Obj
{
    constructor(name, level)
    {
        super(name, level);
        this.__version = 0;
        this.__category = "";
        this.__materials = new Array();
        this.__textures = new Array();
        this.__multimesh = new Map();
        this.__goblinmesh = new Map();
        this.__joints = new Map();
        this.__root = null;
    }

    load(application) {
        console.log("homeworld2 object init");
        console.log({version: this.__version, category: this.__category});
        this.__textures.forEach(texture => {
            texture.load(application);
        });
        this.__multimesh.forEach(multimesh => {
            multimesh.load(application);
        });

        this.__goblinmesh.forEach(goblinmesh => {
            goblinmesh.load(application);
        });
        this.__load = true;
    }

    unload(application)
    {
        this.__multimesh.forEach(multimesh => {
            multimesh.unload(application);
        });

        this.__goblinmesh.forEach(goblinmesh => {
            goblinmesh.unload(application);
        });
        this.__textures.forEach(texture => {
            texture.unload(application);
        });
        this.__load = false;
    }

    material(index)
    {
        return this.__materials[index];
    }

    texture(index)
    {
        return this.__textures[index];
    }

    get name() { return this.__name; }
    get program() { return this.__program; }
    get buffer(){ return this.__buffer; }
    get multimesh(){ return this.__multimesh; }
    get goblinmesh(){ return this.__goblinmesh; }
    get joints(){ return this.__joints; }
    get textures(){ return this.__textures; }
    get materials(){ return this.__materials; }

    set mode(v){ this.__vertices.mode = v; }
    set target(v){ this.__buffer.target = v; }
    set usage(v){ this.__buffer.usage = v; }
    set program(o){ this.__program = o; }
    set root(o){ this.__root = o; }

    build(name)
    {
        console.log("root build");
        return this.__root.build(name);
    }
}
