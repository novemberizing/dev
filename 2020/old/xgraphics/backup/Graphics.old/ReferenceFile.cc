#include "ReferenceFile.hh"
#include "Primitive.hh"

namespace Homeworld2
{
    namespace Graphics
    {
        void ReferenceFile::debug(x::uint32 v)
        {
#if 0
            switch(v)
            {
                case Reference::UNKNOWN:       x::console::out << "unknown" << x::endl; break;
                case Reference::FORM:          x::console::out << "form" << x::endl; break;
                case Reference::NORMAL:        x::console::out << "normal" << x::endl; break;
                case Reference::VERSION:       x::console::out << "version" << x::endl; break;
                case Reference::CATEGORY:      x::console::out << "category" << x::endl; break;
                case Reference::DATA:          x::console::out << "data" << x::endl; break;
                case Reference::MATERIAL:      x::console::out << "material" << x::endl; break;
                case Reference::TEXTURE:       x::console::out << "texture" << x::endl; break;
                case Reference::MULTIMESH:     x::console::out << "multimesh" << x::endl; break;
                case Reference::SINGLEMESH:    x::console::out << "singlemesh" << x::endl; break;
                case Reference::GOBLINMESH:    x::console::out << "goblinmesh" << x::endl; break;
                case Reference::DETAIL:        x::console::out << "detail" << x::endl; break;
                case Reference::JOINTS:        x::console::out << "joints" << x::endl; break;
                case Reference::ENGINESHAPE:   x::console::out << "engineshape" << x::endl; break;
                case Reference::ENGINEBURN:    x::console::out << "engineburn" << x::endl; break;
                case Reference::NAVLIGHT:      x::console::out << "navlight" << x::endl; break;
                case Reference::MARKER:        x::console::out << "marker" << x::endl; break;
                case Reference::HEAD:          x::console::out << "head" << x::endl; break;
                case Reference::KEYFRAME:      x::console::out << "keyframe" << x::endl; break;
                case Reference::BOUNDARY:      x::console::out << "boundary" << x::endl; break;
                case Reference::COLLISION:     x::console::out << "collision" << x::endl; break;
                case Reference::BOX:           x::console::out << "box" << x::endl; break;
                case Reference::SPHERE:        x::console::out << "sphere" << x::endl; break;
                case Reference::TRIANGLE:      x::console::out << "triangle" << x::endl; break;
                case Reference::BASICMESH:     x::console::out << "basicmesh" << x::endl; break;
                case Reference::DESCRIPTION:   x::console::out << "description" << x::endl; break;
                case Reference::NORMALS:       x::console::out << "normals" << x::endl; break;
                case Reference::SUBDIVISION:   x::console::out << "subdivision" << x::endl; break;
                case Reference::INFORMATION:   x::console::out << "information" << x::endl; break;
                case Reference::OWNER:         x::console::out << "owner" << x::endl; break;
                case Reference::GLOW:          x::console::out << "glow" << x::endl; break;
                default: {
                    char * s = (char *)(&v);
                    x::console::out << s[0] << s[1] << s[2] << s[3] << x::endl;
                    exceptional();
                }
            }
#endif // 0
        }

        void ReferenceFile::debug(const ReferenceFile::Context & context)
        {
            Context * parent = context.parent();
            while(parent)
            {
#if 0
                x::console::out << ' ';
#endif // 0
                parent = parent->parent();
            }
            ReferenceFile::debug(context.id());
        }

        x::uint32 ReferenceFile::uinteger32(x::file::input::stream & in, bool invert)
        {
            x::uint32 result = in.uint32();
            return invert ? x::uinteger32::invert(result) : result;
        }

        x::uint32 ReferenceFile::uinteger32(x::file::input::stream & in)
        {
            return ReferenceFile::uinteger32(in, false);
        }

        ReferenceFile::Context ReferenceFile::context(x::file::input::stream & in)
        {
            return ReferenceFile::context(in, nullptr);
        }

