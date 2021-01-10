#ifndef   __X_GRAPHICS__PROGRAM__HH__
#define   __X_GRAPHICS__PROGRAM__HH__

#include <x/graphics/shader.hh>

namespace x
{
    namespace graphics
    {
        class program
        {
        protected:  x::string __name;
        protected:  x::uint32 __id;
        protected:  x::array<x::graphics::shader> __shaders;
        protected:  x::map<x::string, x::uint32> __uniforms;
        public:     inline const x::string & name() const { return __name; }
        public:     inline x::uint32 id() const { return __id; }
        public:     inline void id(x::uint32 v){ __id = v; }
        public:     inline const x::array<x::graphics::shader> & shaders() const { return __shaders; }
        public:     inline x::array<x::graphics::shader> & shaders() { return __shaders; }
        public:     inline x::map<x::string, x::uint32> & uniforms(){ return __uniforms; }
        public:     program & operator=(const program & o);
        public:     program & operator=(program && o) noexcept;
        public:     program(const x::string & name, const x::initializer<x::graphics::shader> & list, const x::initializer<x::string> & uniforms);
        public:     program(x::string && name, const x::initializer<x::graphics::shader> & list, const x::initializer<x::string> & uniforms);
        public:     program(const x::string & name, const x::initializer<x::graphics::shader> & list);
        public:     program(x::string && name, const x::initializer<x::graphics::shader> & list);
        public:     program();
        public:     program(const program & o);
        public:     program(program && o) noexcept;
        public:     virtual ~program();
        };
    }
}

#endif // __X_GRAPHICS__PROGRAM__HH__
