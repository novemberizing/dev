#ifndef   __X_GRAPHICS__SURFACE__HH__
#define   __X_GRAPHICS__SURFACE__HH__

#include <x/graphics/color.hh>
#include <x/graphics/object.hh>
#include <x/graphics/light.hh>
#include <x/graphics/camera.hh>
#include <x/graphics/matrix.hh>
#include <x/graphics/reference.hh>
#include <x/graphics/projection.hh>

namespace x
{
    namespace graphics
    {
        class surface
        {
        protected:  x::graphics::color __background;
        protected:  x::map<x::string, x::graphics::reference> __objects;
        protected:  x::graphics::light __light;
        protected:  x::graphics::camera __camera;
        protected:  x::graphics::projection __projection;
        public:     virtual void refresh();
        public:     virtual x::graphics::reference & reference(const x::string & name);
        public:     virtual void exec(const x::array<x::string> & strings);
        public:     inline const x::graphics::projection & projection() const { return __projection; }
        public:     inline x::graphics::projection & projection() { return __projection; }
        public:     inline const x::graphics::camera & camera() const { return __camera; }
        public:     inline x::graphics::camera & camera() { return __camera; }
        public:     inline const x::graphics::light & light() const { return __light; }
        public:     inline x::graphics::light & light() { return __light; }
        public:     inline void add(const x::string & name, x::graphics::object * o)
                    {
                        __objects.put(name, x::graphics::reference(name, o));
                    }
        public:     inline void add(const x::graphics::reference & o)
                    {
                        __objects.put(o.name(), o);
                    }
        public:     inline void add(x::graphics::reference && o)
                    {
                        __objects.put(o.name(), x::move(o));
                    }
        public:     inline x::map<x::string, x::graphics::reference> & objects() { return __objects; }
        public:     inline const x::graphics::color & background() const { return __background; }
        public:     surface & operator=(const surface & o);
        public:     surface & operator=(surface && o) noexcept;
        public:     surface(x::float32 aspect);
        public:     surface();
        public:     surface(const surface & o);
        public:     surface(surface && o) noexcept;
        public:     virtual ~surface();
        };
    }
}

#endif // __X_GRAPHICS__SURFACE__HH__
