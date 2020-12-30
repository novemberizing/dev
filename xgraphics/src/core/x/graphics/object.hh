#ifndef   __X_GRAPHICS__OBJECT__HH__
#define   __X_GRAPHICS__OBJECT__HH__

#include <x/string.hh>
#include <x/reality/matrix.hh>
#include <x/reality/object.hh>
#include <x/physics/object.hh>

#include <x/graphics/reference.hh>
#include <x/graphics/texture.hh>
#include <x/graphics/program.hh>

namespace x
{
    namespace graphics
    {
        class object : public x::physics::object
        {
        public:     virtual x::graphics::reference * graphics(){ return nullptr; }
        public:     virtual void start(const x::reality::matrix & model, const x::reality::vector & eye) {}
        public:     virtual void update(const x::reality::matrix & model, const x::reality::vector & eye) {}
        public:     virtual void render(const x::reality::vector & position, const x::reality::vector & center) {}
        public:     virtual x::boolean bind(const x::string & name, x::uint32 id) { return false; }
        protected:  object();
        public:     ~object() override;
        public:     x::graphics::object & operator=(const x::graphics::object & o) = delete;
        public:     x::graphics::object & operator=(x::graphics::object && o) noexcept = delete;
        public:     object(const x::graphics::object & o) = delete;
        public:     object(x::graphics::object && o) noexcept = delete;
        };
    }
}

#endif // __X_GRAPHICS__OBJECT__HH__
