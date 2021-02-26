[assertion:console.c:295] xconsoledescriptorprocessor_output:78067520 =>
[assertion:console.c:297] xconsoledescriptorprocessor_output:78067520 =>

위의 로그는 CONSOLE OUTPUT 의 오픈 상태를 잘못 판단하였기 때문이다.
콘솔 OUTPUT 의 상태는 IN 역시 항상 오픈되어 있는 것으로 판단하자.

==156065== 
dsfsdagf
[epoll] in
==156065== Invalid read of size 4
==156065==    at 0x10E129: xstreamadjust (stream.c:313)
==156065==    by 0x10C580: xconsoledescriptorprocessor_in (console.c:207)
==156065==    by 0x10C710: xconsoledescriptorprocessor_input (console.c:245)
==156065==    by 0x10F437: xdescriptorevent_processor_in (descriptor.c:77)
==156065==    by 0x10FA1D: xdescriptorevent_dispatch_in (descriptor.c:240)
==156065==    by 0x10B479: xdescriptoreventgenerator_once (epoll.c:324)
==156065==    by 0x109AC3: xeventengine_generators_once (engine.c:108)
==156065==    by 0x1096CB: xeventengine_run (engine.c:47)
==156065==    by 0x10954A: main (console.c:17)
==156065==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==156065== 
==156065== 
==156065== Process terminating with default action of signal 11 (SIGSEGV)
==156065==  Access not within mapped region at address 0x0
==156065==    at 0x10E129: xstreamadjust (stream.c:313)
==156065==    by 0x10C580: xconsoledescriptorprocessor_in (console.c:207)
==156065==    by 0x10C710: xconsoledescriptorprocessor_input (console.c:245)
==156065==    by 0x10F437: xdescriptorevent_processor_in (descriptor.c:77)
==156065==    by 0x10FA1D: xdescriptorevent_dispatch_in (descriptor.c:240)
==156065==    by 0x10B479: xdescriptoreventgenerator_once (epoll.c:324)
==156065==    by 0x109AC3: xeventengine_generators_once (engine.c:108)
==156065==    by 0x1096CB: xeventengine_run (engine.c:47)
==156065==    by 0x10954A: main (console.c:17)
==156065==  If you believe this happened as a result of a stack
==156065==  overflow in your program's main thread (unlikely but
==156065==  possible), you can try to increase the size of the
==156065==  main thread stack using the --main-stacksize= flag.





[assertion:console.c:259] xconsoledescriptorsubscriber_input:78067520 => 



==152369== Invalid write of size 8
==152369==    at 0x10C23C: xconsoledescriptorin_get (console.c:98)
==152369==    by 0x10C148: xconsolesubscriber_set (console.c:66)
==152369==    by 0x109507: main (console.c:10)
==152369==  Address 0x80 is not stack'd, malloc'd or (recently) free'd
==152369== 
==152369== 
==152369== Process terminating with default action of signal 11 (SIGSEGV)
==152369==  Access not within mapped region at address 0x80
==152369==    at 0x10C23C: xconsoledescriptorin_get (console.c:98)
==152369==    by 0x10C148: xconsolesubscriber_set (console.c:66)
==152369==    by 0x109507: main (console.c:10)
==152369==  If you believe this happened as a result of a stack
==152369==  overflow in your program's main thread (unlikely but
==152369==  possible), you can try to increase the size of the
==152369==  main thread stack using the --main-stacksize= flag.
==152369==  The main thread stack size used in this run was 8388608.






==148181== Jump to the invalid address stated on the next line
==148181==    at 0x0: ???
==148181==    by 0x10B29D: xdescriptoreventgenerator_register (epoll.c:259)
==148181==    by 0x109E96: xeventengine_descriptor_register (engine.c:196)
==148181==    by 0x10951B: main (console.c:12)
==148181==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==148181== 
==148181== 
==148181== Process terminating with default action of signal 11 (SIGSEGV)
==148181==  Bad permissions for mapped region at address 0x0
==148181==    at 0x0: ???
==148181==    by 0x10B29D: xdescriptoreventgenerator_register (epoll.c:259)
==148181==    by 0x109E96: xeventengine_descriptor_register (engine.c:196)
==148181==    by 0x10951B: main (console.c:12)





