#include <x/array.hh>

int main()
{
    x::array<int> source = { 1, 2, 3, 4, 5 };
    x::array<int> o = x::move(source);
    source = { 1, 2, 3, 4, 5 };
    x::array<int> second(x::move(source));
    return 0;
}
