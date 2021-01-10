#ifndef   __X_GRAPHICS__REFERENCE__HH__
#define   __X_GRAPHICS__REFERENCE__HH__

#include <x/physics/reference.hh>
#include <x/reality/matrix.hh>

namespace x
{
    namespace graphics
    {
        class reference : public x::physics::reference
        {
        public:     virtual void load() = 0;
        public:     virtual void unload() = 0;
        public:     virtual void render() = 0;
        public:     x::graphics::reference & operator=(const x::graphics::reference & o) = delete;
        public:     x::graphics::reference & operator=(x::graphics::reference && o) noexcept = delete;
        public:     reference();
        public:     reference(const x::graphics::reference & o) = delete;
        public:     reference(x::graphics::reference && o) noexcept = delete;
        public:     ~reference() override;
        };
    }
}

#endif // __X_GRAPHICS__REFERENCE__HH__
