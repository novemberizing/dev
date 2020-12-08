import Camera from './camera';
import Canvas from './canvas';
import Posenet from './posenet';

const canvas = new Canvas(document.getElementById('canvas'));
const posenet = new Posenet(document.getElementById('video'), 'single', Posenet.MODEL.MobileNetV1, Posenet.PARAMS.MobileNetV1, 0.5);

async function on() {
    await Camera.on(document.getElementById('video'), canvas);
    canvas.push(()=> posenet.skeleton(canvas.context));
    canvas.push(()=> posenet.keypoints(canvas.context));
    await posenet.load();
    canvas.on();

    return true;
}

on();



