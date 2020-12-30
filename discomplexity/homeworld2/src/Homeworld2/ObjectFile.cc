#include "ObjectFile.hh"

namespace Homeworld2
{
    void ObjectFile::debug(x::uint32 v)
    {
#if 0
        switch(v)
        {
            case Object::UNKNOWN:       x::console::out << "unknown" << x::endl; break;
            case Object::FORM:          x::console::out << "form" << x::endl; break;
            case Object::NORMAL:        x::console::out << "normal" << x::endl; break;
            case Object::VERSION:       x::console::out << "version" << x::endl; break;
            case Object::CATEGORY:      x::console::out << "category" << x::endl; break;
            case Object::DATA:          x::console::out << "data" << x::endl; break;
            case Object::MATERIAL:      x::console::out << "material" << x::endl; break;
            case Object::TEXTURE:       x::console::out << "texture" << x::endl; break;
            case Object::MULTIMESH:     x::console::out << "multimesh" << x::endl; break;
            case Object::SINGLEMESH:    x::console::out << "singlemesh" << x::endl; break;
            case Object::GOBLINMESH:    x::console::out << "goblinmesh" << x::endl; break;
            case Object::DETAIL:        x::console::out << "detail" << x::endl; break;
            case Object::JOINTS:        x::console::out << "joints" << x::endl; break;
            case Object::ENGINESHAPE:   x::console::out << "engineshape" << x::endl; break;
            case Object::ENGINEBURN:    x::console::out << "engineburn" << x::endl; break;
            case Object::NAVLIGHT:      x::console::out << "navlight" << x::endl; break;
            case Object::MARKER:        x::console::out << "marker" << x::endl; break;
            case Object::HEAD:          x::console::out << "head" << x::endl; break;
            case Object::KEYFRAME:      x::console::out << "keyframe" << x::endl; break;
            case Object::BOUNDARY:      x::console::out << "boundary" << x::endl; break;
            case Object::COLLISION:     x::console::out << "collision" << x::endl; break;
            case Object::BOX:           x::console::out << "box" << x::endl; break;
            case Object::SPHERE:        x::console::out << "sphere" << x::endl; break;
            case Object::TRIANGLES:     x::console::out << "triangles" << x::endl; break;
            case Object::BASICMESH:     x::console::out << "basicmesh" << x::endl; break;
            case Object::DESCRIPTION:   x::console::out << "description" << x::endl; break;
            case Object::NORMALS:       x::console::out << "normals" << x::endl; break;
            case Object::SUBDIVISION:   x::console::out << "subdivision" << x::endl; break;
            case Object::INFORMATION:   x::console::out << "information" << x::endl; break;
            case Object::OWNER:         x::console::out << "owner" << x::endl; break;
            default: {
                char * s = (char *)(&v);
                x::console::out << s[0] << s[1] << s[2] << s[3] << x::endl;
                exceptional();
            }
        }
#endif // 0
    }

    void ObjectFile::debug(const ObjectFile::Context & context)
    {
        Context * parent = context.parent();
        while(parent)
        {
            // x::console::out << ' ';
            parent = parent->parent();
        }
        ObjectFile::debug(context.id());
    }

    x::uint32 ObjectFile::uinteger32(x::file::input::stream & in, bool swap)
    {
        x::uint32 result = in.uinteger32();
        return swap ? x::endian::convert(result) : result;
    }

    x::uint32 ObjectFile::uinteger32(x::file::input::stream & in)
    {
        return ObjectFile::uinteger32(in, false);
    }

    ObjectFile::Context ObjectFile::context(x::file::input::stream & in)
    {
        return ObjectFile::context(in, nullptr);
    }

