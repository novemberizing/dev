__NOVEMBERIZING PUB/SUB__
=========================

1. FIND PUB/SUB AS A SERVICE

- REAL TIME DATABASE

https://www.w3.org/TR/eventsource/

https://stackoverflow.com/questions/31238626/curl-structuring-request-to-validate-server-sent-events
https://stackoverflow.com/questions/11466595/listening-to-text-event-stream-using-c-sharp

https://developer.mozilla.org/en-US/docs/Web/API/Server-sent_events/Using_server-sent_events

https://blog.naver.com/PostView.nhn?blogId=wnrjsxo&logNo=221338322734

https://javascript.info/server-sent-events

'EventSource'

https://nodejs.org/en/docs/guides/nodejs-docker-webapp/


start a redis instance
$ docker run --name some-redis -d redis
start with persistent storage
$ docker run --name some-redis -d redis redis-server --appendonly yes
If persistence is enabled, data is stored in the VOLUME /data, which can be used with --volumes-from some-volume-container or -v /docker/host/dir:/data (see docs.docker volumes).

For more about Redis Persistence, see http://redis.io/topics/persistence.



```
sudo docker run -it --rm --name my-second-redis --link my-first-redis:redis -d redis
```

docker run --name some-redis -d redis


```
docker build -t novemberizing-pubsub .
```

docker run -it --rm --name pubsub --link some-redis:redis novemberizing-pubsub


docker run --name textory-redis -p 6379:6379 -d redis


```
docker run --name [name] -p 6379:6379 -d redis
```
