
const __degree = 57.295779513082320876798154814105;
const __radian = 0.01745329251994329576923690768489;

export default class Vector
{
    static four(o, end)
    {
        o = o || [];

        if(o.length < 4)
        {
            while(o.length < 3)
            {
                o.push(0);
            }
            o.push(end || 0);
            return o;
        }
        else
        {
            return o.splice(0, 4);
        }
    }

    static two(o)
    {
        o = o || [];

        if(o.length < 2)
        {
            while(o.length < 2)
            {
                o.push(0);
            }
            return o;
        }
        else
        {
            return o.splice(0, 2);
        }
    }

    static degree(o)
    {
        let result = [0, 0, 0, 0];
        result[0] = o[0] * __degree;
        result[1] = o[1] * __degree;
        result[2] = o[2] * __degree;
        result[3] = o[3] * __degree;
        return result;
    }

    static radian(o)
    {
        let result = [0, 0, 0, 0];
        result[0] = o[0] * __radian;
        result[1] = o[1] * __radian;
        result[2] = o[2] * __radian;
        result[3] = o[3] * __radian;
        return result;
    }

    static dot(x, y)
    {
        let result = 0;
        for(let i = 0; i < 4; i++)
        {
            result += (x[i] * y[i]);
        }
        return result;
    }

    static normalize(o)
    {
        let dot = Math.sqrt(Vector.dot(o, o));
        let result = [0, 0, 0, 0];
        for(let i = 0; i < 4; i++)
        {
            result[i] = (o[i]/dot);
        }
        return result;
    }

    static cross(x, y)
    {
        let result = [0, 0, 0, 0];
        result[0] = (x[1] * y[2] - x[2] * y[1]);
        result[1] = (x[2] * y[0] - x[0] * y[2]);
        result[2] = (x[0] * y[1] - x[1] * y[0]);
        return result;
    }

    static minus(x, y)
    {
        let result = [0, 0, 0, 0];
        for(let i = 0; i < 4; i++)
        {
            result[i] = (x[i] - y[i]);
        }
        return result;
    }

    static plus(x, y)
    {
        let result = [0, 0, 0, 0];
        for(let i = 0; i < 4; i++)
        {
            result[i] = (x[i] + y[i]);
        }
        return result;
    }

    static multiply(v, c)
    {
        let result = [0, 0, 0, 0];
        for(let i = 0; i < 4; i++)
        {
            result[i] = v[i] * c;
        }
        return result;
    }
}