        ReferenceFile::Context ReferenceFile::context(x::file::input::stream & in, ReferenceFile::Context * parent)
        {
            x::uint32 type     = ReferenceFile::uinteger32(in, true);
            x::uint32 size     = ReferenceFile::uinteger32(in, true);
            x::uint32 id       = 0;
            x::uint32 version  = 0;
            x::uint32 position = 0;
            if(type == Reference::FORM)
            {
                id = ReferenceFile::uinteger32(in, true);
                position += sizeof(x::uint32);
            }
            else if(type == Reference::NORMAL)
            {
                id = ReferenceFile::uinteger32(in, true);
                version = ReferenceFile::uinteger32(in, true);
                position += (sizeof(x::uint32) * 2);
            }
            else
            {
                id = type;
            }
            if(parent)
            {
                parent->move(sizeof(x::uint32) * 2);
            }
            return ReferenceFile::Context(type, size, id, version, position, parent);
        }

        Reference * ReferenceFile::load(const x::file & file, const x::string & name)
        {
            return ReferenceFile::load(file.path(), name);
        }

        Reference * ReferenceFile::load(const x::string & path, const x::string & name)
        {
            x::file::input::stream in = x::file::input::stream::open(path);
            Reference * object = new Reference(name);
            while(!in.finish())
            {
                ReferenceFile::Context context = ReferenceFile::context(in);
                switch(context.id())
                {
                    case Reference::VERSION:       ReferenceFile::version(context, *object, in);      break;
                    case Reference::CATEGORY:      ReferenceFile::category(context, *object, in);     break;
                    case Reference::DATA:          ReferenceFile::data(context, *object, in);         break;
                    case Reference::DETAIL:        ReferenceFile::detail(context, *object, in);       break;
                    case Reference::INFORMATION:   ReferenceFile::information(context, *object, in);  break;
                    default:                    ReferenceFile::debug(context);                     exceptional();
                }
                assertion(context.finish()==0);
            }
//            object->init();
            return object;
        }

        void ReferenceFile::version(ReferenceFile::Context & root, Reference & object, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            object.version(root.uinteger32(in));
            assertion(root.finish() == 0);
        }

        void ReferenceFile::category(ReferenceFile::Context & root, Reference & object, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            object.category(root.str(in, root.remain()));
            assertion(root.finish() == 0);
        }

        void ReferenceFile::data(ReferenceFile::Context & root, Reference & object, x::file::input::stream & in)
        {
            while(!in.finish() && !root.finish())
            {
                ReferenceFile::Context context = ReferenceFile::context(in, &root);
                switch(context.id())
                {
                    case Reference::MATERIAL:      object.add(ReferenceFile::material(context, in)); break;
                    case Reference::TEXTURE:       object.add(ReferenceFile::texture(context, in)); break;
                    case Reference::MULTIMESH:     object.add(ReferenceFile::multimesh(context, in)); break;
                    case Reference::GOBLINMESH:    object.add(ReferenceFile::goblinmesh(context, in)); break;
                    default:                    ReferenceFile::debug(context);         exceptional();
                }
                root.move(context.size());
                assertion(context.finish() == 0);
            }
        }

        Material ReferenceFile::material(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Material material;
            material.name(root.str(in));
            material.shader(root.str(in));
            x::uint32 total = root.uinteger32(in);
            for(x::uint32 i = 0; i < total; i++)
            {
                x::uint32 type = root.uinteger32(in);
                if(type == 5)
                {
                    x::bytes value = root.data(in);
                    x::string name = root.str(in);
                    if(name == "$diffuse")
                    {
                        material.diffuse(x::uinteger32::from(value));
                    }
                    else if(name == "$glow")
                    {
                        material.glow(x::uinteger32::from(value));
                    }
                    else
                    {
                        x::console::out << name << " => " << x::endl;
                        exceptional();
                    }
                }
                else
                {
                    exceptional();
                }
            }
            assertion(root.finish() == 0);
            return material;
        }

        x::graphics::texture ReferenceFile::texture(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            x::graphics::texture texture;
            texture.name(root.str(in));
            texture.format(x::uinteger32::invert(root.uinteger32(in)));
            x::uint32 total = root.uinteger32(in);
            for(x::uint32 i = 0; i < total; i++)
            {
                x::graphics::mipmap mipmap;
                mipmap.width(root.uinteger32(in));
                mipmap.height(root.uinteger32(in));
                x::uint32 n = Texture::size(mipmap.width(), mipmap.height(), 1, texture.format());

                mipmap.bytes(root.data(in, n));
                texture.mipmaps.append(x::move(mipmap));
            }
            assertion(root.finish() == 0);
            return texture;
        }

