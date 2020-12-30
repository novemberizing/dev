
export default class Executor
{
    constructor()
    {
        this.__queue = null;
    }

    dispatch(o)
    {
        if(o)
        {
            this.__queue = this.__queue || [];
            this.__queue.push(o);
        }
    }

    execute()
    {
        if(this.__queue)
        {
            return Promise.all(this.__queue);
        }
        return Promise.reject(new Error());
    }
}
