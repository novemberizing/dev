#include <x/map.hh>
#include <x/random.hh>

#include <iostream>

int main()
{
    x::random & random = x::random::get();

    x::map<int, int> o;
    for(x::uint64 i = 0; i < 128; i++)
    {
        o.put(random.integer32(128), random.integer32(128));
    }
    std::cout << o.size() << std::endl;
    for(x::uint64 i = 0; i < 64; i++)
    {
        o.del(random.integer32(128));
    }
    std::cout << o.size() << std::endl;
    o.each([](const int & key, int & value){
        std::cout << key << "=>" << value << std::endl;
        x::random & random = x::random::get();
        value = random.integer32(128);
    });
    o.each([](const int & key, const int & value){
        std::cout << key << "=>" << value << std::endl;
    });
    return 0;
}
