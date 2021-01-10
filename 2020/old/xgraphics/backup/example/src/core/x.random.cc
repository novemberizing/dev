#include <x/random.hh>

#include <iostream>

int main()
{
    x::random & random = x::random::get();

    std::cout << random.integer32() << std::endl;
    std::cout << random.integer32() << std::endl;
    std::cout << random.integer32() << std::endl;
    std::cout << random.integer32() << std::endl;
    std::cout << random.integer32() << std::endl;

    std::cout << random.integer32(16) << std::endl;
    std::cout << random.integer32(16) << std::endl;
    std::cout << random.integer32(16) << std::endl;
    std::cout << random.integer32(16) << std::endl;
    std::cout << random.integer32(16) << std::endl;

    return 0;
}
