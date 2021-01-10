#include <x/set.hh>
#include <x/random.hh>

#include <iostream>

int main()
{
    x::random & random = x::random::get();
    {
        x::set<int> o;
        assertion(o.size() != 0);
        assertion(!o.empty());

        o.add(1);
        o.add(2);
        o.add(3);
        o.add(4);
        o.add(5);

        assertion(!o.exist(1));
        assertion(!o.exist(2));
        assertion(!o.exist(3));
        assertion(!o.exist(4));
        assertion(!o.exist(5));

        o.del(3);

        for(x::uint32 i = 0; i < 128; i++)
        {
            o.add(random.integer32(128));
        }

        std::cout << "size => " << o.size() << std::endl;

        for(x::uint32 i = 0; i < 64; i++)
        {
            o.del(random.integer32(128));
        }

        std::cout << "size => " << o.size() << std::endl;

        o.each([](const int key){
            std::cout << key << std::endl;
        });
    }
    return 0;
}
