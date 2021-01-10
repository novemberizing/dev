#ifndef   __X_GRAPHICS_OBJECTS__JOINT__HH__
#define   __X_GRAPHICS_OBJECTS__JOINT__HH__

#include <x/graphics/object.hh>

namespace x
{
    namespace graphics
    {
        namespace objects
        {
            class joint : public x::graphics::object
            {
            protected:  x::reality::vector __location;
            protected:  x::reality::vector __rotation;
            protected:  x::reality::vector __scale;
            protected:  x::reality::vector __axis;
            protected:  x::reality::matrix __model;
            protected:  x::array<x::graphics::objects::joint *> __children;
            protected:  x::array<x::graphics::object *> __objects;
            public:     virtual void add(x::graphics::objects::joint * o);
            public:     virtual void dock(x::graphics::object * o);
            public:     void start(const x::reality::matrix & model, const x::reality::vector & center) override;
            public:     void update(const x::reality::matrix & model, const x::reality::vector & center) override;
            public:     void render(const x::reality::vector & position, const x::reality::vector & center) override;
            public:     joint(const x::reality::vector & location, const x::reality::vector & rotation, const x::reality::vector & scale, const x::reality::vector & axis);
            public:     ~joint() override;
            public:     x::graphics::objects::joint & operator=(const x::graphics::objects::joint & o) = delete;
            public:     x::graphics::objects::joint & operator=(x::graphics::objects::joint && o) noexcept = delete;
            public:     joint() = delete;
            public:     joint(const x::graphics::objects::joint & o) = delete;
            public:     joint(x::graphics::objects::joint && o) noexcept = delete;
            };
        }
    }
}

#endif // __X_GRAPHICS_OBJECTS__JOINT__HH__
