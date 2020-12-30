#ifndef   __HOMEWORLD2_GRAPHICS__REFERENCE_FILE__HH__
#define   __HOMEWORLD2_GRAPHICS__REFERENCE_FILE__HH__

#include <x/file.hh>
#include <x/uinteger32.hh>

#include <Homeworld2/Graphics/Reference.hh>

namespace Homeworld2
{
    namespace Graphics
    {
        class ReferenceFile
        {
        public:     static const x::uint32 POSITION = 0x00000001U;
        public:     static const x::uint32 NORMAL   = 0x00000002U;
        public:     static const x::uint32 COLOR    = 0x00000004U;
        public:     static const x::uint32 TEXTURE  = 0x000007F8U;
        public:     static const x::uint32 HVERTEX  = 0x00000800U; // ???
        public:     static const x::uint32 SVERTEX  = 0x00001000U; // ???
        public:     static const x::uint32 TANGENT  = 0x00002000U;
        public:     static const x::uint32 BINORMAL = 0x00004000U;

        public:     static const x::uint32 INVALID = 0;
        public:     static const x::uint32 POINT = 512;
        public:     static const x::uint32 LINE = 513;
        public:     static const x::uint32 TRIANGLES = 514;
        public:     static const x::uint32 LINELOOP = 515;
        public:     static const x::uint32 LINESTRIP = 516;
        public:     static const x::uint32 TRIANGLEFAN = 517;
        public:     static const x::uint32 TRIANGLESTRIP = 518;
        public:     static const x::uint32 QUAD = 519;
        public:     static const x::uint32 QUADSTRIP = 520;
        public:     static const x::uint32 POLYGON = 521;

