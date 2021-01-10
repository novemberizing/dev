#ifndef   __X_SPACE_OBJECTS_RADARS__UNIT__HH__
#define   __X_SPACE_OBJECTS_RADARS__UNIT__HH__

#include <x/graphics/object.hh>
#include <x/graphics/application.hh>

#include <x/Space/Object.hh>

namespace xSpace
{
    namespace Objects
    {
        namespace Radars
        {
            class Unit : public x::graphics::object
            {
            public:     class Color
                        {
                        public:     static x::reality::color Red;
                        public:     static x::reality::color Blue;
                        public:     static x::reality::color Green;
                        public:     static x::reality::color Grayscale;
                        };
            protected:  xSpace::Object * __unit;
            protected:  x::graphics::reference * __reference;
            protected:  x::graphics::program * __program;
            protected:  x::graphics::texture * __texture;
            protected:  x::real __x;
            protected:  x::real __y;
            protected:  x::real __width;
            protected:  x::real __height;
            protected:  x::reality::matrix __model;
            public:     virtual void start(const x::reality::matrix & model, const x::reality::camera & camera, x::real width, x::real height);
            public:     virtual void update(const x::reality::matrix & model, const x::reality::camera & camera, x::real width, x::real height);
            public:     void render(const x::reality::vector & eye) override;
            public:     x::boolean bind(const x::string & name, x::uint32 id) override;
            public:     virtual x::boolean mousemove(x::int32 x, x::int32 y, x::real width, x::real height);
            public:     virtual x::boolean mouse(x::int32 button, x::int32 state, x::int32 x, x::int32 y, x::real width, x::real height);
            public:     xSpace::Objects::Radars::Unit & operator=(const xSpace::Objects::Radars::Unit & o) = delete;
            public:     xSpace::Objects::Radars::Unit & operator=(xSpace::Objects::Radars::Unit && o) noexcept = delete;
            public:     Unit(xSpace::Object * unit);
            public:     Unit() = delete;
            public:     Unit(const xSpace::Objects::Radars::Unit & o) = delete;
            public:     Unit(xSpace::Objects::Radars::Unit && o) noexcept = delete;
            public:     ~Unit() override;
            };
        }
    }
}

#endif // __X_SPACE_OBJECTS_RADARS__UNIT__HH__
