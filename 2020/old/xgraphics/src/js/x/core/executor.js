
export default class Executor
{
    constructor()
    {
        this.__queue = null;
        this.__total = 0;
        this.__current = 0;
        this.__index = 0;
    }

    dispatch(command)
    {
        if(command)
        {
            this.__queue = this.__queue || [];
            this.__queue.push(command);
            this.__total = this.__total + command.weight;
        }
    }

    call(resolve, reject)
    {
        let results = [];
        if(this.__index < this.__queue.length)
        {
            this.__queue[this.__index].call()
                                      .then(o => {
                                          results.push(o);
                                          this.__index++;
                                          this.call(resolve, reject);
                                      })
                                      .catch(e => reject(e));
        }
        else
        {
            resolve(results);
        }
    }

    execute()
    {
        return new Promise((resolve, reject) => this.call(resolve, reject));

        /**
        console.log("execute");
        return new Promise((resolve, reject) => {
            if(this.__index < this.__queue.length)
            {

            }
        });
        */
        // if(this.__queue)
        // {
        //     return Promise.all(this.__queue);
        // }
        // return Promise.reject(new Error());
    }
}
