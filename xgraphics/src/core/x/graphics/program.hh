#ifndef   __X_GRAPHICS__PROGRAM__HH__
#define   __X_GRAPHICS__PROGRAM__HH__

#include <x/graphics/shader.hh>
#include <x/map.hh>
#include <x/array.hh>

namespace x
{
    namespace graphics
    {
        class program
        {
        protected:  x::string __name;
        protected:  x::uint32 __id;
        protected:  x::array<x::graphics::shader> __shaders;
        public:     x::map<x::string, x::uint32> uniforms;
        public:     inline const x::string & name() const { return __name; }
        public:     inline x::uint32 id() const { return __id; }
        public:     inline void id(x::uint32 v){ __id = v; }
        public:     inline const x::array<x::graphics::shader> & shaders() const { return __shaders; }
        public:     inline x::array<x::graphics::shader> & shaders() { return __shaders; }

        public:     inline void add(const x::graphics::shader & shader){ __shaders.append(shader); }
        public:     inline void add(x::graphics::shader && shader){ __shaders.append(x::move(shader)); }
        public:     inline void add(const x::string & uniform){ uniforms.put(uniform, x::invalid); }
        // public:     inline void add(const x::string & uniform){ __uniforms.put(uniform, x::invalid); }
        public:     x::graphics::program & operator=(const x::graphics::program & o);
        public:     x::graphics::program & operator=(x::graphics::program && o) noexcept;
        public:     program(const x::string & name, const x::initializer<x::graphics::shader> & list, const x::initializer<x::string> & uniforms);
        public:     program(x::string && name, const x::initializer<x::graphics::shader> & list, const x::initializer<x::string> & uniforms);
        public:     program(const x::string & name, const x::initializer<x::graphics::shader> & list);
        public:     program(x::string && name, const x::initializer<x::graphics::shader> & list);
        public:     program(const x::string & name);
        public:     program(x::string && name);
        public:     program(const x::string & name, const x::initializer<x::string> & uniforms);
        public:     program(x::string && name, const x::initializer<x::string> & uniforms);
        public:     program();
        public:     program(const x::graphics::program & o);
        public:     program(x::graphics::program && o) noexcept;
        public:     virtual ~program();
        };
    }
}

#endif // __X_GRAPHICS__PROGRAM__HH__
