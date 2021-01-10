

export default class Camera {
    static async on(video, canvas = null) {
        if (navigator.mediaDevices && navigator.mediaDevices.getUserMedia) {
            let stream = await navigator.mediaDevices.getUserMedia({ video: true });
            video.srcObject = stream;
            video.play();
            if(canvas) {
                canvas.push(() => canvas.context.drawImage(video, 0, 0, 640, 480));
            }
            return stream;
        }
        return null;
    }

    static async off() {
        console.log('implement this');
    }

    constructor() {

    }
}