    ObjectFile::Context ObjectFile::context(x::file::input::stream & in, ObjectFile::Context * parent)
    {
        x::uint32 type     = ObjectFile::uinteger32(in, true);
        x::uint32 size     = ObjectFile::uinteger32(in, true);
        x::uint32 id       = 0;
        x::uint32 version  = 0;
        x::uint32 position = 0;
        if(type == Object::FORM)
        {
            id = ObjectFile::uinteger32(in, true);
            position += sizeof(x::uint32);
        }
        else if(type == Object::NORMAL)
        {
            id = ObjectFile::uinteger32(in, true);
            version = ObjectFile::uinteger32(in, true);
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
        return ObjectFile::Context(type, size, id, version, position, parent);
    }

    Object * ObjectFile::load(const char * path, const char * name)
    {
        x::file::input::stream in = x::file::input::stream::open(path);
        Object * object = new Object(name);
        while(!in.finish())
        {
            ObjectFile::Context context = ObjectFile::context(in);
            switch(context.id())
            {
                case Object::VERSION:       ObjectFile::version(context, *object, in);      break;
                case Object::CATEGORY:      ObjectFile::category(context, *object, in);     break;
                case Object::DATA:          ObjectFile::data(context, *object, in);         break;
                case Object::DETAIL:        ObjectFile::detail(context, *object, in);       break;
                case Object::INFORMATION:   ObjectFile::information(context, *object, in);  break;
                default:                    ObjectFile::debug(context);                     exceptional();
            }
            assertion(context.finish()==0);
        }
        object->init();
        return object;
    }

    void ObjectFile::version(ObjectFile::Context & root, Object & object, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        object.version(root.uinteger32(in));
        assertion(root.finish() == 0);
    }

    void ObjectFile::category(ObjectFile::Context & root, Object & object, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        object.category(root.str(in, root.remain()));
        assertion(root.finish() == 0);
    }

    void ObjectFile::data(ObjectFile::Context & root, Object & object, x::file::input::stream & in)
    {
        while(!in.finish() && !root.finish())
        {
            ObjectFile::Context context = ObjectFile::context(in, &root);
            switch(context.id())
            {
                case Object::MATERIAL:      object.add(ObjectFile::material(context, in)); break;
                case Object::TEXTURE:       object.add(ObjectFile::texture(context, in)); break;
                case Object::MULTIMESH:     object.add(ObjectFile::multimesh(context, in)); break;
                case Object::GOBLINMESH:    object.add(ObjectFile::goblinmesh(context, in)); break;
                default:                    ObjectFile::debug(context);         exceptional();
            }
            root.move(context.size());
            assertion(context.finish() == 0);
        }
    }

    Material ObjectFile::material(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
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
                material.put(name, new x::uinteger32(name, *(x::uint32 *)(value.data())));
            }
            else
            {
                exceptional();
            }
        }
        assertion(root.finish() == 0);
        return material;
    }

    Texture ObjectFile::texture(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        Texture texture;
        texture.name(root.str(in));
        texture.format(x::endian::convert(root.uinteger32(in)));
        x::uint32 total = root.uinteger32(in);
        for(x::uint32 i = 0; i < total; i++)
        {
            texture.width(root.uinteger32(in));
            texture.height(root.uinteger32(in));
            x::uint32 n = Texture::size(texture.width(), texture.height(), 1, texture.format());
            texture.data(root.data(in, n));
        }
        assertion(root.finish() == 0);
        return texture;
    }

    Multimesh ObjectFile::multimesh(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        Multimesh multimesh;
        multimesh.name(root.str(in));
        multimesh.parent(root.str(in));
        x::uint32 total = root.uinteger32(in);
        for(x::uint32 i = 0; i < total; i++)
        {
            ObjectFile::Context context = ObjectFile::context(in, &root);
            switch(context.id())
            {
                case Object::SINGLEMESH:    multimesh.add(ObjectFile::singlemesh(context, in)); break;
                default:                    ObjectFile::debug(context);                         exceptional();
            }
            root.move(context.size());
        }
        assertion(root.finish() == 0);
        return multimesh;
    }

    Singlemesh ObjectFile::singlemesh(Context & root, x::file::input::stream & in)
    {
        x::graphics::application & application = x::graphics::application::get();

        ObjectFile::debug(root);
        Singlemesh singlemesh;
        singlemesh.level(root.uinteger32(in));
        x::uint32 total = root.uinteger32(in);
        for(x::uint32 i = 0; i < total; i++)
        {
            x::uint32 index = root.uinteger32(in);
            x::uint32 mask = root.uinteger32(in);

            x::graphics::primitive * primitive = new x::graphics::primitive();
            primitive->target(x::graphics::buffer::array);
            primitive->usage(x::graphics::buffer::statical, x::graphics::buffer::draw);
            primitive->mode(x::graphics::vertices::triangle);
            primitive->program(application.program("standard"));

            ObjectFile::vertices(*primitive, root, mask, in);
            singlemesh.push(primitive);
        }

        assertion(root.finish() == 0);
        return singlemesh;
    }

    void ObjectFile::vertices(x::graphics::primitive & primitive, ObjectFile::Context & root, x::uint32 mask, x::file::input::stream & in)
    {
        x::uint32 total = root.uinteger32(in);
        for(x::uint32 i = 0; i < total; i++)
        {
            x::graphics::vertex vertex;
            if(mask & POSITION)
            {
                x::float32 x = root.real32(in);
                x::float32 y = root.real32(in);
                x::float32 z = root.real32(in);
                x::float32 w = root.real32(in);
                // vertex.position(x, y, z, w);
                vertex.position(x, y, -z, w);
                vertex.position(x::graphics::matrix::rotate(x::math::radian(180.0f), x::graphics::vector({0.0f, 1.0f, 0.0f})) * vertex.position());

            }
            if(mask & NORMAL)
            {
                x::float32 x = root.real32(in);
                x::float32 y = root.real32(in);
                x::float32 z = root.real32(in);
                x::float32 w = root.real32(in);
                // vertex.normal(x, y, z, w);
                vertex.normal(x, y, -z, w);
                vertex.normal(x::graphics::matrix::rotate(x::math::radian(180.0f), x::graphics::vector({0.0f, 1.0f, 0.0f})) * vertex.normal());

            }
            if(mask & COLOR)
            {
                x::uint32 diffuse = root.uinteger32(in);
                // x::console::out << "diffuse" << diffuse << x::endl;
            }
            if(mask & TEXTURE)
            {
                x::float32 x = root.real32(in);
                x::float32 y = root.real32(in);
                vertex.texture(x, y);
            }
            if(mask & TANGENT)
            {
                x::float32 x = root.real32(in);
                x::float32 y = root.real32(in);
                x::float32 z = root.real32(in);
                // vertex.tangent(x, y, z);
                vertex.tangent(x, y, -z);
                vertex.tangent(x::graphics::matrix::rotate(x::math::radian(180.0f), x::graphics::vector({0.0f, 1.0f, 0.0f})) * vertex.tangent());
            }
            if(mask & BINORMAL)
            {
                x::float32 x = root.real32(in);
                x::float32 y = root.real32(in);
                x::float32 z = root.real32(in);
                // vertex.binormal(x, y, z);
                vertex.binormal(x, y, -z);
                vertex.binormal(x::graphics::matrix::rotate(x::math::radian(180.0f), x::graphics::vector({0.0f, 1.0f, 0.0f})) * vertex.binormal());
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

    Goblinmesh ObjectFile::goblinmesh(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        Goblinmesh goblinmesh;
        goblinmesh.name(root.str(in));
        goblinmesh.parent(root.str(in));
        ObjectFile::Context context = ObjectFile::context(in, &root);
        if(context.id() == Object::SINGLEMESH)
        {
            goblinmesh.set(ObjectFile::singlemesh(context, in));
            root.move(context.size());
        }
        else
        {
            exceptional();
        }
        assertion(root.finish() == 0);
        return goblinmesh;
    }

    void ObjectFile::detail(Context & root, Object & object, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        while(!in.finish() && !root.finish())
        {
            ObjectFile::Context context = ObjectFile::context(in, &root);
            switch(context.id())
            {
                case Object::JOINTS:            ObjectFile::joints(context, object, in);            break;
                case Object::ENGINESHAPE:       object.add(ObjectFile::engineshape(context, in));   break;
                case Object::ENGINEBURN:        object.add(ObjectFile::engineburn(context, in));    break;
                case Object::NAVLIGHT:          ObjectFile::navlight(context, object, in);          break;
                case Object::MARKER:            object.add(ObjectFile::marker(context, in));        break;
                case Object::BOUNDARY:          object.add(ObjectFile::boundary(context, in));      break;
                case Object::COLLISION:         object.add(ObjectFile::collision(context, in));     break;
                case Object::BASICMESH:         object.add(ObjectFile::basicmesh(context, in));     break;
                default:                        ObjectFile::debug(context);                         exceptional();
            }
            assertion(context.finish() == 0);
            root.move(context.size());
        }
    }

    void ObjectFile::joints(Context & root, Object & object, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        x::uint32 total = root.uinteger32(in);
        x::map<x::string, Joint> & joints = object.joints();
        for(x::uint32 i = 0; i < total; i++)
        {
            Joint joint;
            joint.name(root.str(in));

            joint.parent(root.str(in));

            // position
            x::float32 x = root.real32(in);
            x::float32 y = root.real32(in);
            x::float32 z = root.real32(in);
            // joint.position(x, y, z);
            joint.position(-x, y, z);
            // joint.position(x::graphics::matrix::rotate(x::math::radian(180.0f), x::graphics::vector({0.0f, 1.0f, 0.0f})) * joint.position());
            // rotation
            x = root.real32(in);
            y = root.real32(in);
            z = root.real32(in);
            // joint.rotation(x, y, z);
            joint.rotation(-x, -y, z);
            joint.rotation(x::graphics::matrix::rotate(x::math::radian(180.0f), x::graphics::vector({0.0f, 1.0f, 0.0f})) * joint.rotation());
            // joint.rotation(joint.rotation().x(), -joint.rotation().y(), joint.rotation().z());

            // joint.rotation(x::graphics::matrix::rotate(x::math::radian(180.0f), x::graphics::vector({1.0f, 0.0f, 0.0f})) * joint.rotation());
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
            joint.axis(x::graphics::matrix::rotate(x::math::radian(180.0f), x::graphics::vector({0.0f, 1.0f, 0.0f})) * joint.axis());
            // freedom
            x = root.uinteger8(in);
            y = root.uinteger8(in);
            z = root.uinteger8(in);
            joint.freedom(x, y, z);

            object.add(x::move(joint));
        }
        assertion(root.finish() == 0);
    }

    Engineshape ObjectFile::engineshape(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        Engineshape engineshape;
        engineshape.name(root.str(in));
        engineshape.parent(root.str(in));
        // x::string name = root.str(in);
        // x::string parent = root.str(in);
        x::uint32 total = root.uinteger32(in);
        for(x::uint32 i = 0; i < total; i++)
        {
            x::graphics::vertex vertex;
            // position
            x::float32 x = root.real32(in);
            x::float32 y = root.real32(in);
            x::float32 z = root.real32(in);
            vertex.position(x, y, z, 1.0f );
            engineshape.push(x::move(vertex));
        }
        total = root.uinteger32(in);
        x::graphics::vertices & vertices = engineshape.vertices();
        for(x::uint32 i = 0; i < total; i++)
        {

            x::float32 x = root.real32(in);
            x::float32 y = root.real32(in);
            x::float32 z = root.real32(in);
            vertices[i].normal(x, y, z, 0.0f);
        }
        assertion(root.finish() == 0);
        return engineshape;
    }

    Engineburn ObjectFile::engineburn(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
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

    void ObjectFile::navlight(Context & root, Object & object, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
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

    Marker ObjectFile::marker(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        Marker marker;
        while(!root.finish())
        {
            Context context = ObjectFile::context(in, &root);
            switch(context.id())
            {
                case Object::HEAD:      marker.add(ObjectFile::markerhead(context, in)); break;
                case Object::KEYFRAME:  marker.add(ObjectFile::keyframe(context, in));   break;
                default:                ObjectFile::debug(context);                      exceptional();
            }
            assertion(context.finish() == 0);
            root.move(context.size());
        }
        return marker;
    }

    Marker::Head ObjectFile::markerhead(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        Marker::Head head;
        x::string name = root.str(in);
        x::string parent = root.str(in);
        // animation start and end time
        x::float32 start = root.real32(in);
        x::float32 end = root.real32(in);
        // position
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

    Keyframe ObjectFile::keyframe(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        Keyframe keyframe;
        while(!root.finish())
        {
            ObjectFile::Context context = ObjectFile::context(in, &root);
            ObjectFile::debug(context);
            switch(context.id())
            {
                case Object::BOUNDARY:  keyframe.add(ObjectFile::boundary(context, in));    break;
                default:                ObjectFile::debug(context);                         exceptional();
            }
            assertion(context.finish() == 0);
            root.move(context.size());
        }

        return keyframe;
    }

    Boundary ObjectFile::boundary(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
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

    Collision ObjectFile::collision(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        Collision collision;
        x::string name = root.str(in);
        while(!root.finish())
        {
            Context context = ObjectFile::context(in, &root);
            switch(context.id())
            {
                case Object::BOX:       collision.add(ObjectFile::box(context, in));        break;
                case Object::SPHERE:    collision.add(ObjectFile::sphere(context, in));     break;
                case Object::TRIANGLES: collision.add(ObjectFile::triangles(context, in));  break;
                default:                ObjectFile::debug(context);                         exceptional();
            }
            assertion(context.finish() == 0);
            root.move(context.size());
        }
        return collision;
    }

    Box ObjectFile::box(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
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

    Sphere ObjectFile::sphere(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
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

    Triangles ObjectFile::triangles(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        Triangles triangles;
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
        return triangles;
    }

    Basicmesh ObjectFile::basicmesh(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        Basicmesh basicmesh;
        while(!root.finish())
        {
            Context context = ObjectFile::context(in, &root);
            switch(context.id())
            {
                case Object::DESCRIPTION:   basicmesh.add(ObjectFile::description(context, in));    break;
                case Object::BOX:           basicmesh.add(ObjectFile::box(context, in));            break;
                case Object::SPHERE:        basicmesh.add(ObjectFile::sphere(context, in));         break;
                case Object::TRIANGLES:     basicmesh.add(ObjectFile::triangles(context, in));      break;
                case Object::SUBDIVISION:   basicmesh.add(ObjectFile::subdivision(context, in));    break;
                case Object::NORMALS:       ObjectFile::normals(context, basicmesh, in);            break;
                default:                    ObjectFile::debug(context);                             exceptional();
            }
            root.move(context.size());
            assertion(context.finish() == 0);
        }
        return basicmesh;
    }

    Description ObjectFile::description(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        Description description;
        x::string name = root.str(in);
        x::string parent = root.str(in);
        x::uint32 level = root.uinteger32(in);
        assertion(root.finish() == 0);
        return description;
    }

    void ObjectFile::normals(Context & root, Basicmesh & basicmesh, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
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

    Subdivision ObjectFile::subdivision(Context & root, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
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

    void ObjectFile::information(Context & root, Object & object, x::file::input::stream & in)
    {
        ObjectFile::debug(root);
        Information information;
        while(!root.finish())
        {
            Context context = ObjectFile::context(in, &root);
            switch(context.id())
            {
                case Object::OWNER:     information.owner(context.str(in)); break;
                default:                ObjectFile::debug(context);         exceptional();
            }
            assertion(context.finish() == 0);
            root.move(context.size());
        }
        object.add(information);
    }
}
