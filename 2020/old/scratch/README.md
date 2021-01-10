__SCRATCH__
===========

RUN 을 수행할 때 시간이 오래 걸린다.
GIT CLONE 을 통해서 클론하고 카피한 후에 데이터를 로딩하도록 하자.

## SOURCE DOWNLOAD

```
git clone https://github.com/LLK/scratch-gui.git
```

## BUILD IMAGE

```
docker build -t novemberizing/scratch .
```

## RUN IMAGE

```
docker run -it --name scratch -p 8601:8601 --rm scratch
```


- [NODEJS 웹 앱의 도커라이징](https://nodejs.org/ko/docs/guides/nodejs-docker-webapp/)
- [SCRATCH GUI](https://github.com/LLK/scratch-gui)
- [Docker CMD 지시문의 여러 명령](https://qastack.kr/server/685697/multiple-commands-in-docker-cmd-directive)
- [Node.js 웹 앱의 도커라이징](https://nodejs.org/ko/docs/guides/nodejs-docker-webapp/)
