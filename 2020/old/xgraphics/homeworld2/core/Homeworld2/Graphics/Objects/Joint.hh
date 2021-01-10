#ifndef   __HOMEWORLD2_GRAPHICS_OBJECTS__JOINT__HH__
#define   __HOMEWORLD2_GRAPHICS_OBJECTS__JOINT__HH__

#include <x/graphics/objects/joint.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        namespace Objects
        {
            class Joint : public x::graphics::objects::joint
            {
            protected:  x::string __name;
            public:     const x::string & name() const override { return __name; }
            public:     void start(const x::reality::matrix & model, const x::reality::vector & center) override;
            public:     void update(const x::reality::matrix & model, const x::reality::vector & center) override;
            public:     void render(const x::reality::vector & position, const x::reality::vector & center) override;
            public:     Joint(const x::string & name, const x::reality::vector & location, const x::reality::vector & rotation, const x::reality::vector & scale, const x::reality::vector & axis);
            public:     ~Joint() override;
            public:     Homeworld2::Graphics::Objects::Joint & operator=(const Homeworld2::Graphics::Objects::Joint & o) = delete;
            public:     Homeworld2::Graphics::Objects::Joint & operator=(Homeworld2::Graphics::Objects::Joint && o) noexcept = delete;
            public:     Joint() = delete;
            public:     Joint(const Homeworld2::Graphics::Objects::Joint & o) = delete;
            public:     Joint(Homeworld2::Graphics::Objects::Joint && o) noexcept = delete;
            };
        }
    }
}

#endif // __HOMEWORLD2_GRAPHICS_OBJECTS__JOINT__HH__
