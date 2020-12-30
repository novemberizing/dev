#ifndef   __PIONEER__MAP__HH__
#define   __PIONEER__MAP__HH__

namespace Pioneer
{
    class Map
    {
    public:     Pioneer::Map & operator=(const Pioneer::Map & o);
    public:     Pioneer::Map & operator=(Pioneer::Map && o) noexcept;
    public:     Map();
    public:     Map(const Pioneer::Map & o);
    public:     Map(Pioneer::Map && o) noexcept;
    public:     virtual ~Map();
    };
}

#endif // __PIONEER__MAP__HH__
