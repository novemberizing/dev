#ifndef   __X_GRAPHICS__APPLICATION__HH__
#define   __X_GRAPHICS__APPLICATION__HH__

#include <x/graphics/type.hh>
#include <x/graphics/color.hh>
#include <x/graphics/shader.hh>
#include <x/graphics/program.hh>
#include <x/graphics/object.hh>
#include <x/graphics/vertices.hh>
#include <x/graphics/buffer.hh>
#include <x/graphics/primitive.hh>
#include <x/graphics/camera.hh>
#include <x/graphics/light.hh>
#include <x/graphics/surface.hh>
#include <x/graphics/util.hh>
#include <x/console.hh>
#include <x/event.hh>

namespace x
{
    namespace graphics
    {
        class application
        {
        protected:  inline static application * __singleton = nullptr;
        public:     static application & get()
                    {
                        assertion(__singleton == nullptr);
                        return *__singleton;
                    }
        public:     static void refresh()
                    {
                        assertion(__singleton == nullptr);
                        __singleton->__surface.refresh();
                        __singleton->render();
                    }
        protected:  x::int32 __x;
        protected:  x::int32 __y;
        protected:  x::int32 __width;
        protected:  x::int32 __height;
        protected:  x::string __name;
        protected:  x::map<x::string, x::graphics::shader> __shaders;
        protected:  x::map<x::string, x::graphics::program> __programs;
        protected:  x::graphics::surface __surface;
        protected:  x::event::engine __engine;
        protected:  x::map<x::string, x::graphics::object *> __objects;
        public:     inline x::graphics::object * object(const x::string & name)
                    {
                        try
                        {
                            return __objects[name];
                        }
                        catch(const x::exception & e)
                        {
                            return nullptr;
                        }
                    }
        public:     inline x::graphics::surface & surface() { return __surface; }
        public:     inline x::event::engine & engine(){ return __engine; }
        public:     inline x::int32 width() const { return __width; }
        public:     inline x::int32 height() const { return __height; }
        public:     inline const x::graphics::projection & projection() const { return __surface.projection(); }
        public:     inline x::graphics::projection & projection() { return __surface.projection(); }
        public:     inline const x::graphics::camera & camera() const { return __surface.camera(); }
        public:     inline x::graphics::camera & camera() { return __surface.camera(); }
        public:     inline const x::graphics::light & light() const { return __surface.light(); }
        public:     inline x::graphics::light & light() { return __surface.light(); }
        public:     inline void add(const x::graphics::program & o){ __programs.put(o.name(), o); }
        public:     inline void add(x::graphics::program && o){ __programs.put(o.name(), x::move(o)); }
        public:     inline void add(const x::graphics::shader & o){ __shaders.put(o.name(), o); }
        public:     inline void add(x::graphics::shader && o){ __shaders.put(o.name(), x::move(o)); }
        public:     inline void add(x::graphics::object * o)
                    {
                        if(o != nullptr)
                        {
                            __objects.put(o->name(), o);
                        }
                    }
        public:     inline void add(const x::string & name, x::graphics::object * o)
                    {
                        if(o != nullptr)
                        {
                            __surface.add(x::graphics::reference(name, o));
                        }
                    }
        public:     inline void add(const x::graphics::reference & o)
                    {
                        __surface.add(o);
                    }
        public:     inline void add(x::graphics::reference && o)
                    {
                        __surface.add(x::move(o));
                    }
        public:     virtual x::int32 run() = 0;
        public:     virtual void render() = 0;
        public:     virtual void render(x::graphics::primitive & o) = 0;
        public:     virtual void render(x::graphics::surface & surface) = 0;
        public:     virtual void idle() = 0;
        public:     virtual void load(x::graphics::shader & o) = 0;
        public:     virtual void unload(x::graphics::shader & o) = 0;
        public:     virtual void load(x::graphics::program & o) = 0;
        public:     virtual void unload(x::graphics::program & o) = 0;
        public:     virtual void load(x::graphics::vertices & o) = 0;
        public:     virtual void unload(x::graphics::vertices & o) = 0;
        public:     virtual void load(x::graphics::buffer & o) = 0;
        public:     virtual void unload(x::graphics::buffer & o) = 0;
        public:     virtual void load(x::graphics::primitive & o) = 0;
        public:     virtual void unload(x::graphics::primitive & o) = 0;
        public:     virtual void exec(const x::string & command);
        public:     virtual void exec(const x::array<x::string> & strings);
        public:     virtual x::graphics::program * program(const x::string & name)
                    {
                        try
                        {
                            return &__programs[name];
                        }
                        catch(const x::exception & e)
                        {
                            return nullptr;
                        }
                    }
        public:     virtual void bind(x::graphics::program & o) = 0;
        public:     virtual void bind(x::graphics::program & o, const x::string & name, const x::graphics::matrix & matrix) = 0;
        public:     virtual void bind(x::graphics::program & o, const x::string & name, const x::graphics::vector & vector) = 0;
        public:     virtual void bind(x::graphics::program & o, const x::string & name, const x::graphics::color & vector) = 0;
        public:     virtual void bind(x::graphics::program & o, const x::string & name, x::float32 v) = 0;
        public:     virtual void bind(x::graphics::vertices & o) = 0;
        public:     virtual void bind(x::graphics::buffer & o) = 0;
        public:     virtual void bind(x::uint32 index, x::graphics::buffer & buffer, x::uint32 stride, x::uint64 position) = 0;
        public:     virtual void unbind(x::uint32 index) = 0;
        public:     virtual void draw(const x::graphics::vertices & vertices, const x::array<x::uint32> & indices) = 0;
        protected:  application & operator=(const application & o) = delete;
        protected:  application & operator=(application && o) noexcept = delete;
        protected:  application();
        protected:  application(const application & o) = delete;
        protected:  application(application && o) noexcept = delete;
        public:     virtual ~application();
        };
    }
}

#endif // __X_GRAPHICS__APPLICATION__HH__
