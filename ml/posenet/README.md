
WEBPACK

[WEBPACK/GETTING STARTED](https://webpack.js.org/guides/getting-started/)
[POSE DETECTION IN THE BROWSER: POSENET MODEL](https://github.com/tensorflow/tfjs-models/tree/master/posenet)

## LOADING A PRETRAINED POSENET MODEL

> [LOADING A PRETRAINED POSENET MODEL](https://github.com/tensorflow/tfjs-models/tree/master/posenet#loading-a-pre-trained-posenet-model)

In the first step of pose estimation, an image is fed through a pretrained model. PoseNet comes with a few different versions of the model, corresponding to variances of MobileNet v1 architecture and ResNet50 architecture. To get started, a model must be loaded from a checkpoint:

```js
const net = await posenet.load();
```

By default, `posenet.load()` loads a faster and smaller model that is based on MobileNetV1 architecture and has a lower accuracy. If you want to load the larger and more accurate model, specify the architecture explicitly in `posenet.load()` using a ModelConfig dictionary:

__MobileNet (smaller, faster, less accurate)__

```js
const net = await posenet.load({
  architecture: 'MobileNetV1',
  outputStride: 16,
  inputResolution: { width: 640, height: 480 },
  multiplier: 0.75
});
```

__ResNet (larger, slower, more accurate)__

```js
const net = await posenet.load({
  architecture: 'ResNet50',
  outputStride: 32,
  inputResolution: { width: 257, height: 200 },
  quantBytes: 2
});
```

__CONFIG PARAMS IN POSENET LOAD__

| PARAM           | DESCRIPTION |
| --------------- | ----------- |
| architecture    | Can be either MobileNetV1 or ResNet50. It determines which PoseNet architecture to load. |
| outputStride    | Can be one of 8, 16, 32 (Stride 16, 32 are supported for the ResNet architecture and stride 8, 16, 32 are supported for the MobileNetV1 architecture. However if you are using stride 32 you must set the multiplier to 1.0). It specifies the output stride of the PoseNet model. The smaller the value, the larger the output resolution, and more accurate the model at the cost of speed. Set this to a larger value to increase speed at the cost of accuracy. |
| inputResolution | A number or an object of type `{ width: number, height: number }`. Defaults to 257. It specifies the size the image is resized and padded to before it is fed into the PoseNet model. The larger the value, the more accurate the model at the cost of speed. Set this to a smaller value to increase speed at the cost of accuracy. If a number is provided, the image will be resized and padded to be a square with the same width and height. If width and height are provided, the image will be resized and padded to the specified width and height. |
| multiplier      | Can be one of 1.0, 0.75, or 0.50 (The value is used only by the MobileNetV1 architecture and not by the ResNet architecture). It is the fload multiplier for the depth (number of channels) for all convolution ops. The larger the value, the larger the size of the layers, and more accurate the model at the cost of speed. Set this to a smaller value to increase speed at the cost of accuracy. |
| quantBytes      | This argument controls the bytes used for weight quantization. The available options are: 4 (4 bytes per float (no quantization). Leads to highest accuracy and original model size (~90MB)), 2 (2 bytes per float. Leads to slightly lower accuracy and 2x model size reduction (~45MB)), 1 (1 byte per float. Leads to lower accuracy and 4x model size reduction (~22MB)). |
| modelUrl        | An optional string the specifies custom url of the model. This is useful for local development or contries that don't have access to the model hosted on GCP. |

By default, PoseNet loads a MobileNetV1 architecture with a 0.75 multiplier. This recommended for computers with midrange/lower-end GPUs. A model with a 0.50 multiplier is recommended for mobile. The ResNet architecture is recommended for computers with even more powerful GPUs.

