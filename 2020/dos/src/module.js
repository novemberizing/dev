
let canvas = document.createElement('canvas');

canvas.id = 'canvas';
canvas.tabIndex = -1;
canvas.addEventListener(oncontextmenu, function(e) {
    e.preventDefault();
});
canvas.width=640;
canvas.height=400;
canvas.addEventListener("webglcontextlost", function(e) {
    alert('WebGL context lost. You will need to reload the page.');
    e.preventDefault();
}, false);

module.exports = {

};
