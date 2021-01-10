import Homeworld2Object from './obj.js';
import Multimesh from './multimesh.js';
import Goblinmesh from './goblinmesh.js';
import Singlemesh from './singlemesh.js';
import Primitive from '../x/graphics/primitive.js';
import Obj from '../x/graphics/obj.js';
import Buffer from '../x/graphics/buffer.js';
import Vertices from '../x/graphics/vertices.js';
import Joint from './joint.js';

export default class ObjectFile
{
    static load(path, name, application)
    {
        return new Promise((resolve, reject) => {
            let w = new Worker('/js/homeworld2/object.unpack.js');
            let o = new Homeworld2Object(name, 0, 1);

            w.postMessage({path});
            w.onmessage = (event) => {
                if(event.data.version)
                {
                    console.log("version");
                    o.__version = event.data.version;
                }
                else if(event.data.category)
                {
                    console.log("category");
                    o.__category = event.data.category;
                }
                else if(event.data.material)
                {
                    console.log("material");
                    // TODO: DATA TO MATERIAL CLASS
                    // o.__materials.set(event.data.material.name, event.data.material);
                }
                else if(event.data.texture)
                {
                    console.log("texture");
                    // TODO: DATA TO TEXTURE CLASS
                    // o.__textures.set(event.data.texture.name, event.data.texture);
                }
                else if(event.data.multimesh)
                {
                    console.log("multimesh");
                    let multimesh = new Multimesh(event.data.multimesh.name, event.data.multimesh.parent, Obj.enable);
                    event.data.multimesh.children.forEach(_singlemesh => {
                        let singlemesh = new Singlemesh(_singlemesh.level, multimesh.status);
                        _singlemesh.primitives.forEach(_primitive => {
                            let primitive = new Primitive("", _singlemesh.level, multimesh.status);
                            primitive.target = Buffer.targetFromStr(_primitive.target);
                            primitive.usage = Buffer.usageFromStr(_primitive.usage);
                            primitive.mode = Vertices.modeFromStr(_primitive.mode);
                            primitive.program = application.programs.get(_primitive.program);
                            primitive.vertices.set(_primitive.vertices);
                            primitive.buffer.data = _primitive.data;
                            primitive.indices = _primitive.indices;
                            singlemesh.add(primitive);
                        });
                        multimesh.singlemesh.set(singlemesh.level, singlemesh);
                    });
                    o.multimesh.set(multimesh.name, multimesh);
                    // if(multimesh.name === "Root_mesh")
                    // {
                    //     multimesh.status = Obj.enable;
                    // }
                    //
                    // if(multimesh.name === "Weapon_BigGun_Position_mesh")
                    // {
                    //     multimesh.status = Obj.enable;
                    // }
                }
                else if(event.data.goblinmesh)
                {
                    console.log("goblinmesh");
                    let goblinmesh = new Goblinmesh(event.data.goblinmesh.name, event.data.goblinmesh.parent, Obj.enable);
                    goblinmesh.singlemesh = new Singlemesh(event.data.goblinmesh.singlemesh.level, goblinmesh.status);
                    event.data.goblinmesh.singlemesh.primitives.forEach(_primitive => {
                        let primitive = new Primitive("", event.data.goblinmesh.singlemesh.level, goblinmesh.status);
                        primitive.target = Buffer.targetFromStr(_primitive.target);
                        primitive.usage = Buffer.usageFromStr(_primitive.usage);
                        primitive.mode = Vertices.modeFromStr(_primitive.mode);
                        primitive.program = application.programs.get(_primitive.program);
                        primitive.vertices.set(_primitive.vertices);
                        primitive.buffer.data = _primitive.data;
                        primitive.indices = _primitive.indices;
                        goblinmesh.singlemesh.add(primitive);
                    });
                    o.goblinmesh.set(goblinmesh.name, goblinmesh);
                }
                else if(event.data.joints)
                {
                    console.log("joints");
                    event.data.joints.forEach(_joint => {
                        let joint = new Joint(_joint.name,
                                          _joint.parent,
                                          _joint.position,
                                          _joint.rotation,
                                          _joint.scale,
                                          _joint.axis,
                                          _joint.freedom);
                        o.joints.set(joint.name, joint);
                    });
                }
                else if(event.data.engineshape)
                {
                    console.log("engineshape");
                    // console.log({engineshape: event.data.engineshape});
                }
                else if(event.data.engineburn)
                {
                    console.log("engineburn");
                    // console.log({engineburn: event.data.engineburn});
                }
                else if(event.data.navlights)
                {
                    console.log("navlights");
                    // console.log({navlights: event.data.navlights});
                }
                else if(event.data.marker)
                {
                    console.log("marker");
                    // console.log({marker: event.data.marker});
                }
                else if(event.data.boundary)
                {
                    console.log("boundary");
                    // console.log({boundary: event.data.boundary});
                }
                else if(event.data.collision)
                {
                    console.log("collision");
                    // console.log({collision: event.data.collision});
                }
                else if(event.data.basicmesh)
                {
                    console.log("basicmesh");
                    // console.log({basicmesh: event.data.basicmesh});
                }
                else if(event.data.information)
                {
                    console.log("information");
                    // console.log({information: event.data.information});
                }
                else if(event.data.finish)
                {
                    if(event.data.error)
                    {
                        w.terminate();
                        w = null;
                        reject(new Error(event.data.error));
                    }
                    else
                    {
                        console.log({multimesh: o.multimesh});
                        console.log("finish");
                        o.joints.forEach(joint => {
                            if(joint.parent === '')
                            {
                                o.root = joint;
                            }
                            else
                            {
                                let parent = o.joints.get(joint.parent);
                                parent.children.set(joint.name, joint);
                            }
                        });
                        o.multimesh.forEach(multimesh => {
                            let parent = o.joints.get(multimesh.parent);
                            parent.objects.push(multimesh);
                        });
                        o.goblinmesh.forEach(goblinmesh => {
                            let parent = o.joints.get(goblinmesh.parent);
                            parent.objects.push(goblinmesh);
                        });
                        w.terminate();
                        w = null;
                        application.objects.add(o);
                        resolve(o);
                    }
                }
            };
        });
    }
}
