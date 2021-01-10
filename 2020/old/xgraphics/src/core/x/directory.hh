#ifndef   __X__DIRECTORY__HH__
#define   __X__DIRECTORY__HH__

#include <x/string.hh>
#include <x/array.hh>

#include <x/console.hh>

namespace x
{
    class directory
    {
    public:     static x::string current()
                {
                    char buf[1024];
                    __core_getcwd(buf, 1024);
                    return x::string(buf);
                }
    public:     static x::string current(const x::string & execution)
                {
                    x::string path = x::directory::current() + "/" + execution;

                    x::array<x::string> strings = path.split('/');

                    path = "";

                    if(strings.size() > 0)
                    {
                        for(x::uint64 i = 0; i < (strings.size() - 1); i++)
                        {
                            if(strings[i].size() > 0)
                            {
                                if(strings[i] == ".")
                                {
                                    continue;
                                }
                                else if(strings[i] == "..")
                                {
                                    x::uint64 offset = path.find('/', path.size() - 1 ,x::backward);
                                    path.erase(offset, path.size() - offset);
                                }
                                else
                                {
                                    path += '/';
                                    path += strings[i];
                                }
                            }
                        }
                    }
                    else
                    {
                        path += '/';
                    }

                    return path;
                }
    };
}

#endif // __X__DIRECTORY__HH__