        Multimesh ReferenceFile::multimesh(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Multimesh multimesh;
            multimesh.name(root.str(in));
            multimesh.parent(root.str(in));
            x::uint32 total = root.uinteger32(in);
            for(x::uint32 i = 0; i < total; i++)
            {
                ReferenceFile::Context context = ReferenceFile::context(in, &root);
                switch(context.id())
                {
                    case Reference::SINGLEMESH:    multimesh.singlemeshs.append(ReferenceFile::singlemesh(context, in)); break;
                    default:                    ReferenceFile::debug(context);                                        exceptional();
                }
                root.move(context.size());
            }
            assertion(root.finish() == 0);
            return multimesh;
        }

        Singlemesh ReferenceFile::singlemesh(Context & root, x::file::input::stream & in)
        {
            x::graphics::application & application = x::graphics::application::get();

            ReferenceFile::debug(root);
            Singlemesh singlemesh;
            singlemesh.level(root.uinteger32(in));
            x::uint32 total = root.uinteger32(in);
            for(x::uint32 i = 0; i < total; i++)
            {
                x::uint32 index = root.uinteger32(in);  // material index
                x::uint32 flags = root.uinteger32(in);
                x::uint32 mask = 0;
                if(flags & POSITION) { mask |= x::graphics::vertices::location; }
                if(flags & NORMAL) { mask |= x::graphics::vertices::normal; }
                if(flags & COLOR) { mask |= x::graphics::vertices::color; }
                if(flags & TEXTURE) { mask |= x::graphics::vertices::texture; }
                if(flags & TANGENT) { mask |= x::graphics::vertices::tangent; }
                if(flags & BINORMAL) { mask |= x::graphics::vertices::binormal; }
                if(flags & HVERTEX){ exceptional(); }
                if(flags & SVERTEX){ exceptional(); }

                Primitive * primitive = new Primitive();
                // primitive->mask(mask);
                primitive->target(x::graphics::buffer::array);
                primitive->usage(x::graphics::buffer::statical, x::graphics::buffer::draw);
                primitive->mode(x::graphics::vertices::triangle);
                primitive->material(index);

                ReferenceFile::vertices(*primitive, root, mask, in);
                singlemesh.push(primitive);
            }

            assertion(root.finish() == 0);
            return singlemesh;
        }

    //    static x::real __max = 0.0f;

