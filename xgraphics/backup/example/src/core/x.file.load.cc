#include <x/file.hh>
#include <x/console.hh>

int main(int argc, char ** argv)
{
    {
        x::bytes data = x::file::data("/home/sean/Workspace/discomplexity/xgraphics/example/res/hello.txt");
    }
    {
        x::string data = x::file::text("/home/sean/Workspace/discomplexity/xgraphics/example/res/hello.txt");
        x::console::out << data  << x::endl;
    }

    return 0;
}
