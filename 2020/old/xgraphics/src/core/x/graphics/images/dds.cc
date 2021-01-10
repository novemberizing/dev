#include "dds.hh"



namespace x
{
    namespace graphics
    {
        namespace images
        {
            x::graphics::images::dds dds::load(const x::string & path)
            {
                x::graphics::images::dds result;
                x::bytes content = x::file::data(path);
                x::console::out << content.size() << x::endl;

                x::string type = x::string::from(content.data(), 0, 4);
                result.__height = x::uinteger32::from(content.data(), 12);
                result.__width = x::uinteger32::from(content.data(), 16);
                result.__linear = x::uinteger32::from(content.data(), 20);
                result.__count = x::uinteger32::from(content.data(), 28);
                result.__format = x::uinteger32::from(content.data(), 84);

                x::console::out << "type => " << type << x::endl;
                x::console::out << "height => " << result.__height << x::endl;
                x::console::out << "width => " << result.__width << x::endl;
                x::console::out << "linear => " << result.__linear << x::endl;
                x::console::out << "count => " << result.__count << x::endl;
                x::console::out << "format => " << result.__format << x::endl;
                printf("%08XU\n", result.__format);

                assertion(result.__format != 0x33545844);   // DXT3

                x::uint32 width = result.__width;
                x::uint32 height = result.__height;
                x::uint32 offset = 128;
                x::uint32 block = 16;


                for(x::uint32 level = 0; level < result.__count && (width || height); level++)
                {
                    x::uint32 size = ((width+3)/4)*((height+3)/4)*block;
                    x::console::out << size << x::endl;
                    result.mipmaps.append(x::graphics::mipmap(width, height, content.sub(offset, size)));
                    width /= 2;
                    height /= 2;
                    offset += size;
                    x::console::out << level << x::endl;
                    x::console::out << width << x::endl;
                    x::console::out << height << x::endl;


                    // if(width < 1) width = 1;
                    // if(height < 1) height = 1;
                }

                return result;
            }

            dds::dds()
            :   mipmaps(),
                __width(0),
                __height(0),
                __linear(0),
                __count(0),
                __format(0)
            {
            }

            dds::dds(const x::graphics::images::dds & o)
            :   mipmaps(o.mipmaps),
                __width(o.__width),
                __height(o.__height),
                __linear(o.__linear),
                __count(o.__count),
                __format(o.__format)
            {
            }

            dds::dds(x::graphics::images::dds && o) noexcept
            :   mipmaps(x::move(o.mipmaps)),
                __width(o.__width),
                __height(o.__height),
                __linear(o.__linear),
                __count(o.__count),
                __format(o.__format)
            {
                o.__width = 0;
                o.__height = 0;
                o.__linear = 0;
                o.__count = 0;
                o.__format = 0;
            }

            dds::~dds()
            {
                __width = 0;
                __height = 0;
                __linear = 0;
                __count = 0;
                __format = 0;
            }

            x::graphics::images::dds & dds::operator=(const x::graphics::images::dds & o)
            {
                if(&o != this)
                {
                    mipmaps = o.mipmaps;
                    __width = o.__width;
                    __height = o.__height;
                    __linear = o.__linear;
                    __count = o.__count;
                    __format =o.__format;
                }
                return *this;
            }

            x::graphics::images::dds & dds::operator=(x::graphics::images::dds && o) noexcept
            {
                if(&o != this)
                {
                    mipmaps = o.mipmaps;
                    __width = o.__width;
                    __height = o.__height;
                    __linear = o.__linear;
                    __count = o.__count;
                    __format =o.__format;

                    o.__width = 0;
                    o.__height = 0;
                    o.__linear = 0;
                    o.__count = 0;
                    o.__format = 0;
                }
                return *this;
            }

            x::graphics::texture dds::build(const x::string & name)
            {
                return x::graphics::texture(name, __format, mipmaps);
            }

            x::graphics::texture dds::build(x::string && name)
            {
                return x::graphics::texture(x::move(name), __format, mipmaps);
            }
        }
    }
}
