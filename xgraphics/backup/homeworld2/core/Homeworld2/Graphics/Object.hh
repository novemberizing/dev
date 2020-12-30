#ifndef   __HOMEWORLD2_GRAPHICS__OBJECT__HH__
#define   __HOMEWORLD2_GRAPHICS__OBJECT__HH__

#include <x/map.hh>
#include <x/graphics/object.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Object : public x::graphics::object
        {
        protected:  x::map<x::string, Object *> __objects;
        protected:  x::array<x::graphics::reference *> __references;
        public:     inline void add(Object * o)
                    {
                        __objects.put(o->name(), o);
                    }
        public:     inline void add(x::graphics::reference * reference)
                    {
                        __references.append(reference);
                    }
        public:     void render(const x::reality::matrix & model) override;
        public:     Object & operator=(const Object & o) = delete;
        public:     Object & operator=(Object && o) noexcept;
        public:     Object(const x::string & name, const x::reality::vector & location, const x::reality::vector & rotation, x::reality::vector & scale, x::reality::vector & axis);
        public:     Object();
        public:     Object(const Object & o) = delete;
        public:     Object(Object && o) noexcept;
        public:     ~Object();
        };
    }
}

// protected:  x::string __name;
// protected:  x::string __parent;
// protected:  x::reality::vector __location;
// protected:  x::reality::vector __rotation;
// protected:  x::reality::vector __scale;
// protected:  x::reality::vector __axis;

#endif // __HOMEWORLD2_GRAPHICS__OBJECT__HH__
