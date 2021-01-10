#ifndef   __X_GRAPHICS__APPLICATION__HH__
#define   __X_GRAPHICS__APPLICATION__HH__

#include <x/event.hh>
#include <x/map.hh>
#include <x/string.hh>
#include <x/timestamp.hh>

#include <x/graphics/shader.hh>
#include <x/graphics/program.hh>
#include <x/graphics/surface.hh>
#include <x/graphics/primitive.hh>
#include <x/graphics/texture.hh>
#include <x/graphics/layer.hh>
#include <x/graphics/environment.hh>

namespace x
{
    namespace graphics
    {
        class application
        {
        protected:  inline static x::graphics::application * __singleton = nullptr;
        public:     static x::graphics::application & get()
                    {
                        assertion(__singleton == nullptr);

                        return *__singleton;
                    }
        protected:  x::int32 __x;
        protected:  x::int32 __y;
        protected:  x::int32 __width;
        protected:  x::int32 __height;
        protected:  x::string __name;
        protected:  x::real __fps;
        public:     x::graphics::surface * __surface;
        public:     x::event::engine engine;
        public:     x::map<x::string, x::graphics::shader> shaders;
        public:     x::map<x::string, x::graphics::program> programs;
        public:     x::map<x::string, x::graphics::reference *> references;
        public:     x::map<x::string, x::graphics::texture> textures;
        protected:  x::function<void (unsigned char, int, int)> __keyboard;
        protected:  x::function<void (int, int, int)> __special;
        public:     x::graphics::environment environment;
        protected:  x::timestamp __timestamp;
        public:     inline void surface(x::graphics::surface * o){ __surface = o; }
        public:     inline const x::graphics::shader & shader(const x::string & key)
                    {
                        return shaders[key];
                    }
        public:     inline x::graphics::program * program(const x::string & key)
                    {
                        try
                        {
                            return &programs[key];
                        }
                        catch(const x::exception & e)
                        {
                            return nullptr;
                        }
                    }
        public:     inline x::graphics::reference * reference(const x::string & key)
                    {
                        try
                        {
                            return references[key];
                        }
                        catch(const x::exception & e)
                        {
                            return nullptr;
                        }
                    }
        public:     inline x::real width() const { return static_cast<x::real>(__width); }
        public:     inline x::real height() const { return static_cast<x::real>(__height); }
        public:     inline void width(x::int32 v){ __width = v; }
        public:     inline void height(x::int32 v){ __height = v; }
        public:     inline x::real fps() const { return __fps; }
        public:     inline void add(x::graphics::reference * o) { references.put(o->name(), o); }
        public:     inline void add(const x::graphics::shader & o){ shaders.put(o.name(), o); }
        public:     inline void add(x::graphics::shader && o){ shaders.put(o.name(), x::move(o)); }
        public:     inline void add(const x::graphics::program & o){ programs.put(o.name(), o); }
        public:     inline void add(x::graphics::program && o){ programs.put(o.name(), x::move(o)); }
        public:     inline void add(const x::array<x::graphics::texture> & textures) { textures.each([this](const x::graphics::texture & texture){ this->textures.put(texture.name(), texture); }); }
        public:     inline void add(const x::graphics::texture & o){ textures.put(o.name(), o); }
        public:     inline void add(x::graphics::texture && o){ textures.put(o.name(), x::move(o)); }
        public:     virtual void load(x::graphics::shader & o) = 0;
        public:     virtual void load(x::graphics::program & o) = 0;
        public:     virtual void load(x::graphics::primitive & o) = 0;
        public:     virtual void load(x::graphics::buffer & o) = 0;
        public:     virtual void load(x::graphics::vertices & o) = 0;
        public:     virtual void load(x::graphics::texture & o) = 0;
        public:     virtual void unload(x::graphics::texture & o) = 0;
        public:     virtual void unload(x::graphics::vertices & o) = 0;
        public:     virtual void unload(x::graphics::buffer & o) = 0;
        public:     virtual void unload(x::graphics::primitive & o) = 0;
        public:     virtual void unload(x::graphics::program & o) = 0;
        public:     virtual void unload(x::graphics::shader & o) = 0;
        public:     virtual void bind(x::graphics::vertices & o) = 0;
        public:     virtual void bind(x::graphics::buffer & o) = 0;
        public:     virtual void bind(x::graphics::texture & o) = 0;
        public:     virtual void bind(x::graphics::program & o, x::graphics::object & object) = 0;
        public:     virtual void bind(x::uint32 index, x::uint32 size, x::graphics::buffer & buffer, x::uint32 stride, x::uint64 position) = 0;
        public:     virtual void bind(x::uint32 id, const x::reality::matrix & matrix) = 0;
        public:     virtual void bind(x::uint32 id, const x::reality::vector & vector) = 0;
        public:     virtual void bind(x::uint32 id, const x::reality::color & color) = 0;
        public:     virtual void bind(x::uint32 id, x::real v) = 0;
        public:     virtual void bind(x::uint32 id, x::int32 v) = 0;
        public:     virtual void draw(const x::graphics::vertices & vertices, const x::array<x::uint32> & indices) = 0;
        public:     virtual void draw(const x::graphics::vertices & vertices) = 0;
        public:     virtual x::int32 run() = 0;
        public:     virtual void render() = 0;
        public:     virtual void render(x::graphics::reference & reference) = 0;
        public:     virtual void idle() = 0;
        public:     virtual void animation() = 0;
        public:     virtual void keyboard(unsigned char key, int x, int y);
        public:     virtual void keyboard(x::function<void (unsigned char, int, int)> f){ __keyboard = f; }
        public:     virtual void special(int key, int x, int y);
        public:     virtual void special(x::function<void (int, int, int)> f){ __special = f; }
        public:     virtual x::boolean mousemove(x::int32 x, x::int32 y);
        public:     virtual x::boolean mouse(x::int32 button, x::int32 state, x::int32 x, x::int32 y);
        public:     x::graphics::application & operator=(const x::graphics::application & o) = delete;
        public:     x::graphics::application & operator=(x::graphics::application && o) noexcept = delete;
        public:     application();
        public:     application(const application & o) = delete;
        public:     application(application && o) noexcept = delete;
        public:     virtual ~application();
        };
    }
}

#endif // __X_GRAPHICS__APPLICATION__HH__
