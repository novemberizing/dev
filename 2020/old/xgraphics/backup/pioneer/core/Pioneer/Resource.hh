#ifndef   __PIONEER__RESOURCE__HH__
#define   __PIONEER__RESOURCE__HH__

namespace Pioneer
{
    class Resource
    {
    public:     static void load(){}
    public:     Resource & operator=(const Resource & o);
    public:     Resource & operator=(Resource && o) noexcept;
    public:     Resource();
    public:     Resource(const Resource & o);
    public:     Resource(Resource && o) noexcept;
    public:     virtual ~Resource();
    };
}

#endif // __PIONEER__RESOURCE__HH__
