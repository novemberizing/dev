#ifndef   __HOMEWORLD2_GRAPHICS__JOINT__HH__
#define   __HOMEWORLD2_GRAPHICS__JOINT__HH__

#include <x/console.hh>
#include <x/reality/vector.hh>
#include <x/graphics/object.hh>

#include <Homeworld2/Graphics/Object.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Joint
        {
        protected:  x::string __name;
        protected:  x::string __parent;
        protected:  x::reality::vector __location;
        protected:  x::reality::vector __rotation;
        protected:  x::reality::vector __scale;
        protected:  x::reality::vector __axis;
        protected:  x::reality::vector __freedom;
        protected:  x::array<x::graphics::reference *> __references;
        protected:  x::array<Joint *> __children;
        protected:  x::reality::matrix __model; // MAYBE NOT USED
        public:     inline x::array<x::graphics::reference *> & references() { return __references; }
        public:     virtual Object * build();
        // public:     virtual Graphics::Reference * build(const x::string & name);
        public:     inline void add(Joint * joint)
                    {
                        if(joint)
                        {
                            __children.append(joint);
                        }
                    }
        public:     inline void add(x::graphics::reference * o)
                    {
                        if(o)
                        {
                            __references.append(o);
                        }
                    }
        public:     inline const x::reality::matrix & model() const { return __model; }
        public:     inline x::reality::matrix & model() { return __model; }
        public:     inline const x::string & name() const { return __name; }
        public:     inline const x::string & parent() const { return __parent; }
        public:     inline void name(const x::string & v) { __name = v; }
        public:     inline void name(x::string && v) { __name = x::move(v); }
        public:     inline void parent(const x::string & v) { __parent = v; }
        public:     inline void parent(x::string && v) { __parent = x::move(v); }
        public:     inline const x::reality::vector & location() const { return __location; }
        public:     inline x::reality::vector & location() { return __location; }
        public:     inline void location(x::float32 x, x::float32 y, x::float32 z)
                    {
                        __location.x(x);
                        __location.y(y);
                        __location.z(z);
                    }
        public:     inline void location(const x::reality::vector & o){ __location = o; }
        public:     inline void location(x::reality::vector && o){ __location = x::move(o); }
        public:     inline const x::reality::vector & rotation() const { return __rotation; }
        public:     inline x::reality::vector & rotation() { return __rotation; }
        public:     inline void rotation(x::float32 x, x::float32 y, x::float32 z)
                    {
                        __rotation.x(x);
                        __rotation.y(y);
                        __rotation.z(z);
                    }
        public:     inline void rotation(const x::reality::vector & o) { __rotation = o; }
        public:     inline void rotation(x::reality::vector && o) { __rotation = x::move(o); }
        public:     inline const x::reality::vector & scale() const { return __scale; }
        public:     inline x::reality::vector & scale() { return __scale; }
        public:     inline void scale(x::float32 x, x::float32 y, x::float32 z)
                    {
                        __scale.x(x);
                        __scale.y(y);
                        __scale.z(z);
                    }
        public:     inline const x::reality::vector & axis() const { return __axis; }
        public:     inline x::reality::vector & axis() { return __axis; }
        public:     inline void axis(x::float32 x, x::float32 y, x::float32 z)
                    {
                        __axis.x(x);
                        __axis.y(y);
                        __axis.z(z);
                    }
        public:     inline void axis(const x::reality::vector & o) { __axis = o; }
        public:     inline void axis(x::reality::vector && o) { __axis = x::move(o); }
        public:     inline void freedom(x::float32 x, x::float32 y, x::float32 z)
                    {
                        __freedom.x(x);
                        __freedom.y(y);
                        __freedom.z(z);
                    }
        // public:     virtual void exec(const x::array<x::string> & strings, x::uint64 index);
        public:     Joint & operator=(const Joint & o);
        public:     Joint & operator=(Joint && o) noexcept;
        public:     Joint();
        public:     Joint(const Joint & o);
        public:     Joint(Joint && o) noexcept;
        public:     virtual ~Joint();
        };
    }
}

#endif // __HOMEWORLD2_GRAPHICS__JOINT__HH__
