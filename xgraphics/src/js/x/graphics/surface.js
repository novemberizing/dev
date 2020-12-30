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
        this.__light = new Light([18, 7, 30, 1], [1, 1, 1, 1], 0.8);
        this.__camera = new Camera([0, 0, 90, 1], [0, 0, 0, 0], [0, 1, 0, 0]);
        this.__projection = new Projection(45, 1, 0.1, 1000.0);
        this.__extension = null;

        this.__canvas.style.backgroundColor = "black";

        // background-color : black;
    }

    initialize()
    {
        if(!this.__context)
        {
            this.__context = this.__canvas.getContext("webgl") || this.__canvas.getContext("experimental-webgl");
            let extension = this.__context.getExtension('OES_vertex_array_object') || this.__context.getExtension('MOZ_OES_vertex_array_object') || this.__context.getExtension('WEBKIT_OES_vertex_array_object');
            this.__extension = { extension };

            this.__context.viewport(0, 0, this.__canvas.width, this.__canvas.height);
            this.__context.enable(this.__context.DEPTH_TEST);
            this.__context.depthFunc(this.__context.LESS);
            this.__context.enable(this.__context.BLEND);
            this.__context.blendFunc(this.__context.SRC_ALPHA, this.__context.ONE_MINUS_SRC_ALPHA);
        }
    }

    get gl() { return this.__context; }
    get extension(){ return this.__extension; }

    get background(){ return this.__background; }

    get width(){ return this.__canvas.width; }
    get height(){ return this.__canvas.height; }
    get light(){ return this.__light; }
    get camera(){ return this.__camera; }
    get projection(){ return this.__projection; }
}
