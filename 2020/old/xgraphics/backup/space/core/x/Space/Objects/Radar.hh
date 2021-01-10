#ifndef   __X_SPACE_OBJECTS__RADAR__HH__
#define   __X_SPACE_OBJECTS__RADAR__HH__

#include <x/list.hh>

#include <x/graphics/object.hh>
#include <x/graphics/objects/simple.hh>
#include <x/graphics/application.hh>

#include <x/Space/Objects/Radars/Unit.hh>

namespace xSpace
{
    namespace Objects
    {
        class Radar : public x::graphics::object
        {
        protected:  x::string __name;
        protected:  x::real __x;
        protected:  x::real __y;
        protected:  x::real __width;
        protected:  x::real __height;
        protected:  x::graphics::reference * __reference;
        protected:  x::graphics::program * __program;
        protected:  x::graphics::texture * __texture;
        protected:  x::reality::matrix __model;
        protected:  x::array<xSpace::Objects::Radars::Unit *> __units;
        public:     inline void add(xSpace::Objects::Radars::Unit * unit){ __units.append(unit); }
        public:     void start(const x::reality::matrix & model, const x::reality::camera & camera) override;
        public:     void update(const x::reality::matrix & model, const x::reality::camera & camera) override;
        public:     void render(const x::reality::vector & eye) override;
        public:     x::boolean mousemove(x::int32 x, x::int32 y) override;
        public:     x::boolean mouse(x::int32 button, x::int32 state, x::int32 x, x::int32 y) override;
        public:     x::boolean bind(const x::string & name, x::uint32 id) override;
        public:     const x::string & name() const override { return __name; }
        // public:     virtual const x::reality::vector & position() const { return x::reality::vector::center; }
        // public:     virtual const x::reality::vector & front() const { return x::reality::vector::front; }
        // public:     virtual const x::reality::vector & up() const { return x::reality::vector::up; }
        public:     xSpace::Objects::Radar & operator=(const xSpace::Objects::Radar & o) = delete;
        public:     xSpace::Objects::Radar & operator=(xSpace::Objects::Radar && o) noexcept = delete;
        public:     Radar(const x::string & name);
        public:     Radar() = delete;
        public:     Radar(const xSpace::Objects::Radar & o) = delete;
        public:     Radar(xSpace::Objects::Radar && o) noexcept = delete;
        public:     ~Radar() override;
        };
    }
}

#endif // __X_SPACE_OBJECTS__RADAR__HH__
