const express = require('express');
const redis = require('redis');

const retry = {
    retry_strategy: function(options) {
        const millisecond = options.attempt * 1000;
        return Math.min(millisecond > 0 ? millisecond : 10000, 10000);
    }
};

function __create(host, port) {
    const client =  redis.createClient(retry);
    client.on('error', console.log);
    client.on('ready', (o) => {});
    client.on('connect', (o) => {});
    client.on('reconnecting', console.log);
    client.on('end', (o) => {});
    client.on('warning', (o) => {});
    return client;
}

class Pubsub {
    constructor(host, port) {
        this.clients = new Map();
        this.client = __create(host, port);
        this.client.on('connect', (o) => {
            console.log('connect');
            this.clients.forEach((v, k) => {

            });
        });
        this.subscriber = __create(host, port);
        this.subscriber.on('psubscribe', (channel, count) => {
            console.log(channel);
        });
        this.subscriber.on('pmessage', (pattern, channel, message) => this.pub(pattern, channel, message));
        console.log(this.subscriber.psubscribe);
        this.subscriber.psubscribe('message:*');
    }

    /**
     * 키를 체크합니다.
     */
    async auth(auth) {
        return new Promise((resolve, reject) => {
            // TODO: 커스터마이즈 하세요.
            resolve(auth);
        });
    }

    /**
     * EventSource 에 의해서 접속한 세션으로 데이터를 전송합니다.
     */
    pub(pattern, channel, message) {
        const strings = channel.split(':');
        console.log(channel);
        console.log(message);
        if(strings.length >= 2 && strings[0] === 'message' && strings[1]) {
            const key = strings[1];
            const session = this.clients.get(key);
            if(session) {
                session.res.write(`data: {"message":${message}}\n\n`);
            }
        }
    }

    /**
     * EventSource 에 의해 최초 접속했을 때 모든 데이터를 전송합니다.
     */
    async get(key) {
        return new Promise((resolve, reject) => {
            this.client.hgetall(key, (e, v) => {
                if(e) {
                    reject(e);
                    return;
                }
                resolve(v);
            });
        });
    }

    /**
     * 저장소에서 데이터를 삭제합니다.
     */
    async del(key, field) {
        return new Promise((resolve, reject) => {
            this.client.hdel(key, field, (e, v) => {
                if(e) {
                    reject(e);
                    return;
                }
                resolve(v);
            });
        });
    }

    /**
     * 저장소에서 데이터를 삽입하고 삽입되었음을 통지합니다.
     */
    async put(key, field, value) {
        return new Promise((resolve, reject) => {
            this.client.hset(key, field, value, (e, v) => {
                if(e) {
                    reject(e);
                    return;
                }
                let data = {};
                data[field] = value;
                console.log('message:' + key);
                console.log(data);
                console.log('==================');
                this.client.publish('message:' + key, JSON.stringify(data), (e, v) => {
                    if(e) {
                        reject(e);
                        return;
                    }
                    resolve(v);
                });
            });
        });
    }

    reg(key, o) {
        const remove = this.clients.get(key);
        this.clients.set(key, o);
        console.log(`client connected: ${key}`);
        if(remove) {
            console.log(`client ${key}'s old connection is exist`);
        }
        return remove;
    }
}

const app = express();
const pubsub = new Pubsub('127.0.0.1', 6379);

// REMOVE THIS : RELEASE : START
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
                            // document.body.innerHTML += JSON.stringify({key: data.message[k]}) + "<br>";
                            const result = await axios.get('/del/?auth='+auth+'&data='+JSON.stringify({key:k}));
                            // document.body.innerHTML += JSON.stringify(result.data) + "<br>";
                        } catch(e) {
                            console.log(e.toString());
                        }

                    });
                }
            }
        </script>
    </body>
</html>`;

app.get('/', (req, res) => {
    res.send(template);
});
// REMOVE THIS : RELEASE : END

app.get('/del/', async (req, res) => {
    try {
        const key = await pubsub.auth(req.query.auth);
        const data = JSON.parse(req.query.data);
        if(key) {
            const result = await pubsub.del(key, data);
            res.send(JSON.stringify(result));
        } else {
            // logging invalid access must close
            console.log('invalid access => without auth key');
            res.end();
        }
    } catch(e) {
        console.log(`exception => ${e.toString()}`);
        res.end();
    }
});

app.get('/put/', async (req, res) => {
    try {
        const key = await pubsub.auth(req.query.auth);
        const data = JSON.parse(req.query.data);
        if(key) {
            console.log(data);
            const result = await pubsub.put(key, data.key, data.value);
            res.send(JSON.stringify(result));
        } else {
            // logging invalid access must close
            console.log('invalid access => without auth key');
            res.end();
        }
    } catch(e) {
        console.log(`exception => ${e.toString()}`);
        res.end();
    }
});

app.get('/events/', async (req, res) => {
    let result = null;
    try {
        const key = await pubsub.auth(req.query.auth);
        if(key) {
            const removal = pubsub.reg(key, {key, req, res});
            if(removal) {
                removal.req.on('close', ()=>{});
                removal.res.end();
            }
            req.socket.setTimeout(60 * 60 * 1000);
            res.writeHead(200, {
                'Content-Type': 'text/event-stream',
                'Cache-Control': 'no-cache',
                'Connection': 'keep-alive'
            });
            res.write('\n');
            const data = pubsub.get(key);
            if(data) {
                res.write(`data: ${JSON.stringify({message: data})}`);
            }
            return;
        } else {
            result = 'invalid access';
            console.log('invalid access auth is invalid');
        }
    } catch(e) {
        result = e.toString();
        console.log(`exception => ${result}`);
    }

    // 이곳에서 에러가 일어나면 답이 없다.
    try {
        res.writeHead(200, {
            'Content-Type': 'text/event-stream',
            'Cache-Control': 'no-cache',
            'Connection': 'keep-alive'
        });
        res.write('\n');
        res.write(`data: ${result}\n\n`);
        res.end();
    } catch(e) {
        console.log(`critical error: ${e.toString()}`);
    }
});

app.listen(process.env.PORT || 8080);
