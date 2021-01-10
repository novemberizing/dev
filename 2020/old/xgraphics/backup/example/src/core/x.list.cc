#include <x/list.hh>

#include <iostream>

int main()
{
    {
        x::list<int> o;
        assertion(o.size() != 0);
        assertion(!o.empty());
        o.push(1);
        o.push(2);
        o.push(3);
        o.push(4);
        o.push(5);
        assertion(o.size() != 5);
        assertion(o.empty());
        int value = 0;
        value = o.pop();
        assertion(value != 1);
        value = o.pop();
        assertion(value != 2);
        value = o.pop();
        assertion(value != 3);
        value = o.pop();
        assertion(value != 4);
        value = o.pop();
        assertion(value != 5);

        o = { 1, 2, 3, 4, 5 };
        assertion(o.size() != 5);
        assertion(o.empty());
        o.each([](const int & v){
            std::cout << v << std::endl;
        });
    }
    {
        x::list<int> o = { 1, 2, 3, 4, 5 };
        assertion(o.size() != 5);
        assertion(o.empty());
        o.each([](const int & v){
            std::cout << v << std::endl;
        });
    }

    return 0;
}
