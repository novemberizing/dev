#ifndef   __X_GRAPHICS__OBJECT__HH__
#define   __X_GRAPHICS__OBJECT__HH__

#include <x/graphics/vector.hh>
#include <x/graphics/matrix.hh>

namespace x
{
    namespace graphics
    {
        class object
        {
        protected:  x::string __name;
        protected:  x::uint32 __status;
        protected:  x::uint32 __level;
        public:     virtual x::uint32 level() const { return __level; }
        public:     virtual void level(x::uint32 v) { __level = v; }
        public:     virtual x::uint32 status() const { return __status; }
        public:     virtual void status(x::uint32 v){ __status = v; }
        public:     inline void name(const x::string & v) { __name = v; }
        public:     inline void name(x::string && v) { __name = x::move(v); }
        public:     inline const x::string & name() const { return __name; }
        public:     virtual void exec(const x::array<x::string> & strings, x::uint64 index);
        public:     virtual void load();
        public:     virtual void unload();
        public:     virtual void render(const x::graphics::matrix & model, x::uint32 level);
        public:     virtual void refresh(const x::graphics::matrix & model);
        public:     object & operator=(const object & o);
        public:     object & operator=(object && o) noexcept;
        public:     object(const x::string & name);
        public:     object(x::string && name);
        public:     object();
        public:     object(const object & o);
        public:     object(object && o) noexcept;
        public:     virtual ~object();
        };
    }
}

#endif // __X_GRAPHICS__OBJECT__HH__
