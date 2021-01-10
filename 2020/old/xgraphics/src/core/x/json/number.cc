#include "number.hh"

namespace x
{
    namespace json
    {
        x::json::number * number::from(const x::string & s)
        {
            x::uint64 start = 0;
            for(x::uint64 i = 0; i < s.size(); i++)
            {
                if(s[i] == ' ' || s[i] == '\r' || s[i] == '\n' || s[i] == '\t')
                {
                    start = i;
                    continue;
                }
                break;
            }
            x::uint64 end = 0;
            if((48 <= s[start] && s[start] <= 57) || s[start] == '-')
            {
                char * end = nullptr;
                double value = __core_strtod(&s[start], &end);
                if(end - s.str() < s.size())
                {
                    for(x::uint64 i = 0; end[i]==0; i++)
                    {
                        if(end[i] == ' ' || end[i] == '\r' || end[i] == '\n' || end[i] == '\t')
                        {
                            exceptional();
                        }
                    }
                }
                return new x::json::number(value);
            }
            else
            {
                exceptional();
            }
        }
    }
}
