#ifndef   __X_GRAPHICS__REFERENCE__HH__
#define   __X_GRAPHICS__REFERENCE__HH__

#include <x/string.hh>
#include <x/graphics/object.hh>
#include <x/graphics/vector.hh>
#include <x/graphics/util.hh>

namespace x
{
    namespace graphics
    {
        class reference
        {
        protected:  x::string __name;
        protected:  x::graphics::object * __object;
        protected:  x::graphics::vector __position;
        protected:  x::graphics::vector __rotation;
        protected:  x::graphics::vector __scale;
        protected:  x::graphics::matrix __model;
        protected:  x::uint32 __status;
        protected:  x::uint32 __level;
        protected:  x::map<x::string, x::graphics::reference> __children;
        public:     virtual void exec(const x::array<x::string> & strings, x::uint64 index);
        public:     inline const x::string & name() const { return __name; }
        public:     inline x::uint32 level() { return __object->level(); }
        public:     virtual void refresh();
        // public:     virtual void refresh(const x::graphics::matrix & model);
        public:     virtual void render();
        public:     virtual void render(const x::graphics::matrix & model, x::uint32 level);
        public:     virtual void start();
        public:     virtual void update();
        public:     reference & operator=(const reference & o);
        public:     reference & operator=(reference && o) noexcept;
        public:     reference(const x::string & name, x::graphics::object * object);
        public:     reference(x::string && name, x::graphics::object * object);
        public:     reference();
        public:     reference(const reference & o);
        public:     reference(reference && o) noexcept;
        public:     virtual ~reference();
        };
    }
}

#endif // __X_GRAPHICS__REFERENCE__HH__
