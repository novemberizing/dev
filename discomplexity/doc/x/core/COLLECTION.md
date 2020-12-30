X::COLLECTION&lt;T&gt;
======================

자료구조의 기반이 되는 클래스로 [X::CONTAINER](./CONTAINER.md)와 달리 저장된 아이템의 타입과 관계된 행동들을 추상화한 클래스입니다.

컨테이너에 저장된 아이템의 타입과 관련된 공통적인 메서드들이 저장되어 있습니다.

# METHOD

| METHOD                             | DESCRIPTION                    |
| ---------------------------------- | ------------------------------ |
| add(item: T)                       | add a item                     |
| clear()                            | clear all items                |
| clear(f: function&lt;void (T)&gt;) | clear all items and apply them |
| each(f: function&lt;void (T)&gt;)  | apply function all items       |
