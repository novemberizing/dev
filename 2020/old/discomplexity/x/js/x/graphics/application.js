import Surface from './surface.js';
import Executor from '../core/executor.js';
import Objects from './objects.js';
import Matrix from './matrix.js';

class Application extends Executor
{
    constructor()
    {
        super();

        this.__x = 0;
        this.__y = 0;
        this.__width = 0;
        this.__height = 0;
        this.__name = "";
        this.__shaders = new Map();
        this.__programs = new Map();
        this.__surface = null;
        this.__objects = new Objects();
        this.__major = 4;
        this.__minor = 5;
        this.__mode = 0;
    }

    init()
    {
        // create canvas and
        if(!this.__surface)
        {
            let canvas = document.createElement("canvas");
            canvas.width = document.body.clientWidth;
            canvas.height = document.body.clientHeight;
            document.body.appendChild(canvas);
            this.__surface = new Surface(canvas);
            this.__surface.init();
        }
    }

    run()
    {
        this.__programs.forEach(program => {
            program.create(this.__surface.gl, this);
        });
        console.log(this.__objects);
        this.__objects.init(this.__surface.gl);
        this.render();
    }

    render()
    {
        console.log("application render");
        this.gl.viewport(0, 0, this.gl.canvas.width, this.gl.canvas.height);
        this.gl.clearColor(this.background[0], this.background[1], this.background[2], this.background[3]);
        this.gl.clear(this.gl.COLOR_BUFFER_BIT | this.gl.COLOR_DEPTH_BIT);
        this.__objects.render(this.gl, Matrix.identity(), 0);
    }

    shader(o)
    {
        this.__shaders.set(o.name, o);
        return o;
    }

    get gl() { return this.__surface.gl; }
    get programs() { return this.__programs; }
    get shaders(){ return this.__shaders; }
    get objects(){ return this.__objects; }
    get background() { return this.__surface.background; }
}

let application = new Application();

export { application as default };
