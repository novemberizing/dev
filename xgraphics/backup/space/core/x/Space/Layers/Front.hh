#ifndef   __X_SPACE_LAYERS__FRONT__HH__
#define   __X_SPACE_LAYERS__FRONT__HH__

#include <x/graphics/layer.hh>

namespace xSpace
{
    namespace Layers
    {
        class Front : public x::graphics::layer
        {
        public:     xSpace::Layers::Front & operator=(const xSpace::Layers::Front & o) = delete;
        public:     xSpace::Layers::Front & operator=(xSpace::Layers::Front && o) noexcept = delete;
        public:     Front(const x::string & name);
        public:     Front() = delete;
        public:     Front(const xSpace::Layers::Front & o) = delete;
        public:     Front(xSpace::Layers::Front && o) noexcept = delete;
        public:     ~Front() override;
        };
    }
}

#endif // __X_SPACE_LAYERS__FRONT__HH__
