#ifndef   __HOMEWORLD2_GRAPHICS_OBJECTS__ROOT__HH__
#define   __HOMEWORLD2_GRAPHICS_OBJECTS__ROOT__HH__

#include <x/graphics/objects/root.hh>

#include <Homeworld2/Graphics/Objects/Joint.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        namespace Objects
        {
            class Root : public x::graphics::objects::root
            {
            protected:  x::graphics::reference * __reference;
            public:     x::graphics::reference * graphics(){ return __reference; }
            public:     x::physics::reference * physics(){ return __reference; }
            public:     x::reality::reference * reality(){ return __reference; }
            public:     x::real mass() const override { return __reference->mass(); }
            public:     Root(x::graphics::reference * reference, Homeworld2::Graphics::Objects::Joint * root);
            public:     ~Root() override;
            public:     Root() = delete;
            public:     Root(const Homeworld2::Graphics::Objects::Root & o) = delete;
            public:     Root(Homeworld2::Graphics::Objects::Root && o) noexcept = delete;
            public:     Homeworld2::Graphics::Objects::Root & operator=(const Homeworld2::Graphics::Objects::Root & o) = delete;
            public:     Homeworld2::Graphics::Objects::Root & operator=(Homeworld2::Graphics::Objects::Root && o) noexcept = delete;
            };
        }
    }
}

#endif // __HOMEWORLD2_GRAPHICS_OBJECTS__ROOT__HH__
