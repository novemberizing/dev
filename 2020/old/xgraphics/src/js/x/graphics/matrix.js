import Vector from './vector.js';

export default class Matrix
{
    static identity()
    {
        return [1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1];
    }

    static zero()
    {
        return [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
    }

    static deepcopy(m)
    {
        let result = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
        for(let i = 0; i < result.length; i++)
        {
            result[i] = m[i];
        }
        return result;
    }

    static lookat(eye, center, up)
    {
        let f = Vector.normalize(Vector.minus(center, eye));
        let s = Vector.normalize(Vector.cross(f, up));
        let u = Vector.cross(s, f);
        let result = Matrix.identity();
        result[0 * 4 + 0] =  s[0];
        result[1 * 4 + 0] =  s[1];
        result[2 * 4 + 0] =  s[2];
        result[0 * 4 + 1] =  u[0];
        result[1 * 4 + 1] =  u[1];
        result[2 * 4 + 1] =  u[2];
        result[0 * 4 + 2] = -f[0];
        result[1 * 4 + 2] = -f[1];
        result[2 * 4 + 2] = -f[2];
        result[3 * 4 + 0] = -Vector.dot(s, eye);
        result[3 * 4 + 1] = -Vector.dot(u, eye);
        result[3 * 4 + 2] =  Vector.dot(f, eye);
        return result;
    }

    static perspective(fovy, aspect, near, far)
    {
        let half = Math.tan(fovy / 2.0);
        let result = Matrix.zero();
        result[        0] = 1.0 / (aspect * half);
        result[    4 + 1] = 1.0 / half;
        result[2 * 4 + 2] = (far + near) / (near - far);
        result[2 * 4 + 3] = -1.0;
        result[3 * 4 + 2] = -(2.0 * far * near) / (far - near);
        return result;
    }

    static multiply(x, y)
    {
        let result = Matrix.zero();
        result[0 * 4 + 0] = x[0 * 4 + 0] * y[0 * 4 + 0] + x[0 * 4 + 1] * y[1 * 4 + 0] + x[0 * 4 + 2] * y[2 * 4 + 0] + x[0 * 4 + 3] * y[3 * 4 + 0];
        result[0 * 4 + 1] = x[0 * 4 + 0] * y[0 * 4 + 1] + x[0 * 4 + 1] * y[1 * 4 + 1] + x[0 * 4 + 2] * y[2 * 4 + 1] + x[0 * 4 + 3] * y[3 * 4 + 1];
        result[0 * 4 + 2] = x[0 * 4 + 0] * y[0 * 4 + 2] + x[0 * 4 + 1] * y[1 * 4 + 2] + x[0 * 4 + 2] * y[2 * 4 + 2] + x[0 * 4 + 3] * y[3 * 4 + 2];
        result[0 * 4 + 3] = x[0 * 4 + 0] * y[0 * 4 + 3] + x[0 * 4 + 1] * y[1 * 4 + 3] + x[0 * 4 + 2] * y[2 * 4 + 3] + x[0 * 4 + 3] * y[3 * 4 + 3];

        result[1 * 4 + 0] = x[1 * 4 + 0] * y[0 * 4 + 0] + x[1 * 4 + 1] * y[1 * 4 + 0] + x[1 * 4 + 2] * y[2 * 4 + 0] + x[1 * 4 + 3] * y[3 * 4 + 0];
        result[1 * 4 + 1] = x[1 * 4 + 0] * y[0 * 4 + 1] + x[1 * 4 + 1] * y[1 * 4 + 1] + x[1 * 4 + 2] * y[2 * 4 + 1] + x[1 * 4 + 3] * y[3 * 4 + 1];
        result[1 * 4 + 2] = x[1 * 4 + 0] * y[0 * 4 + 2] + x[1 * 4 + 1] * y[1 * 4 + 2] + x[1 * 4 + 2] * y[2 * 4 + 2] + x[1 * 4 + 3] * y[3 * 4 + 2];
        result[1 * 4 + 3] = x[1 * 4 + 0] * y[0 * 4 + 3] + x[1 * 4 + 1] * y[1 * 4 + 3] + x[1 * 4 + 2] * y[2 * 4 + 3] + x[1 * 4 + 3] * y[3 * 4 + 3];

        result[2 * 4 + 0] = x[2 * 4 + 0] * y[0 * 4 + 0] + x[2 * 4 + 1] * y[1 * 4 + 0] + x[2 * 4 + 2] * y[2 * 4 + 0] + x[2 * 4 + 3] * y[3 * 4 + 0];
        result[2 * 4 + 1] = x[2 * 4 + 0] * y[0 * 4 + 1] + x[2 * 4 + 1] * y[1 * 4 + 1] + x[2 * 4 + 2] * y[2 * 4 + 1] + x[2 * 4 + 3] * y[3 * 4 + 1];
        result[2 * 4 + 2] = x[2 * 4 + 0] * y[0 * 4 + 2] + x[2 * 4 + 1] * y[1 * 4 + 2] + x[2 * 4 + 2] * y[2 * 4 + 2] + x[2 * 4 + 3] * y[3 * 4 + 2];
        result[2 * 4 + 3] = x[2 * 4 + 0] * y[0 * 4 + 3] + x[2 * 4 + 1] * y[1 * 4 + 3] + x[2 * 4 + 2] * y[2 * 4 + 3] + x[2 * 4 + 3] * y[3 * 4 + 3];

        result[3 * 4 + 0] = x[3 * 4 + 0] * y[0 * 4 + 0] + x[3 * 4 + 1] * y[1 * 4 + 0] + x[3 * 4 + 2] * y[2 * 4 + 0] + x[3 * 4 + 3] * y[3 * 4 + 0];
        result[3 * 4 + 1] = x[3 * 4 + 0] * y[0 * 4 + 1] + x[3 * 4 + 1] * y[1 * 4 + 1] + x[3 * 4 + 2] * y[2 * 4 + 1] + x[3 * 4 + 3] * y[3 * 4 + 1];
        result[3 * 4 + 2] = x[3 * 4 + 0] * y[0 * 4 + 2] + x[3 * 4 + 1] * y[1 * 4 + 2] + x[3 * 4 + 2] * y[2 * 4 + 2] + x[3 * 4 + 3] * y[3 * 4 + 2];
        result[3 * 4 + 3] = x[3 * 4 + 0] * y[0 * 4 + 3] + x[3 * 4 + 1] * y[1 * 4 + 3] + x[3 * 4 + 2] * y[2 * 4 + 3] + x[3 * 4 + 3] * y[3 * 4 + 3];
        return result;
    }

    static translate(m, v)
    {
        let result = Matrix.deepcopy(m);

        result[3 * 4 + 0] = m[0 * 4 + 0] * v[0] + m[1 * 4 + 0] * v[1] + m[2 * 4 + 0] * v[2] + m[3 * 4 + 0];
        result[3 * 4 + 1] = m[0 * 4 + 1] * v[0] + m[1 * 4 + 1] * v[1] + m[2 * 4 + 1] * v[2] + m[3 * 4 + 1];
        result[3 * 4 + 2] = m[0 * 4 + 2] * v[0] + m[1 * 4 + 2] * v[1] + m[2 * 4 + 2] * v[2] + m[3 * 4 + 2];
        result[3 * 4 + 3] = m[0 * 4 + 3] * v[0] + m[1 * 4 + 3] * v[1] + m[2 * 4 + 3] * v[2] + m[3 * 4 + 3];
        return result;
    }

    static rotate(m, angle, v)
    {
        let c = Math.cos(angle);
        let s = Math.sin(angle);
        let axis = Vector.normalize(v);
        let temp = Vector.multiply(axis, (1 - c));
        let rotation = Matrix.zero();

        rotation[0 * 4 + 0] = c + temp[0] * axis[0];
        rotation[0 * 4 + 1] = temp[0] * axis[1] + s * axis[2];
        rotation[0 * 4 + 2] = temp[0] * axis[2] - s * axis[1];

        rotation[1 * 4 + 0] = temp[1] * axis[0] - s * axis[2];
        rotation[1 * 4 + 1] = c + temp[1] * axis[1];
        rotation[1 * 4 + 2] = temp[1] * axis[2] + s * axis[0];

        rotation[2 * 4 + 0] = temp[2] * axis[0] + s * axis[1];
        rotation[2 * 4 + 1] = temp[2] * axis[1] - s * axis[0];
        rotation[2 * 4 + 2] = c + temp[2] * axis[2];

        let result = Matrix.zero();

        result[0 * 4 + 0] = m[0 * 4 + 0] * rotation[0 * 4 + 0] + m[1 * 4 + 0] * rotation[0 * 4 + 1] + m[2 * 4 + 0] * rotation[0 * 4 + 2];
        result[0 * 4 + 1] = m[0 * 4 + 1] * rotation[0 * 4 + 0] + m[1 * 4 + 1] * rotation[0 * 4 + 1] + m[2 * 4 + 1] * rotation[0 * 4 + 2];
        result[0 * 4 + 2] = m[0 * 4 + 2] * rotation[0 * 4 + 0] + m[1 * 4 + 2] * rotation[0 * 4 + 1] + m[2 * 4 + 2] * rotation[0 * 4 + 2];
        result[0 * 4 + 3] = m[0 * 4 + 3] * rotation[0 * 4 + 0] + m[1 * 4 + 3] * rotation[0 * 4 + 1] + m[2 * 4 + 3] * rotation[0 * 4 + 2];

        result[1 * 4 + 0] = m[0 * 4 + 0] * rotation[1 * 4 + 0] + m[1 * 4 + 0] * rotation[1 * 4 + 1] + m[2 * 4 + 0] * rotation[1 * 4 + 2];
        result[1 * 4 + 1] = m[0 * 4 + 1] * rotation[1 * 4 + 0] + m[1 * 4 + 1] * rotation[1 * 4 + 1] + m[2 * 4 + 1] * rotation[1 * 4 + 2];
        result[1 * 4 + 2] = m[0 * 4 + 2] * rotation[1 * 4 + 0] + m[1 * 4 + 2] * rotation[1 * 4 + 1] + m[2 * 4 + 2] * rotation[1 * 4 + 2];
        result[1 * 4 + 3] = m[0 * 4 + 3] * rotation[1 * 4 + 0] + m[1 * 4 + 3] * rotation[1 * 4 + 1] + m[2 * 4 + 3] * rotation[1 * 4 + 2];

        result[2 * 4 + 0] = m[0 * 4 + 0] * rotation[2 * 4 + 0] + m[1 * 4 + 0] * rotation[2 * 4 + 1] + m[2 * 4 + 0] * rotation[2 * 4 + 2];
        result[2 * 4 + 1] = m[0 * 4 + 1] * rotation[2 * 4 + 0] + m[1 * 4 + 1] * rotation[2 * 4 + 1] + m[2 * 4 + 1] * rotation[2 * 4 + 2];
        result[2 * 4 + 2] = m[0 * 4 + 2] * rotation[2 * 4 + 0] + m[1 * 4 + 2] * rotation[2 * 4 + 1] + m[2 * 4 + 2] * rotation[2 * 4 + 2];
        result[2 * 4 + 3] = m[0 * 4 + 3] * rotation[2 * 4 + 0] + m[1 * 4 + 3] * rotation[2 * 4 + 1] + m[2 * 4 + 3] * rotation[2 * 4 + 2];

        result[3 * 4 + 0] = m[3 * 4 + 0];
        result[3 * 4 + 1] = m[3 * 4 + 1];
        result[3 * 4 + 2] = m[3 * 4 + 2];
        result[3 * 4 + 3] = m[3 * 4 + 3];

        return result;
    }

    static scale(m, v)
    {
        let result = Matrix.zero();
        result[0 * 4 + 0] = m[0 * 4 + 0] * v[0];
        result[0 * 4 + 1] = m[0 * 4 + 1] * v[0];
        result[0 * 4 + 2] = m[0 * 4 + 2] * v[0];
        result[0 * 4 + 3] = m[0 * 4 + 3] * v[0];

        result[1 * 4 + 0] = m[1 * 4 + 0] * v[1];
        result[1 * 4 + 1] = m[1 * 4 + 1] * v[1];
        result[1 * 4 + 2] = m[1 * 4 + 2] * v[1];
        result[1 * 4 + 3] = m[1 * 4 + 3] * v[1];

        result[2 * 4 + 0] = m[2 * 4 + 0] * v[2];
        result[2 * 4 + 1] = m[2 * 4 + 1] * v[2];
        result[2 * 4 + 2] = m[2 * 4 + 2] * v[2];
        result[2 * 4 + 3] = m[2 * 4 + 3] * v[2];

        result[3 * 4 + 0] = m[3 * 4 + 0];
        result[3 * 4 + 1] = m[3 * 4 + 1];
        result[3 * 4 + 2] = m[3 * 4 + 2];
        result[3 * 4 + 3] = m[3 * 4 + 3];
        return result;
    }

    static vectorMultiply(m, v)
    {
        let result = [0, 0, 0, 0];
        result[0] = m[0 * 4 + 0] * v[0] + m[0 * 4 + 1] * v[1] + m[0 * 4 + 2] * v[2] + m[0 * 4 + 3] * v[3];
        result[1] = m[1 * 4 + 0] * v[0] + m[1 * 4 + 1] * v[1] + m[1 * 4 + 2] * v[2] + m[1 * 4 + 3] * v[3];
        result[2] = m[2 * 4 + 0] * v[0] + m[2 * 4 + 1] * v[1] + m[2 * 4 + 2] * v[2] + m[2 * 4 + 3] * v[3];
        result[3] = m[3 * 4 + 0] * v[0] + m[3 * 4 + 1] * v[1] + m[3 * 4 + 2] * v[2] + m[3 * 4 + 3] * v[3];
        return result;
    }
}
