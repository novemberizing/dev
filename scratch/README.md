__SCRATCH__
===========

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
docker run -it --name scratch -p 8601:8601 -v ${PWD}:/usr/src/app --rm scratch
```


- [NODEJS 웹 앱의 도커라이징](https://nodejs.org/ko/docs/guides/nodejs-docker-webapp/)
- [SCRATCH GUI](https://github.com/LLK/scratch-gui)
