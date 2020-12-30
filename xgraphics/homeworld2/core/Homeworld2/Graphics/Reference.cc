#include "Reference.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        x::map<x::string, Homeworld2::Graphics::Reference *> Homeworld2::Graphics::Reference::__references;

        Homeworld2::Graphics::Reference * Reference::get(const x::string & name)
        {
            try
            {
                return __references[name];
            }
            catch(const x::exception & e)
            {
                return nullptr;
            }
        }

        Reference::Reference(const x::string & name)
        :   x::graphics::reference(),
            __name(name),
            __version(0),
            __materials(),
            __textures(),
            __multimeshs(),
            __goblinmeshs(),
            __joints(),
            __engineshapes(),
            __root(nullptr),
            __energy(),
            __velocity(),
            __mass()
        {
            Reference::__references.put(__name, this);
        }

        Reference::~Reference()
        {
            Reference::__references.del(__name);
            unload();
        }

        void Reference::init()
        {
            __multimeshs.each([this](const x::string & name, Multimesh & multimesh){
                Homeworld2::Graphics::Joint & parent = __joints[multimesh.parent()];
                parent.add(multimesh);
            });
            __goblinmeshs.each([this](const x::string & name, Goblinmesh & goblinmesh){
                Homeworld2::Graphics::Joint & parent = __joints[goblinmesh.parent()];
                parent.add(goblinmesh);
            });
            __joints.each([this](const x::string & name, Homeworld2::Graphics::Joint & joint){
                if(joint.parent() == "")
                {
                    assertion(__root != nullptr);

                    __root = &joint;
                }
                else
                {
                    Homeworld2::Graphics::Joint & parent = __joints[joint.parent()];

                    parent.add(joint);
                }
            });
        }

        void Reference::load()
        {
            __multimeshs.each([this](const x::string & name, Multimesh & multimesh){
                multimesh.load();
            });
            __goblinmeshs.each([this](const x::string & name, Goblinmesh & goblinmesh){
                goblinmesh.load();
            });
        }

        void Reference::unload()
        {

        }

        void Reference::render()
        {

        }

        Homeworld2::Graphics::Objects::Root * Reference::build()
        {
            assertion(__root == nullptr);

            return new Homeworld2::Graphics::Objects::Root(this, __root->build(__textures, __materials));
        }
    }
}