        public:     class Context
                    {
                    protected:  x::uint32 __type;
                    protected:  x::uint32 __size;
                    protected:  x::uint32 __id;
                    protected:  x::uint32 __version;
                    protected:  x::uint32 __position;
                    protected:  ReferenceFile::Context * __parent;
                    public:     x::uint32 type() const { return __type; }
                    public:     x::uint32 size() const { return __size; }
                    public:     x::uint32 id() const { return __id; }
                    public:     x::uint32 version() const { return __version; }
                    public:     x::uint32 position() const { return __position; }
                    public:     ReferenceFile::Context * parent() const { return __parent; }
                    public:     x::uint32 remain() const { return __size - __position; }
                    public:     x::int32 finish() const { return __size == __position; }
                    public:     void move(x::uint32 v) { __position = __position + v; }
                    public:     x::float32 real32(x::file::input::stream & in)
                                {
                                    __position = __position + sizeof(x::float32);
                                    return in.float32();
                                }
                    public:     x::float64 real64(x::file::input::stream & in)
                                {
                                    __position = __position + sizeof(x::float64);
                                    return in.float64();
                                }
                    public:     x::uint8 uinteger8(x::file::input::stream & in)
                                {
                                    __position = __position + sizeof(x::uint8);
                                    return in.byte();
                                }
                    public:     x::uint16 uinteger16(x::file::input::stream & in)
                                {
                                    __position = __position + sizeof(x::uint16);
                                    return in.uint16();
                                }
                    public:     x::uint32 uinteger32(x::file::input::stream & in)
                                {
                                    __position = __position + sizeof(x::uint32);
                                    return in.uint32();
                                }
                    public:     x::string str(x::file::input::stream & in, x::uint32 n)
                                {
                                    __position = __position + n;
                                    return n > 0 ? in.str(n) : x::string();
                                }
                    public:     x::string str(x::file::input::stream & in)
                                {
                                    x::uint32 n = uinteger32(in);
                                    return str(in, n);
                                }
                    public:     x::bytes data(x::file::input::stream & in)
                                {
                                    x::uint32 n = uinteger32(in);
                                    return data(in, n);
                                }
                    public:     x::bytes data(x::file::input::stream & in, x::uint32 n)
                                {
                                    __position = __position + n;
                                    return n > 0 ? in.data(n) : x::bytes();
                                }
                    public:     Context & operator=(const Context & o)
                                {
                                    if(&o != this)
                                    {
                                        __type = o.__type;
                                        __size = o.__size;
                                        __id = o.__id;
                                        __version = o.__version;
                                        __position = o.__position;
                                        __parent = o.__parent;
                                    }
                                    return *this;
                                }
                    public:     Context & operator=(Context && o) noexcept
                                {
                                    if(&o != this)
                                    {
                                        __type = o.__type;
                                        __size = o.__size;
                                        __id = o.__id;
                                        __version = o.__version;
                                        __position = o.__position;
                                        __parent = o.__parent;

                                        o.__type = Reference::UNKNOWN;
                                        o.__size = 0;
                                        o.__id = Reference::UNKNOWN;
                                        o.__version = 0;
                                        o.__position = 0;
                                        o.__parent = nullptr;
                                    }
                                    return *this;
                                }
                    public:     Context(x::uint32 type, x::uint32 size, x::uint32 id, x::uint32 version, x::uint32 position, ReferenceFile::Context * parent) :
                                    __type(type),
                                    __size(size),
                                    __id(id),
                                    __version(version),
                                    __position(position),
                                    __parent(parent)
                                {
                                }
                    public:     Context() :
                                    __type(Reference::UNKNOWN),
                                    __size(0),
                                    __id(Reference::UNKNOWN),
                                    __version(0),
                                    __position(0),
                                    __parent(nullptr)
                                {
                                }
                    public:     Context(const Context & o) :
                                    __type(o.__type),
                                    __size(o.__size),
                                    __id(o.__id),
                                    __version(o.__version),
                                    __position(o.__position),
                                    __parent(o.__parent)
                                {
                                }
                    public:     Context(Context && o) noexcept :
                                    __type(o.__type),
                                    __size(o.__size),
                                    __id(o.__id),
                                    __version(o.__version),
                                    __position(o.__position),
                                    __parent(o.__parent)
                                {
                                    o.__type = Reference::UNKNOWN;
                                    o.__size = 0;
                                    o.__id = Reference::UNKNOWN;
                                    o.__version = 0;
                                    o.__position = 0;
                                    o.__parent = nullptr;
                                }
                    public:     virtual ~Context()
                                {
                                    __type = Reference::UNKNOWN;
                                    __size = 0;
                                    __id = Reference::UNKNOWN;
                                    __version = 0;
                                    __position = 0;
                                    __parent = nullptr;
                                }
                    };
        public:     static Homeworld2::Graphics::Reference * load(const x::string & path, const x::string & name);
        public:     static Homeworld2::Graphics::Reference * load(const x::file & file, const x::string & name);
        protected:  static void debug(x::uint32 v);
        protected:  static void debug(const ReferenceFile::Context & context);
        protected:  static x::uint32 uinteger32(x::file::input::stream & in, bool invert);
        protected:  static x::uint32 uinteger32(x::file::input::stream & in);
        protected:  static ReferenceFile::Context context(x::file::input::stream & in);
        protected:  static ReferenceFile::Context context(x::file::input::stream & in, ReferenceFile::Context * parent);
        protected:  static void version(ReferenceFile::Context & root, Homeworld2::Graphics::Reference & object, x::file::input::stream & in);
        protected:  static void category(ReferenceFile::Context & root, Homeworld2::Graphics::Reference & object, x::file::input::stream & in);
        protected:  static void data(ReferenceFile::Context & root, Homeworld2::Graphics::Reference & object, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Material material(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static x::graphics::texture texture(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Multimesh multimesh(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Singlemesh singlemesh(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static void vertices(Homeworld2::Graphics::Primitive & primitive, Context & root, x::uint32 mask, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Goblinmesh goblinmesh(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static void detail(Context & root, Homeworld2::Graphics::Reference & object, x::file::input::stream & in);
        protected:  static void joints(Context & root, Homeworld2::Graphics::Reference & object, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Engineshape engineshape(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Engineburn engineburn(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static void navlight(ReferenceFile::Context & root, Homeworld2::Graphics::Reference & object, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Marker marker(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Marker::Head markerhead(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Keyframe keyframe(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Boundary boundary(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Collision collision(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Box box(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Sphere sphere(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Triangle triangle(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Basicmesh basicmesh(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Description description(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static void normals(ReferenceFile::Context & root, Homeworld2::Graphics::Basicmesh & basicmesh, x::file::input::stream & in);
        protected:  static Homeworld2::Graphics::Subdivision subdivision(ReferenceFile::Context & root, x::file::input::stream & in);
        protected:  static void information(ReferenceFile::Context & root, Reference & object, x::file::input::stream & in);
        protected:  static void information(ReferenceFile::Context & root, Engineglow & engineglow, x::file::input::stream & in);
        protected:  static Engineglow glow(ReferenceFile::Context & root, x::file::input::stream & in);
        };
    }
}

#endif // __HOMEWORLD2_GRAPHICS__REFERENCE_FILE__HH__
