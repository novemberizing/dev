
export default class Canvas {
    constructor(o) {
        this._element = o;
        this._draws = [];
        this._context = this._element.getContext('2d');
    }

    get context() {
        return this._context;
    }

    push(f) {
        this._draws.push(f);
    }

    draw() {
        this._draws.forEach(func => func());
        window.requestAnimationFrame(()=>this.draw());
    }

    on() {
        this.draw();
    }
}