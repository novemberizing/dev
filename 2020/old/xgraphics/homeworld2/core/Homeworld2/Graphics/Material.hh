#ifndef   __HOMEWORLD2_GRAPHICS__MATERIAL__HH__
#define   __HOMEWORLD2_GRAPHICS__MATERIAL__HH__

#include <x/map.hh>
#include <x/string.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Material
        {
        protected:  x::string __name;
        protected:  x::string __shader;
        protected:  x::uint32 __diffuse;
        protected:  x::uint32 __glow;
        public:     inline const x::string name() const { return __name; }
        public:     inline const x::string shader() const { return __shader; }
        public:     inline x::uint32 diffuse() const { return __diffuse; }
        public:     inline x::uint32 glow() const { return __glow; }
        public:     inline void diffuse(x::uint32 v){ __diffuse = v; }
        public:     inline void glow(x::uint32 v){ __glow = v; }
        public:     inline void name(const x::string & v){ __name = v; }
        public:     inline void name(x::string && v){ __name = x::move(v); }
        public:     inline void shader(const x::string & v){ __shader = v; }
        public:     inline void shader(x::string && v){ __shader = x::move(v); }
        public:     Material & operator=(const Material & o);
        public:     Material & operator=(Material && o) noexcept;
        public:     Material();
        public:     Material(const Material & o);
        public:     Material(Material && o) noexcept;
        public:     virtual ~Material();
        };
    }
}

#endif // __HOMEWORLD2_GRAPHICS__MATERIAL__HH__
