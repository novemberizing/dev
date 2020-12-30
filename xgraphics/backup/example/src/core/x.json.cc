#include <x/json.hh>
#include <x/console.hh>

int main(int argc, char ** argv)
{
    {
        x::json::value * n = x::json::value::from("1000");
        x::console::out << *n << x::endl;
        delete n;
    }

    {
        x::json::value * n = x::json::value::from("      \t 1000.005   \t\r\n");
        x::console::out << *n << x::endl;
        delete n;
    }

    {
        x::json::value * s = x::json::value::from("\"helloworld\"");
        x::console::out << *s << x::endl;
        delete s;
    }
    {
        x::json::value * s = x::json::value::from("\"hello\\\" \\\" \\'world\"");
        x::console::out << *s << x::endl;
        delete s;
    }

    {
        try
        {
            x::json::value * s = x::json::value::from("\"hello\\\" \\\" \\'world\"     d");
            x::console::out << *s << x::endl;
            delete s;
        }
        catch(const x::exception & e)
        {
            x::console::out << "success" << x::endl;
        }

    }

    {
        try
        {
            x::json::value * s = x::json::value::from("     dlfkjd \"hello\\\" \\\" \\'world\"     d");
            x::console::out << *s << x::endl;
            delete s;
        }
        catch(const x::exception & e)
        {
            x::console::out << "success" << x::endl;
        }

    }
    {
        x::json::value * a = x::json::value::from("[1, \"hello\", 2, [1,2,3] ]");
        x::console::out << *a << x::endl;
        delete a;

    }
    {
        try
        {
            x::json::value * a = x::json::value::from("[1, \"hello\", 2, [1,] ]");
            x::console::out << *a << x::endl;
            delete a;
        }
        catch(const x::exception & e)
        {
            x::console::out << "success" << x::endl;
        }
    }
    {
        try
        {
            x::json::value * a = x::json::value::from("[1, \"hello\", 2, [1,,] ]");
            x::console::out << *a << x::endl;
            delete a;
        }
        catch(const x::exception & e)
        {
            x::console::out << "success" << x::endl;
        }
    }

    {
        x::json::value * o = x::json::value::from("{            \"name\": \"salamis\",            \"type\": \"ship\"        }");
        x::console::out << *o << x::endl;
        delete o;
    }
    return 0;
}
