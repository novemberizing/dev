
export default class Mipmap
{
    constructor(width, height, data)
    {
        this.__id;
        this.__width = width;
        this.__height = height;
        this.__data = data;
    }

    get width(){ return this.__width; }
    get height(){ return this.__height; }
    get data(){ return this.__data; }
}
