#include "Reference.hh"
// #include "Unit/Ship.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        Reference::Reference(const x::string & name)
        :   x::reality::reference(name),
            x::graphics::reference(),
            __version(0),
            __category(),
            __materials(),
            __textures(),
            __multimeshs(),
            __goblinmeshs(),
            __joints(),
            __engineshapes(),
            __root(nullptr)
        {
            x::console::out << "name: " << __name << x::endl << x::flush;
        }

        Reference::Reference(x::string && name)
        :   x::reality::reference(x::move(name)),
            x::graphics::reference(),
            __version(0),
            __category(),
            __materials(),
            __textures(),
            __multimeshs(),
            __goblinmeshs(),
            __joints(),
            __engineshapes(),
            __root(nullptr)
        {
        }

        Reference::Reference()
        :   x::reality::reference(),
            x::graphics::reference(),
            __version(0),
            __category(),
            __materials(),
            __textures(),
            __multimeshs(),
            __goblinmeshs(),
            __joints(),
            __engineshapes(),
            __root(nullptr)
        {
        }

        Reference::Reference(const Reference & o)
        :   x::reality::reference(o),
            x::graphics::reference(o),
            __version(o.__version),
            __category(o.__category),
            __materials(o.__materials),
            __textures(o.__textures),
            __multimeshs(o.__multimeshs),
            __goblinmeshs(o.__goblinmeshs),
            __joints(o.__joints),
            __engineshapes(o.__engineshapes),
            __root(o.__root)
        {
        }

        Reference::Reference(Reference && o) noexcept
        :   x::reality::reference(x::move(o)),
            x::graphics::reference(x::move(o)),
            __version(o.__version),
            __category(x::move(o.__category)),
            __materials(x::move(o.__materials)),
            __textures(x::move(o.__textures)),
            __multimeshs(x::move(o.__multimeshs)),
            __goblinmeshs(x::move(o.__goblinmeshs)),
            __joints(x::move(o.__joints)),
            __engineshapes(x::move(o.__engineshapes)),
            __root(o.__root)
        {
            o.__version = 0;
            o.__root = nullptr;
        }

        Reference::~Reference()
        {
        }

        Reference & Reference::operator=(const Reference & o)
        {
            if(&o != this)
            {
                x::reality::reference::operator=(o);
                x::graphics::reference::operator=(o);

                __version = o.__version;
                __category = o.__category;
                __materials = o.__materials;
                __textures = o.__textures;
                __multimeshs = o.__multimeshs;
                __goblinmeshs = o.__goblinmeshs;
                __joints = o.__joints;
                __engineshapes = o.__engineshapes;
                __root = o.__root;
            }
            return *this;
        }

        Reference & Reference::operator=(Reference && o) noexcept
        {
            if(&o != this)
            {
                x::reality::reference::operator=(x::move(o));
                x::graphics::reference::operator=(x::move(o));

                __version = o.__version;
                __category = x::move(o.__category);
                __materials = x::move(o.__materials);
                __textures = x::move(o.__textures);
                __multimeshs = x::move(o.__multimeshs);
                __goblinmeshs = x::move(o.__goblinmeshs);
                __joints = x::move(o.__joints);
                __engineshapes = x::move(o.__engineshapes);
                __root = o.__root;

                o.__version = 0;
                o.__root = nullptr;
            }
            return *this;
        }

        void Reference::init()
        {
            __multimeshs.each([this](const x::string & name, Multimesh & multimesh){
                Joint & joint = __joints[multimesh.parent()];
                joint.add(&multimesh);
                x::array<Material> & materials = __materials;
                x::array<x::graphics::texture> & textures = __textures;
                multimesh.singlemeshs.each([&materials, &textures](Singlemesh & singlemesh) {
                    singlemesh.children.each([&materials, &textures](typename x::var<Primitive *>::type & primitive){
                        primitive->set(materials);
                        primitive->set(&textures);
                    });
                });
            });
            __goblinmeshs.each([this](const x::string & name, Goblinmesh & goblinmesh){
                Joint & joint = __joints[goblinmesh.parent()];
                joint.add(&goblinmesh);
                x::array<Material> & materials = __materials;
                x::array<x::graphics::texture> & textures = __textures;
                goblinmesh.singlemesh.children.each([&materials, &textures](typename x::var<Primitive *>::type & primitive){
                    primitive->set(materials);
                    primitive->set(&textures);
                });
            });
            __joints.each([this](const x::string & name, Joint & joint){
                if(joint.parent() == "")
                {
                    if(__root != nullptr)
                    {
                        exceptional();
                    }
                    __root = &joint;
                }
                else
                {
                    Joint & parent = __joints[joint.parent()];
                    parent.add(&joint);
                }
            });
        }

        void Reference::load()
        {
            init();

            __textures.each([](x::graphics::texture & texture){
                texture.load();
            });

            __multimeshs.each([](const x::string & name, Multimesh & multimesh){
                multimesh.load();
            });
            __goblinmeshs.each([](const x::string & name, Goblinmesh & goblinmesh){
                goblinmesh.load();
            });

        }

        void Reference::unload()
        {
            __multimeshs.each([](const x::string & name, Multimesh & multimesh){
                multimesh.unload();
            });
            __goblinmeshs.each([](const x::string & name, Goblinmesh & goblinmesh){
                goblinmesh.unload();
            });
        }

        void Reference::render(const x::reality::matrix & model)
        {
            exceptional();
        }

        Object * Reference::build()
        {
            return __root->build();
        }
    }
}