        void ReferenceFile::vertices(x::graphics::primitive & primitive, ReferenceFile::Context & root, x::uint32 mask, x::file::input::stream & in)
        {
            x::uint32 total = root.uinteger32(in);
            for(x::uint32 i = 0; i < total; i++)
            {
                x::graphics::vertex vertex;
                if(mask & x::graphics::vertices::location)
                {
                    x::float32 x = root.real32(in);
                    x::float32 y = root.real32(in);
                    x::float32 z = root.real32(in);
                    x::float32 w = root.real32(in);
                    // if(__max < x::abs(x))
                    // {
                    //     __max = x::abs(x);
                    //     x::console::out << __max << x::endl << x::flush;
                    // }
                    // if(__max < x::abs(y))
                    // {
                    //     __max = x::abs(y);
                    //     x::console::out << __max << x::endl << x::flush;
                    // }
                    // if(__max < x::abs(z))
                    // {
                    //     __max = x::abs(z);
                    //     x::console::out << __max << x::endl << x::flush;
                    // }
                    vertex.location(x, y, -z, w);
                    vertex.location(x::reality::matrix::rotate(x::radian(180.0f), x::reality::vector({0.0f, 1.0f, 0.0f})) * vertex.location());

                }
                if(mask & x::graphics::vertices::normal)
                {
                    x::float32 x = root.real32(in);
                    x::float32 y = root.real32(in);
                    x::float32 z = root.real32(in);
                    x::float32 w = root.real32(in);
                    // vertex.normal(x, y, z, w);
                    vertex.normal(x, y, -z, w);
                    vertex.normal(x::reality::matrix::rotate(x::radian(180.0f), x::reality::vector({0.0f, 1.0f, 0.0f})) * vertex.normal());

                }
                if(mask & x::graphics::vertices::color)
                {
                    x::uint32 diffuse = root.uinteger32(in);
                    // x::console::out << "diffuse" << diffuse << x::endl;
                }
                if(mask & x::graphics::vertices::texture)
                {
                    x::float32 x = root.real32(in);
                    x::float32 y = root.real32(in);
                    // x::console::out << "texture " << x << "," << (1.0f - y) << x::endl;
                    vertex.texture(x, y);
                }
                if(mask & x::graphics::vertices::tangent)
                {
                    x::float32 x = root.real32(in);
                    x::float32 y = root.real32(in);
                    x::float32 z = root.real32(in);
                    // vertex.tangent(x, y, z);
                    vertex.tangent(x, y, -z);
                    vertex.tangent(x::reality::matrix::rotate(x::radian(180.0f), x::reality::vector({0.0f, 1.0f, 0.0f})) * vertex.tangent());
                }
                if(mask & x::graphics::vertices::binormal)
                {
                    x::float32 x = root.real32(in);
                    x::float32 y = root.real32(in);
                    x::float32 z = root.real32(in);
                    // vertex.binormal(x, y, z);
                    vertex.binormal(x, y, -z);
                    vertex.binormal(x::reality::matrix::rotate(x::radian(180.0f), x::reality::vector({0.0f, 1.0f, 0.0f})) * vertex.binormal());
                }
                primitive.push(x::move(vertex));
            }
            total = root.uinteger16(in);

            for(x::uint32 i = 0; i < total; i++)
            {
                x::uint32 type = root.uinteger32(in);
                x::uint32 count = root.uinteger32(in);
                // primitive.type(type);
                // x::console::out << "implement set type" << x::endl;
                for(x::uint32 j = 0; j < count; j++)
                {
                    primitive.push((x::uint32) root.uinteger16(in));
                }
            }
        }

        Goblinmesh ReferenceFile::goblinmesh(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Goblinmesh goblinmesh;
            goblinmesh.name(root.str(in));
            goblinmesh.parent(root.str(in));
            ReferenceFile::Context context = ReferenceFile::context(in, &root);
            if(context.id() == Reference::SINGLEMESH)
            {
                goblinmesh.singlemesh = x::move(ReferenceFile::singlemesh(context, in));
                root.move(context.size());
            }
            else
            {
                exceptional();
            }
            assertion(root.finish() == 0);
            return goblinmesh;
        }

        void ReferenceFile::detail(Context & root, Reference & object, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            while(!in.finish() && !root.finish())
            {
                ReferenceFile::Context context = ReferenceFile::context(in, &root);
                switch(context.id())
                {
                    case Reference::JOINTS:            ReferenceFile::joints(context, object, in);            break;
                    case Reference::ENGINESHAPE:       object.add(ReferenceFile::engineshape(context, in));   break;
                    case Reference::ENGINEBURN:        object.add(ReferenceFile::engineburn(context, in));    break;
                    case Reference::NAVLIGHT:          ReferenceFile::navlight(context, object, in);          break;
                    case Reference::MARKER:            object.add(ReferenceFile::marker(context, in));        break;
                    case Reference::BOUNDARY:          object.add(ReferenceFile::boundary(context, in));      break;
                    case Reference::COLLISION:         object.add(ReferenceFile::collision(context, in));     break;
                    case Reference::BASICMESH:         object.add(ReferenceFile::basicmesh(context, in));     break;
                    case Reference::GLOW:              object.add(ReferenceFile::glow(context, in));          break;
                    default:                        ReferenceFile::debug(context);                         exceptional();
                }
                assertion(context.finish() == 0);
                root.move(context.size());
            }
        }

