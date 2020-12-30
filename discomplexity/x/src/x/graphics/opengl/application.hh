#ifndef   __X_GRAPHICS_OPENGL__APPLICATION__HH__
#define   __X_GRAPHICS_OPENGL__APPLICATION__HH__

#include <x/graphics/application.hh>

namespace x
{
    namespace graphics
    {
        namespace opengl
        {
            class application : public x::graphics::application
            {
            public:     static x::graphics::application & init(int argc, char ** argv);
            protected:  x::uint32 __mode;
            protected:  x::uint32 __major;
            protected:  x::uint32 __minor;
            public:     x::int32 run() override;
            public:     void render() override;
            public:     void render(x::graphics::surface & surface) override;
            public:     void render(x::graphics::primitive & o) override;
            public:     void idle() override;
            public:     void load(x::graphics::shader & o) override;
            public:     void unload(x::graphics::shader & o) override;
            public:     void load(x::graphics::program & o) override;
            public:     void unload(x::graphics::program & o) override;
            public:     void load(x::graphics::vertices & o) override;
            public:     void unload(x::graphics::vertices & o) override;
            public:     void load(x::graphics::buffer & o) override;
            public:     void unload(x::graphics::buffer & o) override;
            public:     void load(x::graphics::primitive & o) override;
            public:     void unload(x::graphics::primitive & o) override;
            public:     void bind(x::graphics::program & o) override;
            public:     void bind(x::graphics::program & o, const x::string & name, const x::graphics::matrix & matrix) override;
            public:     void bind(x::graphics::program & o, const x::string & name, const x::graphics::vector & vector) override;
            public:     void bind(x::graphics::program & o, const x::string & name, const x::graphics::color & color) override;
            public:     void bind(x::graphics::program & o, const x::string & name, x::float32 v) override;
            public:     void bind(x::graphics::vertices & o) override;
            public:     void bind(x::graphics::buffer & o) override;
            public:     void bind(x::uint32 index, x::graphics::buffer & buffer, x::uint32 stride, x::uint64 position) override;
            public:     void unbind(x::uint32 index) override;
            public:     void draw(const x::graphics::vertices & vertices, const x::array<x::uint32> & indices) override;
            protected:  application & operator=(const application & o) = delete;
            protected:  application & operator=(application && o) noexcept = delete;
            protected:  application();
            protected:  application(const application & o) = delete;
            protected:  application(application && o) noexcept = delete;
            public:     ~application() override;
            };
        }
    }
}

#endif // __X_GRAPHICS_OPENGL__APPLICATION__HH__
