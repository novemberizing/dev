XGRAPHICS
=========

이 프로젝트의 목표는 컴퓨터 그래픽스 관련한 개발을 쉽게 할 수 있도록 돕는 것입니다. 부가적으로 이 프로젝트는 처음으로 게임엔진을 만들어 보려는 사람들에게 지도와 같이 길을 잃지 않는 지도와 나침판과 같은 역할을 할 수 있기를 바랍니다. 저는 이 프로젝트를 첫번째로 저만의 홈월드2 게임을 만들어 보는 것이 목적입니다. 완전히 다른 게임이겠지만, 홈월드2를 통해서 얻은 새로운 게임에 대한 영감을 얻었고 이를 통해서 새로운 자만의 게임을 만들려는 것입니다. 물론 이 프로젝트는 새로운 게임에 대한 영감을 가진 사람들에게 그것을 실현할 수 있는 어떤 지도와 나침판 같은 역할을 할 수 있는 프로젝트가 되길 희망합니다. 새로운 영감을 얻었을 때 어떻게 해야하는지 모르는 저와 저와 유사한 방향을 찾지 못하는 사람들에게 조금이나마 힘이 되는 프로젝트와 소프트웨어 그리고 라이브러리가 되도록 조금씩 조금씩 앞으로 나아가 볼 것 입니다.

## HISTORY

[THE BEGINNING](./document/history/20200313.md)<br />
[DATA STRUCTURE](./document/history/20200314.md)<br />
[EVENT LOOP & CUSTOM CONSOLE I/O](./document/history/20200315.md)<br />
[MATRIX, VECTOR, GRAPHICS BASIS](./document/history/20200316.md)<br />
[SIMPLE PRIMITIVE, HOMEWORLD2 OBJECT DESERIALIZE, WEBGL, LOADING](./document/history/20200317.md)<br />
[WEBGL REFACTORING, HOMEWORLD2 MATERIAL & TEXTURE ANALYSIS](./document/history/20200318.md)<br />
[TEXTURE MAPPING ING](./document/history/20200319.md)<br />
[TEXTURE MAPPING](./document/history/20200320.md)<br />
[CLASS IMPLEMENT FOR PHYSICS CONCEPT](./document/history/20200321.md)<br />
[LAYER AND BACKGROUND](./document/history/20200323.md)<br />
[IMAGE PRIMITIVE](./document/history/20200324.md)<br />
[OBJECT CONTROL](./document/history/20200325.md)<br />
[OBJECT CONCEPT](./document/history/20200327.md)<br />
[REFACTORING](./document/history/20200328.md)<br />

## DEVELOPMENT ENVIRONMENT

```
sudo apt update
sudo apt upgrade
sudo apt install git
sudo apt install build-essential
wget https://nodejs.org/dist/v12.16.1/node-v12.16.1-linux-x64.tar.xz
tar xvf node-v12.16.1-linux-x64.tar.xz
sudo mkdir /opt/nodejs
sudo mv node-v12.16.1-linux-x64 /opt/nodejs/
sudo chown sean:sean /opt/nodejs -R
sudo apt install vim
sudo apt install valgrind
sudo apt install cmake
sudo apt install freeglut3-dev
sudo apt install libglew-dev
```

## JAVASCRIPT DEVELOPMENT DEPENDENCIES

@babel/core
@babel/cli
@babel/preset-env
babel-loader
webpack
webpack-cli
webpack-dev-server

## BUILD

```
cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ..
cmake --build .
```

## DOCUMENT

[XGRAPHICS](./document/xgraphics/README.md)<br />
[HOMEWORLD2](./document/homeworld2/README.md)<br />
[OPENGL](./document/opengl/README.md)<br />
[HISTORY](./document/history/README.md)<br />

## ETC

[TWITTER](https://twitter.com/discomplexity)
