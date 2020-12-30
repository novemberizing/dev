#ifndef   __X_SPACE__LAYER__HH__
#define   __X_SPACE__LAYER__HH__

#include <x/graphics/layer.hh>

namespace xSpace
{
    class Layer : public x::graphics::layer
    {
    public:     Layer(const x::string & name);
    public:     virtual ~Layer();
    public:     xSpace::Layer & operator=(const xSpace::Layer & o) = delete;
    public:     xSpace::Layer & operator=(xSpace::Layer && o) noexcept = delete;
    public:     Layer() = delete;
    public:     Layer(const xSpace::Layer & o) = delete;
    public:     Layer(xSpace::Layer && o) noexcept = delete;
    };
}

#endif // __X_SPACE__LAYER__HH__
