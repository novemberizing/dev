#ifndef   __X_GRAPHICS__LIGHT__HH__
#define   __X_GRAPHICS__LIGHT__HH__

#include <x/reality/vector.hh>
#include <x/reality/color.hh>
#include <x/console.hh>

namespace x
{
    namespace reality
    {
        class light
        {
        protected:  static x::reality::light __main;
        public:     static x::reality::light & main()
                    {
                        return __main;
                    }
        protected:  x::reality::vector __location;
        protected:  x::reality::color __color;
        protected:  x::real __ambient;
        public:     virtual void exec(const x::array<x::string> & strings, x::uint64 index);
        public:     inline x::float32 ambient() const { return __ambient; }
        public:     inline x::reality::color & color() { return __color; }
        public:     inline const x::reality::color & color() const { return __color; }
        public:     inline x::reality::vector & location() { return __location; }
        public:     inline const x::reality::vector & location() const { return __location; }
        public:     x::reality::light & operator=(const x::reality::light & o);
        public:     x::reality::light & operator=(x::reality::light && o) noexcept;
        public:     light(const x::initializer<x::real> & location, const x::initializer<x::real> & color, x::real ambient);
        public:     light();
        public:     light(const x::reality::light & o);
        public:     light(x::reality::light && o) noexcept;
        public:     virtual ~light();
        };
    }
}

#endif // __X_GRAPHICS__LIGHT__HH__
