#ifndef   __PIONEER__WORLD__HH__
#define   __PIONEER__WORLD__HH__

#include <x/graphics/layer.hh>

namespace Pioneer
{
    class World : public x::graphics::layer
    {
    public:     World & operator=(const World & o) = delete;
    public:     World & operator=(World && o) noexcept = delete;
    public:     World(const x::string & name);
    public:     World() = delete;
    public:     World(const World & o) = delete;
    public:     World(World && o) noexcept = delete;
    public:     virtual ~World();
    };
}

#endif // __PIONEER__WORLD__HH__
