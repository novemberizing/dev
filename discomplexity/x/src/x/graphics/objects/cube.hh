#ifndef   __X_GRAPHICS_OBJECTS__CUBE__HH__
#define   __X_GRAPHICS_OBJECTS__CUBE__HH__

#include <x/graphics/primitive.hh>

#include <x/console.hh>

namespace x
{
    namespace graphics
    {
        namespace objects
        {
            class cube : public x::graphics::primitive
            {
            public:     void render(const x::graphics::matrix & model, x::uint32 level) override;
            public:     cube & operator=(const cube & o);
            public:     cube & operator=(cube && o) noexcept;
            public:     cube(const x::string & name);
            public:     cube(x::string && name);
            public:     cube();
            public:     cube(const cube & o);
            public:     cube(cube && o) noexcept;
            public:     ~cube() override;
            };
        }
    }
}

#endif // __X_GRAPHICS_OBJECTS__CUBE__HH__