==147774== Invalid write of size 4
==147774==    at 0x10C22E: xconsoledescriptorout_get (console.c:111)
==147774==    by 0x109509: main (console.c:12)
==147774==  Address 0x1c is not stack'd, malloc'd or (recently) free'd
==147774== 
==147774== 
==147774== Process terminating with default action of signal 11 (SIGSEGV)
==147774==  Access not within mapped region at address 0x1C
==147774==    at 0x10C22E: xconsoledescriptorout_get (console.c:111)
==147774==    by 0x109509: main (console.c:12)
==147774==  If you believe this happened as a result of a stack
==147774==  overflow in your program's main thread (unlikely but
==147774==  possible), you can try to increase the size of the
==147774==  main thread stack using the --main-stacksize= flag.
==147774==  The main thread stack size used in this run was 8388608.



고민스러운 부분은 CONSOLE 에 등록하느냐? 아니면 SUBSCRIPTION 에 등록하는냐 이다.
결국은 SUBSCRIPTION 에 등록하는 것이 아니라 콘솔에 등록하는 것이겠구나

등록할 때 서브스크립션을 생성 한 후에 generatornode 에 generator 를 삽입하도록 하였다.

[assertion:descriptor/event/generator/subscription/list.c:41] xdescriptoreventgeneratorsubscriptionlist_push:78067520 =>


생성과 동시에 생성하지 않았다. 그래서 생성과 동시에 필요한 자원을 생성하도록 해야 한다.

==135190== Invalid read of size 8
==135190==    at 0x10B179: xdescriptoreventgenerator_register (epoll.c:263)
==135190==    by 0x109E4F: xeventengine_descriptor_register (engine.c:194)
==135190==    by 0x1094FB: main (console.c:8)
==135190==  Address 0x8 is not stack'd, malloc'd or (recently) free'd
==135190== 
==135190== 
==135190== Process terminating with default action of signal 11 (SIGSEGV)
==135190==  Access not within mapped region at address 0x8
==135190==    at 0x10B179: xdescriptoreventgenerator_register (epoll.c:263)
==135190==    by 0x109E4F: xeventengine_descriptor_register (engine.c:194)
==135190==    by 0x1094FB: main (console.c:8)
==135190==  If you believe this happened as a result of a stack
==135190==  overflow in your program's main thread (unlikely but
==135190==  possible), you can try to increase the size of the
==135190==  main thread stack using the --main-stacksize= flag.
==135190==  The main thread stack size used in this run was 8388608.
 
 
 디스크립터 이벤트 제네레이터가 널이다.

```
==134690== Invalid read of size 8
==134690==    at 0x10B104: xdescriptoreventgenerator_register (epoll.c:263)
==134690==    by 0x109DC2: xeventengine_descriptor_register (engine.c:193)
==134690==    by 0x1094FB: main (console.c:8)
==134690==  Address 0x8 is not stack'd, malloc'd or (recently) free'd
```

nobase_include_HEADERS

가 설치 시에 사용되어지는 것인가 아니면 ...

이것은 프로그램을 다 만든 후에 정리한번 하자.

이벤트 마스크 역시 정리한번 하자.


```
generating build information using aclocal, autoheader, automake and autoconf
src/x/Makefile.am:6: warning: source file 'thread/posix.c' is in a subdirectory,
src/x/Makefile.am:6: but option 'subdir-objects' is disabled
automake: warning: possible forward-incompatibility.
automake: At least a source file is in a subdirectory, but the 'subdir-objects'
automake: automake option hasn't been enabled.  For now, the corresponding output
automake: object file(s) will be placed in the top-level directory.  However,
automake: this behaviour will change in future Automake versions: they will
automake: unconditionally cause object files to be placed in the same subdirectory
automake: of the corresponding sources.
automake: You are advised to start using 'subdir-objects' option throughout your
automake: project, to avoid future incompatibilities.
````

__20210219__
============

1. void * 를 다른 이름으로 변경할 필요가 있어 보인다.

    xhandle, xreference, 

2. 이벤트 프로세서 풀에 락을 없애자.
   모든 수행은 메인 스레드에서 수행되도록 하자.

   이벤트 

-----

20210218



완료

1. EVENT OBJECT > DESCRIPTOR > SOCKET > CLIENT SOCKET, SERVER SOCKET, SESSION SOCKT 을 도식화하고 중요한 함수들을 구현하자.

xdescriptorsub 를 xdescriptorsubscription 으로 변경하자. - 고민스러움





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

2. DESCRIPTOR EXCEPTION ERROR CODE 구조체를 정의하고, EXCEPTION 발생 시에 함수를 처리할 수 있도록 한다.


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