        void ReferenceFile::joints(Context & root, Reference & object, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            x::uint32 total = root.uinteger32(in);
            x::map<x::string, Joint> & joints = object.joints();
            for(x::uint32 i = 0; i < total; i++)
            {
                Joint joint;
                joint.name(root.str(in));

                joint.parent(root.str(in));

                // location
                x::float32 x = root.real32(in);
                x::float32 y = root.real32(in);
                x::float32 z = root.real32(in);
                joint.location(-x, y, z);
                // rotation
                x = root.real32(in);
                y = root.real32(in);
                z = root.real32(in);
                // joint.rotation(x, y, z);
                joint.rotation(-x, -y, z);
                joint.rotation(x::reality::matrix::rotate(x::radian(180.0f), x::reality::vector({0.0f, 1.0f, 0.0f})) * joint.rotation());
                // joint.rotation(joint.rotation().x(), -joint.rotation().y(), joint.rotation().z());

                // joint.rotation(x::reality::matrix::rotate(x::radian(180.0f), x::reality::vector({1.0f, 0.0f, 0.0f})) * joint.rotation());
                // joint.rotation(-joint.rotation().x(), joint.rotation().y(), joint.rotation().z());
                // joint.rotation(x, z, -y);
                // scale
                x = root.real32(in);
                y = root.real32(in);
                z = root.real32(in);
                joint.scale(x, y, z);
                // axis
                x = root.real32(in);
                y = root.real32(in);
                z = root.real32(in);
                // joint.axis(x, y, z);
                joint.axis(-x, -y, z);
                joint.axis(x::reality::matrix::rotate(x::radian(180.0f), x::reality::vector({0.0f, 1.0f, 0.0f})) * joint.axis());
                // freedom
                x = root.uinteger8(in);
                y = root.uinteger8(in);
                z = root.uinteger8(in);
                joint.freedom(x, y, z);

                object.add(x::move(joint));
            }
            assertion(root.finish() == 0);
        }

        Engineshape ReferenceFile::engineshape(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Engineshape engineshape;
            engineshape.name(root.str(in));
            engineshape.parent(root.str(in));
            // x::string name = root.str(in);
            // x::string parent = root.str(in);
            x::uint32 total = root.uinteger32(in);
            for(x::uint32 i = 0; i < total; i++)
            {
                x::graphics::vertex vertex;
                // location
                x::float32 x = root.real32(in);
                x::float32 y = root.real32(in);
                x::float32 z = root.real32(in);
                vertex.location(x, y, z, 1.0f );
                engineshape.push(x::move(vertex));
            }
            total = root.uinteger32(in);
            // x::graphics::vertices & vertices = engineshape.vertices();
            for(x::uint32 i = 0; i < total; i++)
            {

                x::float32 x = root.real32(in);
                x::float32 y = root.real32(in);
                x::float32 z = root.real32(in);
                engineshape.vertices[i].normal(x, y, z, 0.0f);
            }
            assertion(root.finish() == 0);
            return engineshape;
        }

        Engineburn ReferenceFile::engineburn(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Engineburn engineburn;
            x::string name = root.str(in);
            x::string parent = root.str(in);
            x::uint32 division = root.uinteger32(in);
            x::uint32 flames = root.uinteger32(in);
            for(x::uint32 i = 0; i < flames; i++)
            {
                for(x::uint32 j = 0; j < division; j++)
                {
                    x::float32 x = root.real32(in);
                    x::float32 y = root.real32(in);
                    x::float32 z = root.real32(in);
                }
            }
            assertion(root.finish() == 0);
            return engineburn;
        }

        void ReferenceFile::navlight(Context & root, Reference & object, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            x::uint32 total = root.uinteger32(in);
            for(x::uint32 i = 0; i < total; i++)
            {
                Navlight navlight;
                x::string name = root.str(in);
                x::uint32 section = root.uinteger32(in);
                x::float32 size = root.real32(in);
                x::float32 phase = root.real32(in);
                x::float32 frequency = root.real32(in);
                x::string style = root.str(in);
                // color
                x::float32 x = root.real32(in);
                x::float32 y = root.real32(in);
                x::float32 z = root.real32(in);
                x::float32 w = root.real32(in);
                x::float32 distance = root.real32(in);
                x::byte visible = root.uinteger8(in);
                x::byte highend = root.uinteger8(in);

                object.add(x::move(navlight));
            }
            assertion(root.finish() == 0);
        }

