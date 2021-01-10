#ifndef   __X_SPACE__OBJECT__HH__
#define   __X_SPACE__OBJECT__HH__

#include <x/graphics/object.hh>

namespace xSpace
{
    class Object : public x::graphics::object
    {
    protected:  x::string __name;
    protected:  x::graphics::object * __graphics;
    protected:  x::string __relationship;
    public:     xSpace::Object & operator=(const xSpace::Object & o) = delete;
    public:     xSpace::Object & operator=(xSpace::Object && o) noexcept = delete;
    public:     Object(const x::string & name, x::graphics::object * graphics, const x::string & relationship);
    public:     Object() = delete;
    public:     Object(const xSpace::Object & o) = delete;
    public:     Object(xSpace::Object && o) noexcept = delete;
    public:     ~Object() override;
    };
}

#endif // __X_SPACE__OBJECT__HH__
