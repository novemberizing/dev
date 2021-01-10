#ifndef   __HOMEWORLD2__OBJECT__HH__
#define   __HOMEWORLD2__OBJECT__HH__

#include <x/physics/reference.hh>

#include <x/graphics/reference.hh>
#include <x/graphics/application.hh>

#include <Homeworld2/Graphics/Material.hh>
#include <Homeworld2/Graphics/Texture.hh>
#include <Homeworld2/Graphics/Multimesh.hh>
#include <Homeworld2/Graphics/Goblinmesh.hh>
#include <Homeworld2/Graphics/Joint.hh>
#include <Homeworld2/Graphics/Engineshape.hh>
#include <Homeworld2/Graphics/Engineburn.hh>
#include <Homeworld2/Graphics/Navlight.hh>
#include <Homeworld2/Graphics/Marker.hh>
#include <Homeworld2/Graphics/Boundary.hh>
#include <Homeworld2/Graphics/Collision.hh>
#include <Homeworld2/Graphics/Basicmesh.hh>
#include <Homeworld2/Graphics/Information.hh>
#include <Homeworld2/Graphics/Object.hh>
#include <Homeworld2/Graphics/Glow.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class Reference : public x::graphics::reference
        {
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
        protected:  x::uint32 __version;
        protected:  x::string __category;
        protected:  x::array<Material> __materials;
        protected:  x::array<x::graphics::texture> __textures;
        protected:  x::map<x::string, Multimesh> __multimeshs;
        protected:  x::map<x::string, Goblinmesh> __goblinmeshs;
        protected:  x::map<x::string, Joint> __joints;
        protected:  x::map<x::string, Engineshape> __engineshapes;
        protected:  Joint * __root;
        public:     void load() override;
        public:     void unload() override;
        public:     void render(const x::reality::matrix & model) override;
        public:     Object * build();
        // public:     x::reality::object::reference * build(const x::string & name, const x::reality::vector & position, const x::reality::vector & direction) override;
        public:     inline x::map<x::string, Joint> & joints() { return __joints; }
        public:     inline void version(x::uint32 v){ __version = v; }
        public:     inline void category(const x::string & v) { __category = v; }
        public:     inline void category(x::string && v) { __category = x::move(v); }
        public:     inline void add(Material && o) { __materials.append(x::move(o)); }
        public:     inline void add(const Material & o) { __materials.append(o); }
        public:     inline void add(x::graphics::texture && o) { __textures.append(x::move(o)); }
        public:     inline void add(const x::graphics::texture & o) { __textures.append(o); }
        public:     inline void add(Multimesh && o) { __multimeshs.put(o.name(), x::move(o)); }
        public:     inline void add(const Multimesh & o) { __multimeshs.put(o.name(), o); }
        public:     inline void add(Goblinmesh && o) { __goblinmeshs.put(o.name(), x::move(o)); }
        public:     inline void add(const Goblinmesh & o) { __goblinmeshs.put(o.name(), o); }
        public:     inline void add(Joint && o) { __joints.put(o.name(), x::move(o)); }
        public:     inline void add(const Joint & o) { __joints.put(o.name(), o); }
        public:     inline void add(Engineshape && o) { __engineshapes.put(o.name(), x::move(o)); }
        public:     inline void add(const Engineshape & o) { __engineshapes.put(o.name(), o); }
        public:     inline void add(Engineburn && o){}
        public:     inline void add(const Engineburn & o){}
        public:     inline void add(Navlight && o){}
        public:     inline void add(const Navlight & o){}
        public:     inline void add(Marker && o){}
        public:     inline void add(const Marker & o){}
        public:     inline void add(Boundary && o){}
        public:     inline void add(const Boundary & o){}
        public:     inline void add(Collision && o){}
        public:     inline void add(const Collision & o){}
        public:     inline void add(Basicmesh && basicmesh){}
        public:     inline void add(const Basicmesh & basicmesh){}
        public:     inline void add(Information && basicmesh){}
        public:     inline void add(const Information & basicmesh){}
        public:     inline void add(Glow && glow){}
        public:     inline void add(const Glow & glow){}
        public:     virtual void init();
        public:     Reference & operator=(const Reference & o);
        public:     Reference & operator=(Reference && o) noexcept;
        public:     Reference();
        public:     Reference(const x::string & name);
        public:     Reference(x::string && name);
        public:     Reference(const Reference & o);
        public:     Reference(Reference && o) noexcept;
        public:     ~Reference() override;
        public:     friend x::output::stream & operator<<(x::output::stream & os, const Reference & o)
                    {
                        return os;
                    }
        };
    }
}


#endif // __HOMEWORLD2__OBJECT__HH__
