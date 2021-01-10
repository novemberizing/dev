#include <xSpace/Application.hh>

int main(int argc, char ** argv)
{
    xSpace::Application & application = xSpace::Application::init(argc, argv);

    return application.run();
}
