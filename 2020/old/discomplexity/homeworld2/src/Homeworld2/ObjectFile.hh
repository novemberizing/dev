#ifndef   __HOMEWORLD2__OBJECT_FILE__HH__
#define   __HOMEWORLD2__OBJECT_FILE__HH__

#include <x/file.hh>
#include <x/endian.hh>

#include <Homeworld2/Object.hh>

namespace Homeworld2
{
    class ObjectFile : public x::file
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
                protected:  ObjectFile::Context * __parent;
                public:     x::uint32 type() const { return __type; }
                public:     x::uint32 size() const { return __size; }
                public:     x::uint32 id() const { return __id; }
                public:     x::uint32 version() const { return __version; }
                public:     x::uint32 position() const { return __position; }
                public:     ObjectFile::Context * parent() const { return __parent; }
                public:     x::uint32 remain() const { return __size - __position; }
                public:     x::int32 finish() const { return __size == __position; }
                public:     void move(x::uint32 v) { __position = __position + v; }
                public:     x::float32 real32(x::file::input::stream & in)
                            {
                                __position = __position + sizeof(x::float32);
                                return in.real32();
                            }
                public:     x::float64 real64(x::file::input::stream & in)
                            {
                                __position = __position + sizeof(x::float64);
                                return in.real64();
                            }
                public:     x::uint8 uinteger8(x::file::input::stream & in)
                            {
                                __position = __position + sizeof(x::uint8);
                                return in.uinteger8();
                            }
                public:     x::uint16 uinteger16(x::file::input::stream & in)
                            {
                                __position = __position + sizeof(x::uint16);
                                return in.uinteger16();
                            }
                public:     x::uint32 uinteger32(x::file::input::stream & in)
                            {
                                __position = __position + sizeof(x::uint32);
                                return ObjectFile::uinteger32(in);
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

                                    o.__type = Object::UNKNOWN;
                                    o.__size = 0;
                                    o.__id = Object::UNKNOWN;
                                    o.__version = 0;
                                    o.__position = 0;
                                    o.__parent = nullptr;
                                }
                                return *this;
                            }
                public:     Context(x::uint32 type, x::uint32 size, x::uint32 id, x::uint32 version, x::uint32 position, ObjectFile::Context * parent) :
                                __type(type),
                                __size(size),
                                __id(id),
                                __version(version),
                                __position(position),
                                __parent(parent)
                            {
                            }
                public:     Context() :
                                __type(Object::UNKNOWN),
                                __size(0),
                                __id(Object::UNKNOWN),
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
                                o.__type = Object::UNKNOWN;
                                o.__size = 0;
                                o.__id = Object::UNKNOWN;
                                o.__version = 0;
                                o.__position = 0;
                                o.__parent = nullptr;
                            }
                public:     virtual ~Context()
                            {
                                __type = Object::UNKNOWN;
                                __size = 0;
                                __id = Object::UNKNOWN;
                                __version = 0;
                                __position = 0;
                                __parent = nullptr;
                            }
                };
    protected:  static void debug(x::uint32 v);
    protected:  static void debug(const ObjectFile::Context & context);
    protected:  static x::uint32 uinteger32(x::file::input::stream & in, bool swap);
    protected:  static x::uint32 uinteger32(x::file::input::stream & in);
    protected:  static ObjectFile::Context context(x::file::input::stream & in);
    protected:  static ObjectFile::Context context(x::file::input::stream & in, ObjectFile::Context * parent);
    protected:  static void version(ObjectFile::Context & root, Object & object, x::file::input::stream & in);
    protected:  static void category(ObjectFile::Context & root, Object & object, x::file::input::stream & in);
    protected:  static void data(ObjectFile::Context & root, Object & object, x::file::input::stream & in);
    protected:  static Material material(Context & root, x::file::input::stream & in);
    protected:  static Texture texture(Context & root, x::file::input::stream & in);
    protected:  static Multimesh multimesh(Context & root, x::file::input::stream & in);
    protected:  static Singlemesh singlemesh(Context & root, x::file::input::stream & in);
    protected:  static void vertices(x::graphics::primitive & primitive, Context & root, x::uint32 mask, x::file::input::stream & in);
    protected:  static Goblinmesh goblinmesh(Context & root, x::file::input::stream & in);
    protected:  static void detail(Context & root, Object & object, x::file::input::stream & in);
    protected:  static void joints(Context & root, Object & object, x::file::input::stream & in);
    protected:  static Engineshape engineshape(Context & root, x::file::input::stream & in);
    protected:  static Engineburn engineburn(Context & root, x::file::input::stream & in);
    protected:  static void navlight(Context & root, Object & object, x::file::input::stream & in);
    protected:  static Marker marker(Context & root, x::file::input::stream & in);
    protected:  static Marker::Head markerhead(Context & root, x::file::input::stream & in);
    protected:  static Keyframe keyframe(Context & root, x::file::input::stream & in);
    protected:  static Boundary boundary(Context & root, x::file::input::stream & in);
    protected:  static Collision collision(Context & root, x::file::input::stream & in);
    protected:  static Box box(Context & root, x::file::input::stream & in);
    protected:  static Sphere sphere(Context & root, x::file::input::stream & in);
    protected:  static Triangles triangles(Context & root, x::file::input::stream & in);
    protected:  static Basicmesh basicmesh(Context & root, x::file::input::stream & in);
    protected:  static Description description(Context & root, x::file::input::stream & in);
    protected:  static void normals(Context & root, Basicmesh & basicmesh, x::file::input::stream & in);
    protected:  static Subdivision subdivision(Context & root, x::file::input::stream & in);
    protected:  static void information(Context & root, Object & object, x::file::input::stream & in);
    public:     static Object * load(const char * path, const char * name);
    };
}

#endif // __HOMEWORLD2__OBJECT_FILE__HH__