        Marker ReferenceFile::marker(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Marker marker;
            while(!root.finish())
            {
                Context context = ReferenceFile::context(in, &root);
                switch(context.id())
                {
                    case Reference::HEAD:      marker.add(ReferenceFile::markerhead(context, in)); break;
                    case Reference::KEYFRAME:  marker.add(ReferenceFile::keyframe(context, in));   break;
                    default:                ReferenceFile::debug(context);                      exceptional();
                }
                assertion(context.finish() == 0);
                root.move(context.size());
            }
            return marker;
        }

        Marker::Head ReferenceFile::markerhead(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Marker::Head head;
            x::string name = root.str(in);
            x::string parent = root.str(in);
            // animation start and end time
            x::float32 start = root.real32(in);
            x::float32 end = root.real32(in);
            // location
            x::float64 x = root.real64(in);
            x::float64 y = root.real64(in);
            x::float64 z = root.real64(in);
            // rotation
            x = root.real64(in);
            y = root.real64(in);
            z = root.real64(in);
            assertion(root.finish() == 0);
            return head;
        }

        Keyframe ReferenceFile::keyframe(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Keyframe keyframe;
            while(!root.finish())
            {
                ReferenceFile::Context context = ReferenceFile::context(in, &root);
                ReferenceFile::debug(context);
                switch(context.id())
                {
                    case Reference::BOUNDARY:  keyframe.add(ReferenceFile::boundary(context, in));    break;
                    default:                ReferenceFile::debug(context);                         exceptional();
                }
                assertion(context.finish() == 0);
                root.move(context.size());
            }

            return keyframe;
        }

        Boundary ReferenceFile::boundary(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Boundary boundary;
            x::string name = root.str(in);
            x::string parent = root.str(in);
            x::uint32 total = root.uinteger32(in);
            for(x::uint32 i = 0; i < total; i++)
            {
                x::float32 x = root.real32(in);
                x::float32 y = root.real32(in);
                x::float32 z = root.real32(in);
            }
            x::uint32 information = root.uinteger32(in);
            assertion(root.finish() == 0);
            return boundary;
        }

        Collision ReferenceFile::collision(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Collision collision;
            x::string name = root.str(in);
            while(!root.finish())
            {
                Context context = ReferenceFile::context(in, &root);
                switch(context.id())
                {
                    case Reference::BOX:       collision.add(ReferenceFile::box(context, in));        break;
                    case Reference::SPHERE:    collision.add(ReferenceFile::sphere(context, in));     break;
                    case Reference::TRIANGLE:  collision.add(ReferenceFile::triangle(context, in));  break;
                    default:                ReferenceFile::debug(context);                         exceptional();
                }
                assertion(context.finish() == 0);
                root.move(context.size());
            }
            return collision;
        }

        Box ReferenceFile::box(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Box box;
            // min
            x::float32 x = root.real32(in);
            x::float32 y = root.real32(in);
            x::float32 z = root.real32(in);
            // max
            x = root.real32(in);
            y = root.real32(in);
            z = root.real32(in);
            assertion(root.finish() == 0);
            return box;
        }

        Sphere ReferenceFile::sphere(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Sphere sphere;
            // center
            x::float32 x = root.real32(in);
            x::float32 y = root.real32(in);
            x::float32 z = root.real32(in);
            // max
            x::float32 radius = root.real32(in);
            assertion(root.finish() == 0);
            return sphere;
        }

        Triangle ReferenceFile::triangle(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Triangle triangle;
            x::uint32 total = root.uinteger32(in);
            // vertex
            for(x::uint32 i = 0; i < total; i++)
            {
                x::float32 x = root.real32(in);
                x::float32 y = root.real32(in);
                x::float32 z = root.real32(in);
            }
            total = root.uinteger32(in);
            // index
            for(x::uint32 i = 0; i < total; i++)
            {
                x::uint16 index = root.uinteger16(in);
            }
            assertion(root.finish() == 0);
            return triangle;
        }

