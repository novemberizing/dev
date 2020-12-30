#include <x/core.hh>
#include <x/array.hh>

#include <iostream>

int main()
{
    {
        x::array<int> o;
        std::cout << o.size() << std::endl;
        std::cout << o.empty() << std::endl;
    }
    {
        x::array<int> o = { 1, 2, 3, 4, 5 };
        assertion(o.size() != 5);
        assertion(o.empty());
        o.each([](const int & v){ std::cout << v << std::endl; });
        assertion(o[0] != 1);
        assertion(o[1] != 2);
        assertion(o[2] != 3);
        assertion(o[3] != 4);
        assertion(o[4] != 5);
        o.clear();
        assertion(o.size() != 0);
        assertion(!o.empty());
        o = { 1, 2, 3, 4, 5 };
        assertion(o[0] != 1);
        assertion(o[1] != 2);
        assertion(o[2] != 3);
        assertion(o[3] != 4);
        assertion(o[4] != 5);
    }
    {
        x::array<int> o(10, 5);
        assertion(o.size() != 5);
        assertion(o.empty());
        assertion(o[0] != 10);
        assertion(o[1] != 10);
        assertion(o[2] != 10);
        assertion(o[3] != 10);
        assertion(o[4] != 10);
        o.each([](int & v){
            std::cout << v << std::endl;
            v = 20;
        });
        assertion(o[0] != 20);
        assertion(o[1] != 20);
        assertion(o[2] != 20);
        assertion(o[3] != 20);
        assertion(o[4] != 20);
    }
    {
        int source[5] = { 1, 2, 3, 4, 5 };
        x::array<int> o(source, 3);
        assertion(o[0] != 1);
        assertion(o[1] != 2);
        assertion(o[2] != 3);
        assertion(o.size() != 3);
        assertion(o.empty());
    }
    {
        x::array<int> source = { 6, 7, 8, 9, 10 };
        x::array<int> o = { 1, 2, 3, 4, 5 };
        o.each([](const int & v){ std::cout << v << std::endl; });
        o+=source;
        o.each([](const int & v){ std::cout << v << std::endl; });
        assertion(o[0] != 1);
        assertion(o[1] != 2);
        assertion(o[2] != 3);
        assertion(o[3] != 4);
        assertion(o[4] != 5);
        assertion(o[5] != 6);
        assertion(o[6] != 7);
        assertion(o[7] != 8);
        assertion(o[8] != 9);
        assertion(o[9] != 10);
        o += { 11, 12, 13, 14, 15 };
        assertion(o[10] != 11);
        assertion(o[11] != 12);
        assertion(o[12] != 13);
        assertion(o[13] != 14);
        assertion(o[14] != 15);
    }
    return 0;
}
