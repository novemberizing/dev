import Light from './light.js';
import Camera from './camera.js';
import Projection from './projection.js';

export default class Surface
{
    constructor(canvas)
    {
        this.__canvas = canvas;
        this.__context = null;
        this.__background = [0, 0, 0, 1];
        this.__references = new Map();
        this.__light = new Light();
        this.__camera = new Camera();
        this.__projection = new Projection();

        this.__canvas.style.backgroundColor = "black";

        // background-color : black;
    }

    init()
    {
        if(!this.__context)
        {
            this.__context = this.__canvas.getContext("webgl") || this.__canvas.getContext("experimental-webgl");
            this.__context.viewport(0, 0, this.__canvas.width, this.__canvas.height);
            this.__context.enable(this.__context.DEPTH_TEST);
            this.__context.depthFunc(this.__context.LESS);
            this.__context.enable(this.__context.BLEND);
            this.__context.blendFunc(this.__context.SRC_ALPHA, this.__context.ONE_MINUS_SRC_ALPHA);
        }
    }

    get gl() { return this.__context; }

    get background(){ return this.__background; }
}
