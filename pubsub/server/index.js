const express = require('express');

const app = express();

class Pubsub {
    construct() {

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

    }

    async del(key, keys) {

    }

    async put(key, data) {

    }
};

const service = new Pubsub();

const template = `<!DOCTYPE html>
<html>
    <head>
    </head>
    <body>
        <script type="text/javascript">
            const source = new EventSource("/events/?auth=" + 93, {
                withCredentials: false
            });
            console.log(source);
            source.onmessage = function(e) {
                document.body.innerHTML += e.data + "<br>";
            }
        </script>
    </body>
</html>`;

let clients = {};

app.get('/', (req, res) => {
    res.send(template);
});

app.get('/del/', async (req, res) => {
    try {
        const key = await service.auth(req.query.auth);
        const data = JSON.stringify(req.query.data);
        if(key) {
            const result = await service.del(key, data);
            res.send(result);
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
        const key = await service.auth(req.query.auth);
        const data = JSON.stringify(req.query.data);
        if(key) {
            const result = await service.put(key, data);
            res.send(result);
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
            res.write(`data: ${JSON.stringify({message:'greeting'})}\n\n`);
            // 4. SEND REAL DATA
            const data = await service.get(session.auth);
            res.write(`data: ${JSON.stringify(data)}`);
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
