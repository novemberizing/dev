#ifndef   __HOMEWORLD2__JOINT__H__
#define   __HOMEWORLD2__JOINT__H__

#include <x/console.hh>
#include <x/graphics/vector.hh>
#include <x/graphics/object.hh>

namespace Homeworld2
{
    class Joint
    {
    protected:  x::string __name;
    protected:  x::string __parent;
    protected:  x::graphics::vector __position;
    protected:  x::graphics::vector __rotation;
    protected:  x::graphics::vector __scale;
    protected:  x::graphics::vector __axis;
    protected:  x::graphics::vector __freedom;
    protected:  x::array<x::graphics::object *> __objects;
    protected:  x::array<Joint *> __children;
    protected:  x::graphics::matrix __model;
    public:     virtual x::graphics::matrix axis(const x::graphics::matrix & model);
    public:     virtual void refresh(const x::graphics::matrix & model);
    public:     virtual void render(const x::graphics::matrix & model, x::uint32 level);
    public:     inline x::array<x::graphics::object *> & objects() { return __objects; }
    public:     inline void add(Joint * joint)
                {
                    if(joint)
                    {
                        __children.add(joint);
                    }
                }
    public:     inline void add(x::graphics::object * o)
                {
                    if(o)
                    {
                        __objects.add(o);
                    }
                }
    public:     inline const x::string & name() const { return __name; }
    public:     inline const x::string & parent() const { return __parent; }
    public:     inline void name(const x::string & v) { __name = v; }
    public:     inline void name(x::string && v) { __name = x::move(v); }
    public:     inline void parent(const x::string & v) { __parent = v; }
    public:     inline void parent(x::string && v) { __parent = x::move(v); }
    public:     inline const x::graphics::vector & position() const { return __position; }
    public:     inline x::graphics::vector & position() { return __position; }
    public:     inline void position(x::float32 x, x::float32 y, x::float32 z)
                {
                    __position.x(x);
                    __position.y(y);
                    __position.z(z);
                }
    public:     inline void position(const x::graphics::vector & o){ __position = o; }
    public:     inline void position(x::graphics::vector && o){ __position = x::move(o); }
    public:     inline const x::graphics::vector & rotation() const { return __rotation; }
    public:     inline x::graphics::vector & rotation() { return __rotation; }
    public:     inline void rotation(x::float32 x, x::float32 y, x::float32 z)
                {
                    __rotation.x(x);
                    __rotation.y(y);
                    __rotation.z(z);
                }
    public:     inline void rotation(const x::graphics::vector & o) { __rotation = o; }
    public:     inline void rotation(x::graphics::vector && o) { __rotation = x::move(o); }
    public:     inline void scale(x::float32 x, x::float32 y, x::float32 z)
                {
                    __scale.x(x);
                    __scale.y(y);
                    __scale.z(z);
                }
    public:     inline const x::graphics::vector & axis() const { return __axis; }
    public:     inline x::graphics::vector & axis() { return __axis; }
    public:     inline void axis(x::float32 x, x::float32 y, x::float32 z)
                {
                    __axis.x(x);
                    __axis.y(y);
                    __axis.z(z);
                }
    public:     inline void axis(const x::graphics::vector & o) { __axis = o; }
    public:     inline void axis(x::graphics::vector && o) { __axis = x::move(o); }
    public:     inline void freedom(x::float32 x, x::float32 y, x::float32 z)
                {
                    __freedom.x(x);
                    __freedom.y(y);
                    __freedom.z(z);
                }
    public:     virtual void exec(const x::array<x::string> & strings, x::uint64 index);
    public:     Joint & operator=(const Joint & o);
    public:     Joint & operator=(Joint && o) noexcept;
    public:     Joint();
    public:     Joint(const Joint & o);
    public:     Joint(Joint && o) noexcept;
    public:     virtual ~Joint();
    };
}

#endif // __HOMEWORLD2__JOINT__H__
