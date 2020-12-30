
export default class Command
{
    constructor(func, weight)
    {
        this.__func = func;
        this.__weight = weight;
    }

    call() {
        return new Promise((resolve, reject) => {
            this.__func(resolve, reject);
        });
    }

    get weight(){ return this.__weight; }
}
