20210217

1. 현재까지의 구현을 설계한다.

dispatch(descriptor: descriptor, event: uint32, data: reference, size: int64): int64

파라미터에 대한 고민과 컨셉을 잡는 것이 필요하다.

data: const void * : 이벤트를 배치할 때, read 의 경우 const 이면 동작하지 않는다. 그렇기 때문에
const 를 없애야 한다. 또한 WRITE 의 경우 const 이어야 한다. 두가지를 모두 담을 수 있는 그릇이 필요하다. 만약에 데이터가 stream 이라면 어떨까?
event 에 따른 data 타입의 정의가 필요하다,

| TYPE      | CLASS                     |
| --------- | ------------------------- |
| void      | xnil                      |
| open      | `<<callback>> function`   |
| in        | `<<reference>> stream`    |
| out       | `<<reference>> stream`    |
| exception | `<<reference>> errorcode` |
| close     | `<<callback>> function`   |

size: int64: buffer 의 경우 의미가 있지만, 그렇지 않은 경우 의미가 없다.


----


20210216

1. XDESCRIPTOREVENT DISPATCH
2. XDESCRIPTOREVENT PROCESS
3. XDESCRIPTOREVENT FINISH

관련한 이벤트 처리에 대한 컨셉을 잡고 만들자.

어떻게 하면 이벤트 생성 시에 동적할당으로 이벤트 객체를 생성하지 않을까?
하나의 이벤트 객체가 여러개의 이벤트 생성 객체에 등록되려면,...
빠져버린 늪은 O(1) 을 보장하기 위해서 객체의 크기가 커진다.
타임이벤트 타겟이면서 디스크립터 이벤트 타겟 그리고 시그널 이벤트 타겟이려면,...

`xdescriptorevent_dispatch(descriptor, xdescriptor_event_exception, xnil, 0);` 함수 수행 시에 예외 코드를 같이 전송할 수 있도록 하자.

1. xeventengine_event_push 구현 필요
2. 좋은 이름이 없나? 디스크립터에 WRITE 해야할 데이터의 존재 여부 으로 정하였다. xdescriptorexist_out

----

