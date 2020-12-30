#ifndef   __HOMEWORLD2_GRAPHICS__REFERENCE_DATA__HH__
#define   __HOMEWORLD2_GRAPHICS__REFERENCE_DATA__HH__

#include <x/graphics/reference.hh>
#include <x/graphics/texture.hh>
#include <x/physics/reference.hh>

#include <Homeworld2/Graphics/Material.hh>
#include <Homeworld2/Graphics/Texture.hh>
#include <Homeworld2/Graphics/Multimesh.hh>
#include <Homeworld2/Graphics/Goblinmesh.hh>
#include <Homeworld2/Graphics/Joint.hh>
#include <Homeworld2/Graphics/Engineshape.hh>
#include <Homeworld2/Graphics/Engineburn.hh>
#include <Homeworld2/Graphics/Navlight.hh>
#include <Homeworld2/Graphics/Marker.hh>
#include <Homeworld2/Graphics/Collision.hh>
#include <Homeworld2/Graphics/Basicmesh.hh>
#include <Homeworld2/Graphics/Engineglow.hh>
#include <Homeworld2/Graphics/Information.hh>

#include <Homeworld2/Graphics/Objects/Root.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Reference : public x::graphics::reference
        {
        protected:  static x::map<x::string, Homeworld2::Graphics::Reference *> __references;
        public:     static Homeworld2::Graphics::Reference * get(const x::string & name);
        public:     static const x::uint32 UNKNOWN     = 0x00000000U;
        public:     static const x::uint32 FORM        = 0x464F524DU;
        public:     static const x::uint32 NORMAL      = 0x4E524D4CU;
        public:     static const x::uint32 VERSION     = 0x56455253U;
        public:     static const x::uint32 CATEGORY    = 0x4E414D45U;
        public:     static const x::uint32 DATA        = 0x48564D44U;
        public:     static const x::uint32 MATERIAL    = 0x53544154U;
        public:     static const x::uint32 TEXTURE     = 0x4C4D4950U;
        public:     static const x::uint32 MULTIMESH   = 0x4D554C54U;
        public:     static const x::uint32 SINGLEMESH  = 0x424D5348U;
        public:     static const x::uint32 GOBLINMESH  = 0x474F4247U;
        public:     static const x::uint32 DETAIL      = 0x4454524DU;
        public:     static const x::uint32 JOINTS      = 0x48494552U;
        public:     static const x::uint32 ENGINESHAPE = 0x45545348U;
        public:     static const x::uint32 ENGINEBURN  = 0x4255524EU;
        public:     static const x::uint32 NAVLIGHT    = 0x4E41564CU;
        public:     static const x::uint32 MARKER      = 0x4D524B52U;
        public:     static const x::uint32 HEAD        = 0x48454144U;
        public:     static const x::uint32 KEYFRAME    = 0x4B455946U;
        public:     static const x::uint32 BOUNDARY    = 0x424E4456U;
        public:     static const x::uint32 COLLISION   = 0x434F4C44U;
        public:     static const x::uint32 BOX         = 0x42424F58U;
        public:     static const x::uint32 SPHERE      = 0x42535048U;
        public:     static const x::uint32 TRIANGLE    = 0x54524953U;
        public:     static const x::uint32 BASICMESH   = 0x4253524DU;
        public:     static const x::uint32 DESCRIPTION = 0x44455343U;
        public:     static const x::uint32 NORMALS     = 0x564E524DU;
        public:     static const x::uint32 SUBDIVISION = 0x53535542U;
        public:     static const x::uint32 INFORMATION = 0x494E464FU;
        public:     static const x::uint32 OWNER       = 0x4F574E52U;
        public:     static const x::uint32 GLOW        = 0x474C4F57U;
        protected:  x::string __name;
        protected:  x::uint32 __version;
        protected:  x::string __category;
        protected:  x::array<Homeworld2::Graphics::Material> __materials;
        protected:  x::array<x::graphics::texture> __textures;
        protected:  x::map<x::string, Homeworld2::Graphics::Multimesh> __multimeshs;
        protected:  x::map<x::string, Homeworld2::Graphics::Goblinmesh> __goblinmeshs;
        protected:  x::map<x::string, Homeworld2::Graphics::Joint> __joints;
        protected:  x::map<x::string, Homeworld2::Graphics::Engineshape> __engineshapes;
        protected:  Homeworld2::Graphics::Joint * __root;
        protected:  x::real __energy;
        protected:  x::real __velocity;
        protected:  x::real __mass;
        public:     const x::real mass() const override { return __mass; }
        public:     virtual void mass(x::real v){ __mass = v; }
        public:     const x::real energy() const override { return __energy; }
        public:     virtual void energy(x::real v){ __energy = v; }
        public:     const x::real velocity() const override { return __velocity; }
        public:     virtual void velocity(x::real v){ __velocity = v; }
        public:     inline const x::array<x::graphics::texture> & textures() const { return __textures; }
        public:     inline void version(x::uint32 v){ __version = v; }
        public:     inline void category(const x::string & v){ __category = v; }
        public:     inline void add(Homeworld2::Graphics::Material && o) { __materials.append(x::move(o)); }
        public:     inline void add(const Homeworld2::Graphics::Material & o) { __materials.append(o); }
        public:     inline void add(x::graphics::texture && o) { __textures.append(x::move(o)); }
        public:     inline void add(const x::graphics::texture & o) { __textures.append(o); }
        public:     inline void add(Homeworld2::Graphics::Multimesh && o) { __multimeshs.put(o.name(), x::move(o)); }
        public:     inline void add(const Homeworld2::Graphics::Multimesh & o) { __multimeshs.put(o.name(), o); }
        public:     inline void add(Homeworld2::Graphics::Goblinmesh && o) { __goblinmeshs.put(o.name(), x::move(o)); }
        public:     inline void add(const Homeworld2::Graphics::Goblinmesh & o) { __goblinmeshs.put(o.name(), o); }
        public:     inline void add(Homeworld2::Graphics::Joint && o) { __joints.put(o.name(), x::move(o)); }
        public:     inline void add(const Homeworld2::Graphics::Joint & o) { __joints.put(o.name(), o); }
        public:     inline void add(Homeworld2::Graphics::Engineshape && o) { __engineshapes.put(o.name(), x::move(o)); }
        public:     inline void add(const Homeworld2::Graphics::Engineshape & o) { __engineshapes.put(o.name(), o); }
        public:     inline void add(Homeworld2::Graphics::Engineburn && o){}
        public:     inline void add(const Homeworld2::Graphics::Engineburn & o){}
        public:     inline void add(Homeworld2::Graphics::Navlight && o){}
        public:     inline void add(const Homeworld2::Graphics::Navlight & o){}
        public:     inline void add(Homeworld2::Graphics::Marker && o){}
        public:     inline void add(const Homeworld2::Graphics::Marker & o){}
        public:     inline void add(Homeworld2::Graphics::Boundary && o){}
        public:     inline void add(const Homeworld2::Graphics::Boundary & o){}
        public:     inline void add(Homeworld2::Graphics::Collision && o){}
        public:     inline void add(const Homeworld2::Graphics::Collision & o){}
        public:     inline void add(Homeworld2::Graphics::Basicmesh && basicmesh){}
        public:     inline void add(const Homeworld2::Graphics::Basicmesh & basicmesh){}
        public:     inline void add(Information && basicmesh){}
        public:     inline void add(const Information & basicmesh){}
        public:     inline void add(Engineglow && engineglow){}
        public:     inline void add(const Engineglow & engineglow){}
        public:     const x::string & name() const override { return __name; }
        public:     virtual Homeworld2::Graphics::Objects::Root * build();
        public:     virtual void init();
        public:     void load() override;
        public:     void unload() override;
        public:     void render() override;
        public:     Homeworld2::Graphics::Reference & operator=(const Homeworld2::Graphics::Reference & o) = delete;
        public:     Homeworld2::Graphics::Reference & operator=(Homeworld2::Graphics::Reference && o) noexcept = delete;
        public:     Reference(const x::string & name);
        public:     Reference() = delete;
        public:     Reference(const Homeworld2::Graphics::Reference & o) = delete;
        public:     Reference(Homeworld2::Graphics::Reference && o) noexcept = delete;
        public:     virtual ~Reference();
        };
    }
}

#endif // __HOMEWORLD2_GRAPHICS__REFERENCE_DATA__HH__
