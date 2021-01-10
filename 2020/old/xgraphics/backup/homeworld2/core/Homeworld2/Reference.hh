#ifndef   __HOMEWORLD2__REFERENCE__HH__
#define   __HOMEWORLD2__REFERENCE__HH__

#include <Homeworld2/Graphics/Reference.hh>
#include <Homeworld2/Physics/Reference.hh>

namespace Homeworld2
{
    class Reference : public x::graphics::reference,
                      public x::physics::reference
    {
    protected:  Homeworld2::Graphics::Reference * __graphics;
    protected:  Homeworld2::Physics::Reference * __physics;
    public:     void load() override;
    public:     void unload() override;
    public:     void render(const x::reality::matrix & model) override;
    public:     const x::real weight() const override;
    public:     void weight(x::real v) override;
    public:     const x::real energy() const override;
    public:     void energy(x::real v) override;
    public:     Homeworld2::Reference & operator=(const Homeworld2::Reference & o) = delete;
    public:     Homeworld2::Reference & operator=(Homeworld2::Reference && o) noexcept = delete;
    public:     Reference(const x::string & name, Homeworld2::Graphics::Reference * graphics, Homeworld2::Physics::Reference * physics);
    public:     Reference() = delete;
    public:     Reference(const Homeworld2::Reference & o) = delete;
    public:     Reference(Homeworld2::Reference && o) noexcept = delete;
    public:     ~Reference() override;
    };
}

#endif // __HOMEWORLD2__REFERENCE__HH__
