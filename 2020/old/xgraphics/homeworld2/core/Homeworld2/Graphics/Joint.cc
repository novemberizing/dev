#include "Joint.hh"

#include <x/graphics/application.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        Joint::Joint()
        :   __name(),
            __parent(),
            __location(),
            __rotation(),
            __scale(),
            __axis(),
            __freedom(),
            __children(),
            __goblinmeshs(),
            __multimeshs()
        {
        }

        Joint::Joint(const Joint & o)
        :   __name(o.__name),
            __parent(o.__parent),
            __location(o.__location),
            __rotation(o.__rotation),
            __scale(o.__scale),
            __axis(o.__axis),
            __freedom(o.__freedom),
            __children(o.__children),
            __goblinmeshs(o.__goblinmeshs),
            __multimeshs(o.__multimeshs)
        {

        }

        Joint::Joint(Joint && o) noexcept
        :   __name(x::move(o.__name)),
            __parent(x::move(o.__parent)),
            __location(x::move(o.__location)),
            __rotation(x::move(o.__rotation)),
            __scale(x::move(o.__scale)),
            __axis(x::move(o.__axis)),
            __freedom(x::move(o.__freedom)),
            __children(x::move(o.__children)),
            __goblinmeshs(x::move(o.__goblinmeshs)),
            __multimeshs(x::move(o.__multimeshs))
        {

        }

        Joint::~Joint()
        {

        }

        Joint & Joint::operator=(const Joint & o)
        {
            if(&o != this)
            {
                __name = o.__name;
                __parent = o.__parent;
                __location = o.__location;
                __rotation = o.__rotation;
                __scale = o.__scale;
                __axis = o.__axis;
                __freedom = o.__freedom;
                __children = o.__children;
                __goblinmeshs = o.__goblinmeshs;
                __multimeshs = o.__multimeshs;
            }
            return *this;
        }

        Joint & Joint::operator=(Joint && o) noexcept
        {
            if(&o != this)
            {
                __name = x::move(o.__name);
                __parent = x::move(o.__parent);
                __location = x::move(o.__location);
                __rotation = x::move(o.__rotation);
                __scale = x::move(o.__scale);
                __axis = x::move(o.__axis);
                __freedom = x::move(o.__freedom);
                __children = x::move(o.__children);
                __goblinmeshs = x::move(o.__goblinmeshs);
                __multimeshs = x::move(o.__multimeshs);
            }
            return *this;
        }

        Homeworld2::Graphics::Objects::Joint * Joint::build(x::array<x::graphics::texture> & textures, x::array<Material> & materials)
        {
            Homeworld2::Graphics::Objects::Joint * joint = new Homeworld2::Graphics::Objects::Joint(__name, __location, __rotation, __scale, __axis);

            __goblinmeshs.each([joint, &textures, &materials](x::var<Homeworld2::Graphics::Goblinmesh *>::type & goblinmesh){
                joint->dock(goblinmesh->build(textures, materials));
            });

            __multimeshs.each([joint, &textures, &materials](x::var<Homeworld2::Graphics::Multimesh *>::type & multimesh){
                joint->dock(multimesh->build(textures, materials));
            });

            __children.each([joint, &textures, &materials](x::var<Homeworld2::Graphics::Joint *>::type & child){
                joint->add(child->build(textures, materials));
            });

            return joint;
        }
    }
}
