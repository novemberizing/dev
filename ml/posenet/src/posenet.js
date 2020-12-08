import * as tf from '@tensorflow/tfjs';
import * as posenet from '@tensorflow-models/posenet';

export default class PoseNet {
    static get MODEL() {
        return {
            MobileNetV1: {
                architecture: 'MobileNetV1',
                outputStride: 16,
                inputResolution: 256,
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
        this._poses = null;
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

        this._poses = [
            {
                pose,
                skeletons: posenet.getAdjacentKeyPoints(pose.keypoints, this._confidence)
            }
        ];

        // this.emit('pose', this._poses);

        tf.nextFrame().then(() => this.singlePose());

        return this._poses;
    }

    async multiPose() {
        const pose = await this._net.estimateSinglePose(this._video, this._params);

        this._poses = pose.map(pose => {
            return {
                pose,
                skeletons: posenet.getAdjacentKeyPoints(pose.keypoints, this._confidence)
            }
        });

        // this.emit('pose', this._poses);

        tf.nextFrame().then(() => this.multiPose());

        return this._poses;
    }

    emit(type, o) {
        // console.log(type, o);
    }

    skeleton(context) {
        if(this._poses) {
            this._poses.forEach(o => {
                o.skeletons.forEach(skeleton => {
                    context.strokeStyle = 'green';
                    context.beginPath();
                    context.moveTo(skeleton[0].position.x, skeleton[0].position.y);
                    context.lineTo(skeleton[1].position.x, skeleton[1].position.y);
                    context.stroke();
                });
            });
        }
    }

    keypoints(context) {
        if(this._poses) {
            this._poses.forEach(o => {
                o.pose.keypoints.forEach(keypoint => {
                    if(keypoint.score > 0.2) {
                        context.strokeStyle = 'green';
                        context.beginPath();
                        context.arc(keypoint.position.x, keypoint.position.y, 10, 0, 2 * Math.PI);
                        context.stroke();
                    }
                });
            });
        }
    }
}
