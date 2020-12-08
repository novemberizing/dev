import * as tf from '@tensorflow/tfjs';
import * as posenet from '@tensorflow-models/posenet';

export default class PoseNet {
    static get MODEL() {
        return {
            MobileNetV1: {
                architecture: 'MobileNetV1',
                outputStride: 16,
                inputResolution: { width: 640, height: 480 },
                multiplier: 0.75
            },
            ResNet50: {
                architecture: 'ResNet50',
                outputStride: 32,
                inputResolution: { width: 257, height: 200 },
                quantBytes: 2
            }
        }
    }

    static get PARAMS() {
        return {
            MobileNetV1: {
                flipHorizontal: false
            },
            ResNet50: {
                flipHorizontal: false,
                maxDetections: 5,
                scoreThreshold: 0.5,
                nmsRadius: 20
            }
        }
    }

    constructor(video, detection, model, params, confidence = 0.5) {
        this._video = video;
        this._model = model;
        this._params = params;
        this._detection = detection;
        this._confidence = confidence;
        this._net = null;
    }

    async load() {
        this._net = await posenet.load(this._model);

        if(this._video) {
            if(this._video.readyState === 0) {
                await new Promise((resolve) => { this._video.onloadeddata = () => resolve(); });
            }
            if(this._detection === 'single') {
                await this.singlePose();
            } else if(this._video === 'multi') {
                await this.multiPose();
            }
        }

        return this;
    }

    async singlePose() {
        const pose = await this._net.estimateSinglePose(this._video, this._params);

        result = [
            {
                pose,
                skeleton: posenet.getAdjacentKeyPoints(pose.keypoints, this._confidence)
            }
        ];

        this.emit('pose', result);

        tf.nextFrame().then(() => this.singlePose());

        return result;
    }

    async multiPose() {
        const pose = await this._net.estimateSinglePose(this._video, this._params);

        result = pose.map(pose => {
            return {
                pose,
                skeleton: posenet.getAdjacentKeyPoints(pose.keypoints, this._confidence)
            }
        });

        this.emit('pose', result);

        tf.nextFrame().then(() => this.multiPose());

        return result;
    }

    emit(type, o) {
        console.log(type, o);
    }
}
