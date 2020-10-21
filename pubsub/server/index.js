const express = require('express');
const redis = require('redis');
const app = express();

const retry = {
    retry_strategy: function(options) {
        if (options.total_retry_time > 1000 * 60 * 60) {
            // reconnect after
            return 10000;
        }
        if (options.error && options.error.code === "ECONNREFUSED") {
            // reconnect after
            return 5000;
        }
        // reconnect after
        if(options.attempt > 50) {
            options.attempt = 0;
        }
        return Math.min(options.attempt * 100, 3000);
    }
};

class Pubsub {
    constructor() {
        this.client = redis.createClient(retry);
        this.subscriber = redis.createClient(retry);



        this.client.on('error', (e) => { console.log(e); });
        this.client.on('ready', (o) => {});
        this.client.on('connect', (o) => {
            console.log('send all data');
        });
        this.client.on('reconnecting', (o) => { console.log('reconnect'); });
        this.client.on('end', (o) => {});
        this.client.on('warning', (o) => {});

        this.subscriber.on('error', (e) => { console.log(e); });
        this.subscriber.on('ready', (o) => {});
        this.subscriber.on('connect', (o) => {});
        this.subscriber.on('reconnecting', (o) => { console.log('reconnect'); });
        this.subscriber.on('end', (o) => {});
        this.subscriber.on('warning', (o) => {});
        this.subscriber.on('subscribe', (channel, count) => {});
        this.subscriber.on('message', async (channel, message) => {
            console.log(message);
            const session = clients[message];
            if(session) {
                const data = await this.get(message);
                session.res.write(`data: ${JSON.stringify({message:data})}\n\n`);
                console.log('session write');
            } else {
                console.log('no session');
            }
        });
        this.subscriber.subscribe("message");
    }

    async auth(auth) {
        return new Promise((resolve, reject) => {
            try {
                const key = auth;
                // TODO: AUTH 를 통해서 저장된 공간의 키를 가지고 옵니다.
                resolve(key);
            } catch(e) {
                reject(e);
            }
        });
    }

    async get(key) {
        return new Promise((resolve, reject) => {
            this.client.hgetall(key, (e, v) => {
                if(e) {
                    reject(e);
                    return;
                }
                console.log(v);
                resolve(v);
            });
        });
    }

    async del(key, data) {
        return new Promise((resolve, reject) => {
            console.log(data);
            this.client.hdel(key, data.key, (e, v) => {
                if(e) {
                    reject(e);
                    return;
                }
                resolve(v);
            });
        });
    }

    async put(key, data) {
        return new Promise((resolve, reject) => {
            this.client.hset(key, data.key, data.value, (e, v) => {
                if(e) {
                    reject(e);
                    return;
                }
                this.client.publish('message', key, (e, v) => {
                    if(e) {
                        reject(e);
                        return;
                    }
                    resolve(v);
                });
            });
        });
    }
};

const service = new Pubsub();

const template = `<!DOCTYPE html>
<html>
    <head>
    </head>
    <body>
        <script src="https://cdn.jsdelivr.net/npm/axios/dist/axios.min.js"></script>
        <script type="text/javascript">
            const auth = '93';
            const source = new EventSource("/events/?auth=" + auth, {
                withCredentials: false
            });
            console.log(source);
            source.onmessage = function(e) {
                document.body.innerHTML += e.data + "<br>";
                const data = JSON.parse(e.data);
                console.log(data.message);
                if(data.message) {
                    Object.keys(data.message).forEach(async (k) => {
                        console.log(k);
                        try {
                            document.body.innerHTML += JSON.stringify({key: data.message[k]}) + "<br>";
                            const result = await axios.get('/del/?auth='+auth+'&data='+JSON.stringify({key:k}));
                            document.body.innerHTML += JSON.stringify(result.data) + "<br>";
                        } catch(e) {
                            console.log(e.toString());
                        }

                    });
                }
            }
        </script>
    </body>
</html>`;

let clients = {};

// REMOVE THIS : RELEASE
app.get('/', (req, res) => {
    res.send(template);
});

app.get('/del/', async (req, res) => {
    try {
        console.log('del');
        const key = await service.auth(req.query.auth);
        const data = JSON.parse(req.query.data);
        console.log(data);
        if(key) {
            const result = await service.del(key, data);
            res.send(JSON.stringify(result));
        } else {
            // logging invalid access must close
            console.log('invalid access => without auth key');
            req.socket.close();
        }
    } catch(e) {
        console.log(`exception => ${e.toString()}`);
        req.socket.close();
    }
});

app.get('/put/', async (req, res) => {
    try {
        console.log('put');
        const key = await service.auth(req.query.auth);
        const data = JSON.parse(req.query.data);
        if(key) {
            const result = await service.put(key, data);
            res.send(JSON.stringify(result));
        } else {
            // logging invalid access must close
            console.log('invalid access => without auth key');
            req.socket.close();
        }
    } catch(e) {
        console.log(`exception => ${e.toString()}`);
        req.socket.close();
    }
});

app.get('/events/', async (req, res) => {
    try {
        const key = await service.auth(req.query.auth);
        if(key) {
            console.log(`implement auth check ${key}`);
            // 1. OLD SESSION REMOVE (IF EXIST)
            let session = clients[key];
            if(session) {
                console.log('old session remove');
                try {
                    // PERMIT DUPLICATE DELETE
                    session.req.on('close', ()=>{});
                    session.req.socket.close();
                } catch(e) {
                    console.log('check this logic');
                }
            }
            // 2. REGISTER NEW SESSION
            session = { key, req, res };
            clients[key] = session;
            session.req.on('close', () => {
                console.log('close');
                delete clients[key];
            });
            req.socket.setTimeout(60 * 60 * 1000);
            // 3. SEND GREETING
            res.writeHead(200, {
                'Content-Type': 'text/event-stream',
                'Cache-Control': 'no-cache',
                'Connection': 'keep-alive'
            });
            res.write('\n');
            res.write(`data: ${JSON.stringify({greeting:'greeting'})}\n\n`);
            // 4. SEND REAL DATA
            const data = await service.get(session.key);
            if(data) {
                res.write(`data: ${JSON.stringify({message: data})}\n\n`);
            } else {
                console.log('no data');
            }
        } else {
            // logging invalid access must close
            console.log('invalid access => without auth key');
            req.socket.close();
        }
    } catch(e) {
        console.log(`exception => ${e.toString()}`);
        req.socket.close();
    }
});

app.listen(process.env.PORT || 8080);
