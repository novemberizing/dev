#ifndef   __X_GRAPHICS__SHADER__HH__
#define   __X_GRAPHICS__SHADER__HH__

#include <x/graphics/type.hh>

namespace x
{
    namespace graphics
    {
        class shader
        {
        public:     static const uint32 none = 0;
        public:     static const uint32 vertex = 1;
        public:     static const uint32 fragment = 2;
        public:     static const uint32 compute = 3;
        public:     static const uint32 geometry = 4;
        public:     static const uint32 tessellation = 5;
        public:     static const uint32 control = 1;
        public:     static const uint32 evaluation = 2;
        protected:  x::string __name;
        protected:  x::uint32 __category;
        protected:  x::uint32 __type;
        protected:  x::uint32 __id;
        protected:  x::string __code;
        public:     inline const x::string & name() const { return __name; }
        public:     inline x::uint32 id() const { return __id; }
        public:     inline void id(x::uint32 v){ __id = v; }
        public:     inline x::uint32 category() const { return __category; }
        public:     inline x::uint32 type() const { return __type; }
        public:     inline const char * code() const { return __code.str(); }
        public:     shader & operator=(const shader & o);
        public:     shader & operator=(shader && o) noexcept;
        public:     shader(const x::string & name, x::uint32 category, const x::string & code);
        public:     shader(x::string && name, x::uint32 category, x::string && code);
        public:     shader();
        public:     shader(const shader & o);
        public:     shader(shader && o) noexcept;
        public:     virtual ~shader();
        };
    }
}

#endif // __X_GRAPHICS__SHADER__HH__
