#include "Object.hh"

namespace Homeworld2
{
    Object::Object(const x::string & name)
    :   x::graphics::object(name),
        __version(0),
        __category(),
        __materials(),
        __textures(),
        __multimesh(),
        __goblinmesh(),
        __joints(),
        __engineshapes(),
        __root(nullptr)
    {
    }

    Object::Object(x::string && name)
    :   x::graphics::object(x::move(name)),
        __version(0),
        __category(),
        __materials(),
        __textures(),
        __multimesh(),
        __goblinmesh(),
        __joints(),
        __engineshapes(),
        __root(nullptr)
    {
    }

    Object::Object()
    :   x::graphics::object(),
        __version(0),
        __category(),
        __materials(),
        __textures(),
        __multimesh(),
        __goblinmesh(),
        __joints(),
        __engineshapes(),
        __root(nullptr)
    {
    }

    Object::Object(const Object & o)
    :   x::graphics::object(o),
        __version(o.__version),
        __category(o.__category),
        __materials(o.__materials),
        __textures(o.__textures),
        __multimesh(o.__multimesh),
        __goblinmesh(o.__goblinmesh),
        __joints(o.__joints),
        __engineshapes(o.__engineshapes),
        __root(o.__root)
    {
    }

    Object::Object(Object && o) noexcept
    :   x::graphics::object(x::move(o)),
        __version(o.__version),
        __category(x::move(o.__category)),
        __materials(x::move(o.__materials)),
        __textures(x::move(o.__textures)),
        __multimesh(x::move(o.__multimesh)),
        __goblinmesh(x::move(o.__goblinmesh)),
        __joints(x::move(o.__joints)),
        __engineshapes(x::move(o.__engineshapes)),
        __root(o.__root)
    {
        o.__version = 0;
        o.__root = nullptr;
    }

    Object::~Object()
    {
    }

    Object & Object::operator=(const Object & o)
    {
        if(&o != this)
        {
            x::graphics::object::operator=(o);
            __version = o.__version;
            __category = o.__category;
            __materials = o.__materials;
            __textures = o.__textures;
            __multimesh = o.__multimesh;
            __goblinmesh = o.__goblinmesh;
            __joints = o.__joints;
            __engineshapes = o.__engineshapes;
            __root = o.__root;
        }
        return *this;
    }

    Object & Object::operator=(Object && o) noexcept
    {
        if(&o != this)
        {
            x::graphics::object::operator=(x::move(o));
            __version = o.__version;
            __category = x::move(o.__category);
            __materials = x::move(o.__materials);
            __textures = x::move(o.__textures);
            __multimesh = x::move(o.__multimesh);
            __goblinmesh = x::move(o.__goblinmesh);
            __joints = x::move(o.__joints);
            __engineshapes = x::move(o.__engineshapes);
            __root = o.__root;

            o.__version = 0;
            o.__root = nullptr;
        }
        return *this;
    }

    void Object::init()
    {
        __multimesh.each([this](const x::string & name, Multimesh & multimesh){
            try
            {
                Joint & joint = __joints[multimesh.parent()];
                joint.add(&multimesh);
            }
            catch(const x::exception & e)
            {
                x::console::out << "exception" << x::endl;
            }
        });
        __goblinmesh.each([this](const x::string & name, Goblinmesh & goblinmesh){
            try
            {
                Joint & joint = __joints[goblinmesh.parent()];
                joint.add(&goblinmesh);
            }
            catch(const x::exception & e)
            {
                x::console::out << "exception" << x::endl;
            }
        });
        __joints.each([this](const x::string & name, Joint & joint){
            try
            {
                if(joint.parent() == "")
                {
                    if(__root != nullptr)
                    {
                        x::console::out << "root is already exist" << x::endl;
                        exceptional();
                    }
                    __root = &joint;
                }
                else
                {
                    Joint & parent = __joints[joint.parent()];
                    parent.add(&joint);
                }
            }
            catch(const x::exception & e)
            {
                x::console::out << "exception" << x::endl;
            }
        });
    }