        Basicmesh ReferenceFile::basicmesh(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Basicmesh basicmesh;
            while(!root.finish())
            {
                Context context = ReferenceFile::context(in, &root);
                switch(context.id())
                {
                    case Reference::DESCRIPTION:   basicmesh.add(ReferenceFile::description(context, in));    break;
                    case Reference::BOX:           basicmesh.add(ReferenceFile::box(context, in));            break;
                    case Reference::SPHERE:        basicmesh.add(ReferenceFile::sphere(context, in));         break;
                    case Reference::TRIANGLE:      basicmesh.add(ReferenceFile::triangle(context, in));      break;
                    case Reference::SUBDIVISION:   basicmesh.add(ReferenceFile::subdivision(context, in));    break;
                    case Reference::NORMALS:       ReferenceFile::normals(context, basicmesh, in);            break;
                    default:                    ReferenceFile::debug(context);                             exceptional();
                }
                root.move(context.size());
                assertion(context.finish() == 0);
            }
            return basicmesh;
        }

        Description ReferenceFile::description(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Description description;
            x::string name = root.str(in);
            x::string parent = root.str(in);
            x::uint32 level = root.uinteger32(in);
            assertion(root.finish() == 0);
            return description;
        }

        void ReferenceFile::normals(Context & root, Basicmesh & basicmesh, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            x::uint32 total = root.uinteger32(in);
            for(x::uint32 i = 0; i < total; i++)
            {
                x::float32 x = root.real32(in);
                x::float32 y = root.real32(in);
                x::float32 z = root.real32(in);
            }
            total = root.uinteger32(in);
            for(x::uint32 i = 0; i < total; i++)
            {
                x::uint16 index = root.uinteger16(in);
            }
            assertion(root.finish() == 0);
        }

        Subdivision ReferenceFile::subdivision(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Subdivision subdivision;
            x::uint32 x = root.uinteger32(in);
            x::uint32 y = root.uinteger32(in);
            x::uint32 z = root.uinteger32(in);
            for(x::uint32 i = 0; i < z; i++)
            {
                for(x::uint32 j = 0; j < y; j++)
                {
                    for(x::uint32 k = 0; k < x; k++)
                    {
                        x::uint32 total = root.uinteger32(in);
                        for(x::uint32 l = 0; l < total; l++)
                        {
                            x::uint16 index = root.uinteger16(in);
                        }
                    }
                }
            }
            assertion(root.finish() == 0);
            return subdivision;
        }

        void ReferenceFile::information(Context & root, Reference & object, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Information information;
            while(!root.finish())
            {
                Context context = ReferenceFile::context(in, &root);
                switch(context.id())
                {
                    case Reference::OWNER:     information.owner(context.str(in)); break;
                    default:                ReferenceFile::debug(context);         exceptional();
                }
                assertion(context.finish() == 0);
                root.move(context.size());
            }
            object.add(information);
        }

        void ReferenceFile::information(Context & root, Glow & object, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);

            x::string name = root.str(in);
            x::string parent = root.str(in);
            x::uint32 level = root.uinteger32(in);

            assertion(root.finish() == 0);
        }

        Glow ReferenceFile::glow(Context & root, x::file::input::stream & in)
        {
            ReferenceFile::debug(root);
            Glow glow;

            while(!in.finish() && !root.finish())
            {
                ReferenceFile::Context context = ReferenceFile::context(in, &root);
                switch(context.id())
                {
                    case Reference::INFORMATION:    ReferenceFile::information(context, glow, in); break;
                    case Reference::SINGLEMESH:     glow.add(ReferenceFile::singlemesh(context, in)); break;
                    // case Reference::MATERIAL:      object.add(ReferenceFile::material(context, in)); break;
                    // case Reference::TEXTURE:       object.add(ReferenceFile::texture(context, in)); break;
                    // case Reference::MULTIMESH:     object.add(ReferenceFile::multimesh(context, in)); break;
                    // case Reference::GOBLINMESH:    object.add(ReferenceFile::goblinmesh(context, in)); break;
                    default:                    ReferenceFile::debug(context);         exceptional();
                }
                root.move(context.size());
                assertion(context.finish() == 0);
            }

            return glow;
        }
    }
}
