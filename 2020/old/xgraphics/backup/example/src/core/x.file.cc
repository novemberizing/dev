#include <x/file.hh>
#include <x/console.hh>

int main()
{
    x::file::input::stream is("/home/sean/Workspace/discomplexity/xgraphics/example/res/helloworld.txt");
    is.open();
    printf("%f\n", is.float32());
    printf("%f\n", is.float64());
    printf("%u\n", is.byte());
    printf("%c\n", is.character());
    printf("%d\n", is.int16());
    printf("%d\n", is.uint16());
    printf("%d\n", is.int32());
    printf("%u\n", is.uint32());
    printf("%ld\n", is.int64());
    printf("%lu\n", is.uint64());
    x::string o = is.str(6);
    x::console::out << o << x::endl;
    x::bytes o2 = is.data(6);
    x::console::out << o2.size() << x::endl;
    is.close();

    x::file f("/home/sean/Workspace/discomplexity/xgraphics/homeworld2/res/sample.hod");

    x::console::out << f.name() << x::endl << x::flush;
    x::console::out << f.path() << x::endl << x::flush;
    x::console::out << f.extension() << x::endl << x::flush;

    f = x::file("/home/sean/Workspace/discomplexity/xgraphics/homeworld2/res/sample");

    x::console::out << f.name() << x::endl << x::flush;
    x::console::out << f.path() << x::endl << x::flush;
    x::console::out << f.extension() << x::endl << x::flush;

    f = x::file("/home/sean/Workspace/discomplexity/xgraphics/homeworld2/res/.sample");

    x::console::out << f.name() << x::endl << x::flush;
    x::console::out << f.path() << x::endl << x::flush;
    x::console::out << f.extension() << x::endl << x::flush;

    f = x::file(".sample");

    x::console::out << f.name() << x::endl << x::flush;
    x::console::out << f.path() << x::endl << x::flush;
    x::console::out << f.extension() << x::endl << x::flush;


    f = x::file("sample");

    x::console::out << f.name() << x::endl << x::flush;
    x::console::out << f.path() << x::endl << x::flush;
    x::console::out << f.extension() << x::endl << x::flush;

    f = x::file("/home/sean/Workspace/discomplexity/xgraphics/homeworld2/res");

    x::console::out << f.name() << x::endl << x::flush;
    x::console::out << f.path() << x::endl << x::flush;
    x::console::out << f.extension() << x::endl << x::flush;
    x::console::out << f.type() << x::endl << x::flush;
    if(f.children.size() > 0)
    {
        f.children.each([](const x::file & child){
            x::console::out << "child: " << child.name() << x::endl << x::flush;
            x::console::out << "child: " << child.path() << x::endl << x::flush;
            x::console::out << "child: " << child.extension() << x::endl << x::flush;
        });

        f.get([](const x::file & child){
            x::console::out << "child: " << child.path() << x::endl << x::flush;
        });
    }
    else
    {
        x::console::out << "child is none" << x::endl;
    }

    return 0;
}
