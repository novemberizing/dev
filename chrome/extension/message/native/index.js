const struct = require('python-struct');
const fs = require('fs');

const stream = fs.createWriteStream('./output');

let buffer = null;

process.stdin.on('data', function(data) {
    buffer = buffer ? Buffer.concat([buffer, data]) : data;

    if(buffer.length < 4) {
        stream.write('data.length < 4\n');
        return;
    }

    try {
        stream.write(`${buffer.length}\n`);
        stream.write(`${buffer.readInt32LE(0)}\n`);
        while(buffer.length > 4 && buffer.readInt32LE(0) + 4 <= buffer.length) {
            const msg = buffer.slice(4, 4 + buffer.readInt32LE(0));
            stream.write(msg.toString());
            stream.write(`${buffer.length}\n`);
            buffer = buffer.slice(buffer.readInt32LE(0) + 4);
            stream.write(`${buffer.length}\n`);
        }
    } catch(e) {
        stream.write(`${e.toString()}\n`);
    }
    
});
