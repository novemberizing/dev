XGRAPHICS
=========

## DEVELOPMENT ENVIRONMENT

- UBUNTU 18.04
- GCC
- NODEJS
- ATOM
- GIT
- VALGRIND
- CMAKE

### INSTALL BUILD ENVIRONMENT

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

PATH 환경 변수에 /opt/nodejs/node-v12.16.1-linux-x64 추가

### C++ BUILD

```
mkdir build
cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ..
cmake --build .
```

## DOCUMENT

[XGRAPHICS](./xgraphics/README.md)<br />
[OPENGL](./opengl/README.md)<br />
[HOMEWORLD2](./homeworld2/README.md)<br />
[HISTORY](./history/README.md)<br />
