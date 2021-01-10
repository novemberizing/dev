#ifndef   __HOMEWORLD2__OBJECT__HH__
#define   __HOMEWORLD2__OBJECT__HH__

#include <x/graphics/object.hh>
#include <x/graphics/application.hh>

#include <Homeworld2/Material.hh>
#include <Homeworld2/Texture.hh>
#include <Homeworld2/Multimesh.hh>
#include <Homeworld2/Goblinmesh.hh>
#include <Homeworld2/Joint.hh>
#include <Homeworld2/Engineshape.hh>
#include <Homeworld2/Engineburn.hh>
#include <Homeworld2/Navlight.hh>
#include <Homeworld2/Marker.hh>
#include <Homeworld2/Boundary.hh>
#include <Homeworld2/Collision.hh>
#include <Homeworld2/Basicmesh.hh>
#include <Homeworld2/Information.hh>

namespace Homeworld2
{
    class Object : public x::graphics::object
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
    public:     static const x::uint32 TRIANGLES   = 0x54524953U;
    public:     static const x::uint32 BASICMESH   = 0x4253524DU;
    public:     static const x::uint32 DESCRIPTION = 0x44455343U;
    public:     static const x::uint32 NORMALS     = 0x564E524DU;
    public:     static const x::uint32 SUBDIVISION = 0x53535542U;
    public:     static const x::uint32 INFORMATION = 0x494E464FU;
    public:     static const x::uint32 OWNER       = 0x4F574E52U;
    protected:  x::uint32 __version;
    protected:  x::string __category;
    protected:  x::map<x::string, Material> __materials;
    protected:  x::map<x::string, Texture> __textures;
    protected:  x::map<x::string, Multimesh> __multimesh;
    protected:  x::map<x::string, Goblinmesh> __goblinmesh;
    protected:  x::map<x::string, Joint> __joints;
    protected:  x::map<x::string, Engineshape> __engineshapes;
    protected:  Joint * __root;
    public:     void load() override;
    public:     void unload() override;
    public:     void refresh(const x::graphics::matrix & model) override;
    public:     void render(const x::graphics::matrix & model, x::uint32 level) override;
    public:     void exec(const x::array<x::string> & strings, x::uint64 index) override;
    public:     inline x::map<x::string, Joint> & joints() { return __joints; }
    public:     inline void version(x::uint32 v){ __version = v; }
    public:     inline void category(const x::string & v) { __category = v; }
    public:     inline void category(x::string && v) { __category = x::move(v); }
    public:     inline void add(Material && o) { __materials.put(o.name(), x::move(o)); }
    public:     inline void add(const Material & o) { __materials.put(o.name(), o); }
    public:     inline void add(Texture && o) { __textures.put(o.name(), x::move(o)); }
    public:     inline void add(const Texture & o) { __textures.put(o.name(), o); }
    public:     inline void add(Multimesh && o) { __multimesh.put(o.name(), x::move(o)); }
    public:     inline void add(const Multimesh & o) { __multimesh.put(o.name(), o); }
    public:     inline void add(Goblinmesh && o) { __goblinmesh.put(o.name(), x::move(o)); }
    public:     inline void add(const Goblinmesh & o) { __goblinmesh.put(o.name(), o); }
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
    public:     virtual void init();
    public:     Object & operator=(const Object & o);
    public:     Object & operator=(Object && o) noexcept;
    public:     Object();
    public:     Object(const x::string & name);
    public:     Object(x::string && name);
    public:     Object(const Object & o);
    public:     Object(Object && o) noexcept;
    public:     ~Object() override;
    public:     friend x::output::stream & operator<<(x::output::stream & os, const Object & o)
                {
                    return os;
                }
    };
}


#endif // __HOMEWORLD2__OBJECT__HH__
