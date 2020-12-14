"use strict"

const builder = require("electron-builder")
const Platform = builder.Platform

// Promise is returned
builder.build({

})
.then((o) => {
    console.log(o);
})
.catch((e) => {
    console.log(e);
});