    void Object::load()
    {
        __multimesh.each([](const x::string & name, Multimesh & multimesh){
            multimesh.load();
        });
        __goblinmesh.each([](const x::string & name, Goblinmesh & goblinmesh){
            goblinmesh.load();
        });
    }

    void Object::unload()
    {
        __multimesh.each([](const x::string & name, Multimesh & multimesh){
            multimesh.unload();
        });
        __goblinmesh.each([](const x::string & name, Goblinmesh & goblinmesh){
            goblinmesh.unload();
        });
    }
    void Object::render(const x::graphics::matrix & model, x::uint32 level)
    {
        if(__root)
        {
            __root->render(model, level);
        }
        // x::console::out << __level << " = " << level << x::endl;
        // __multimesh.each([&model, &level](const x::string & name, Multimesh & multimesh){
        //     multimesh.render(model, level);
        // });
        // __goblinmesh.each([&model, &level](const x::string & name, Goblinmesh & goblinmesh){
        //     goblinmesh.render(model, level);
        // });
    }

    void Object::refresh(const x::graphics::matrix & model)
    {
        if(__root)
        {
            __root->refresh(model);
        }
    }

    void Object::exec(const x::array<x::string> & strings, x::uint64 index)
    {
        if(index < strings.size())
        {
            if(strings[index] == "load")
            {
                if(index + 1 < strings.size())
                {
                    index = index + 1;
                    x::graphics::application & application = x::graphics::application::get();
                    x::graphics::surface & surface = application.surface();
                    surface.add(strings[index], this);
                    x::graphics::application::refresh();
                }
                else
                {
                    x::graphics::util::unknown(strings);
                }
            }
            else if(strings[index] == "enable")
            {
                if(index + 1 < strings.size())
                {
                    index = index + 1;
                    x::exception::safe<x::map<x::string, Multimesh> &, const x::string &>([](x::map<x::string, Multimesh> & multimeshs, const x::string & key){ multimeshs[key].status(1); }, __multimesh, strings[index]);
                    x::exception::safe<x::map<x::string, Goblinmesh> &, const x::string &>([](x::map<x::string, Goblinmesh> & goblinmeshs, const x::string & key){ goblinmeshs[key].status(1); }, __goblinmesh, strings[index]);
                    x::graphics::application::refresh();
                }
                else
                {
                    x::graphics::util::unknown(strings);
                }
            }
            else if(strings[index] == "disable")
            {
                if(index + 1 < strings.size())
                {
                    index = index + 1;
                    x::exception::safe<x::map<x::string, Multimesh> &, const x::string &>([](x::map<x::string, Multimesh> & multimeshs, const x::string & key){ multimeshs[key].status(0); }, __multimesh, strings[index]);
                    x::exception::safe<x::map<x::string, Goblinmesh> &, const x::string &>([](x::map<x::string, Goblinmesh> & goblinmeshs, const x::string & key){ goblinmeshs[key].status(0); }, __goblinmesh, strings[index]);
                    x::graphics::application::refresh();
                }
                else
                {
                    x::graphics::util::unknown(strings);
                }
            }
            else if(strings[index] == "joint")
            {
                if(index + 1 < strings.size())
                {
                    index = index + 1;
                    try
                    {
                        __joints[strings[index]].exec(strings, index + 1);
                    }
                    catch(const x::exception & e)
                    {

                    }
                    // x::graphics::util::unknown(strings);
                }
                else
                {
                    __joints.each([](const x::string & key, Joint & joint){
                        x::console::out << joint.name() << x::endl;
                    });
                }
            }
            else if(strings[index] == "rotation")
            {
                __root->exec(strings, index);
            }
            else if(strings[index] == "position")
            {
                __root->exec(strings, index);
            }
            else
            {
                x::graphics::util::unknown(strings);
            }
        }
        else
        {
            __multimesh.each([](const x::string & name, Multimesh & multimesh){
                x::console::out << multimesh.name() << x::endl;
                // multimesh.render(model, level);
            });
            __goblinmesh.each([](const x::string & name, Goblinmesh & goblinmesh){
                x::console::out << goblinmesh.name() << x::endl;
                //goblinmesh.render(model, level);
            });
        }
    }
}
