import dosbox from '@novemberizing/dosbox';

export default class Dos {
    constructor(canvas, uploader) {
        this._o = null;
        this._canvas = canvas;
        this._uploader = uploader;
    }

    async run() {
        this._o = await dosbox.run(this._canvas);
        this._o.FS.chdir('/dosbox');
        if(this._uploader) {
            this._uploader.addEventListener('change', event => {
                const file = event.target.files[0];
                let reader = new FileReader();
                reader.readAsArrayBuffer(file);
                reader.onload = () => {
                    const x = new Uint8Array(reader.result);
                    console.log(this._o.FS);
                    const stream = this._o.FS.open('/dosbox/' + file.name, "w+");
                    this._o.FS.write(stream, x, 0, x.length, 0);
                    this._o.FS.close(stream);
                    this._o.FS.syncfs(false, function(error){
                      console.log(error);
                    });
                    console.log(file.name);

                    var buffer = new TextEncoder().encode(file.name + '\0');

                    // var buf = Module._malloc(myTypedArray.length*myTypedArray.BYTES_PER_ELEMENT);
                    // Module.HEAPU8.set(myTypedArray, buf);
                    // Module.ccall('my_function', 'number', ['number'], [buf]);
                    // Module._free(buf);

                    console.log(buffer);


                    var name = this._o._malloc(buffer.length * buffer.BYTES_PER_ELEMENT);
                    this._o.HEAPU8.set(buffer, name);
                    console.log(name);
                    console.log(this._o._unzip(name));
                    this._o.FS.syncfs(false, function(err) {
                        console.log(err);
                    });
                    console.log('hello world');
                    // this._o._free(name);

                    // var name = this._o._malloc(file.name.length);
                    // this._o.HEAPU8.set(, name);
                    // this._o._free(name);
                    //     myTypedArray.length*myTypedArray.BYTES_PER_ELEMENT);
                    // Module.HEAPU8.set(myTypedArray, buf);
                    // Module.ccall('my_function', 'number', ['number'], [buf]);
                    // Module._free(buf);


                    // this._o.ccall('unzip', 'number', ['string'], [file.name])
                    //        .then(o => console.log(o))
                    //        .catch(e => console.log(e));
                    // set working directory

                };

                reader.onerror = () => {
                    console.log(reader.error);
                };
            }, true);
        }
        return this;
    }

    async upload() {



    }
}