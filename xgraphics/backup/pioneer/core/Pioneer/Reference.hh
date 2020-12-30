#ifndef   __PIONEER__REFERENCE__HH__
#define   __PIONEER__REFERENCE__HH__

namespace Pioneer
{
    class Reference : public x::graphics::reference,
                      public x::physics::reference
    {
    public:     Pioneer::Reference & operator=(const Pioneer::Reference & o) = delete;
    public:     Pioneer::Reference & operator=(Pioneer::Reference && o) noexcept = delete;
    public:     Reference();
    public:     Reference(const Pioneer::Reference & o) = delete;
    public:     Reference(Pioneer::Reference && o) noexcept = delete;
    public:     virtual ~Reference();
    };
}

#endif // __PIONEER__REFERENCE__HH__
