#ifndef   __X_GRAPHICS__COMPLEX__HH__
#define   __X_GRAPHICS__COMPLEX__HH__

#include <x/graphics/object.hh>

namespace x
{
    namespace graphics
    {
        class complex : public object
        {
        protected:  x::array<x::graphics::object *> __children;
        // public:     void level(x::uint32 v) override;
        public:     inline void push(x::graphics::object * o)
                    {
                        if(o)
                        {
                            __children.push(o);
                        }
                    }
        public:     void status(x::uint32 v) override;
        public:     void load() override;
        public:     void unload() override;
        public:     void render(const x::graphics::matrix & model, x::uint32 level) override;
        public:     complex & operator=(const complex & o);
        public:     complex & operator=(complex && o) noexcept;
        public:     complex();
        public:     complex(const complex & o);
        public:     complex(complex && o) noexcept;
        public:     ~complex() override;
        };
    }
}

#endif // __X_GRAPHICS__COMPLEX__HH__
