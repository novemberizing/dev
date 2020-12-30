#ifndef   __HOMEWORLD2_GRAPHICS__SINGLEMESH__H__
#define   __HOMEWORLD2_GRAPHICS__SINGLEMESH__H__

#include <x/graphics/reference.hh>
#include <Homeworld2/Graphics/Primitive.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Singlemesh : public x::graphics::reference
        {
        protected:  x::uint32 __index;
        protected:  x::uint32 __level;
        public:     x::array<Primitive *> children;
        public:     inline void push(Primitive * o)
                    {
                        if(o)
                        {
                            children.push(o);
                        }
                    }
        public:     inline void level(x::uint32 v){ __level = v; }
        public:     inline x::uint32 level() const { return __level; }
        public:     void load() override;
        public:     void unload() override;
        public:     void render(const x::reality::matrix & model) override;
        public:     Singlemesh & operator=(const Singlemesh & o);
        public:     Singlemesh & operator=(Singlemesh && o) noexcept;
        public:     Singlemesh();
        public:     Singlemesh(const Singlemesh & o);
        public:     Singlemesh(Singlemesh && o) noexcept;
        public:     ~Singlemesh();
        };
    }
}

#endif // __HOMEWORLD2_GRAPHICS__SINGLEMESH__H__'
