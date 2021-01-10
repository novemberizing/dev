import Executor from '../core/executor.js';
import Camera from './camera.js';
import Projection from './projection.js';
import Light from './light.js';
import Surface from './surface.js';
import Matrix from './matrix.js';
import Command from '../core/command.js';

let application = null;

export class Application extends Executor
{
    static __loading()
    {
        // application.__progress += 0.01;
        application.__progress = application.__current / application.__total;
        // console.log(application.current);
        if(application.finish)
        {
            console.log("end loading");
            application.__references = new Map();
            application.render();
            if(application.__defer)
            {

                application.__defer.call();
            }
        }
        else
        {
            application.render();
            setTimeout(Application.__loading, 1000/30);
        }
    }

    constructor()
    {
        super();

        this.__x = 0;
        this.__y = 0;
        this.__name = "";
        this.__shaders = new Map();
        this.__programs = new Map();
        this.__surface = null;
        this.__objects = new Map();
        this.__references = new Map();
        this.__major = 4;
        this.__minor = 5;
        this.__mode = 0;
        this.__progress = 0;
        this.__finish = false;
        this.__defer = null;

        if(!this.__surface)
        {
            let canvas = document.createElement("canvas");
            canvas.width = document.body.clientWidth;
            canvas.height = document.body.clientHeight;
            document.body.appendChild(canvas);
            this.__surface = new Surface(canvas);
            this.__surface.initialize();
        }
    }

    run(func)
    {
        this.__defer = new Command((resolve, reject) => {
            this.__programs.forEach(program => program.load(this));
            this.__objects.forEach(object => object.load(this));

            func();

            this.render();
        }, 1);
        if(this.__finish)
        {
            this.__defer.call();
            this.__defer = null;
            console.log("defer call");
        }
    }

    loading(commands)
    {
        this.__programs.forEach(program => program.load(this));
        this.__objects.forEach(object => object.load(this));

        commands.forEach(command => {
            this.dispatch(command);
        });

        console.log("total", this.__total);

        // this.render();
        Application.__loading();

        return this.execute();
    }

    render()
    {
        // console.log("application render");
        this.gl.viewport(0, 0, this.gl.canvas.width, this.gl.canvas.height);
        this.gl.clearColor(this.background[0], this.background[1], this.background[2], this.background[3]);
        this.gl.clear(this.gl.COLOR_BUFFER_BIT | this.gl.COLOR_DEPTH_BIT);

        this.__references.forEach((reference, name) => {
            // console.log("render", name);
            reference.render(application, Matrix.identity(), 0);
        });
    }

    shader(o)
    {
        this.__shaders.set(o.name, o);
        return o;
    }

    program(o)
    {
        this.__programs.set(o.name, o);
        return o;
    }

    object(o)
    {
        this.__objects.set(o.name, o);
        return o;
    }

    reference(o)
    {
        this.__references.set(o.name, o);
        return o;
    }

    get gl() { return this.__surface.gl; }
    get extension(){ return this.__surface.extension; }
    get programs() { return this.__programs; }
    get shaders(){ return this.__shaders; }
    get objects(){ return this.__objects; }
    get background() { return this.__surface.background; }
    get light(){ return this.__surface.light; }
    get camera(){ return this.__surface.camera; }
    get projection(){ return this.__surface.projection; }
    get progress(){ return this.__progress; }
    get finish(){ return this.__finish; }
    get width(){ return this.__surface.width; }
    get height(){ return this.__surface.height; }

    set finish(v){ this.__finish = v; }
}

application = new Application();

export { application as default };
