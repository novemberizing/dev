X::CONTAINER
============

자료구조 구현 클래스의 기반이 되는 클래스입니다.

모든 자료구조 클래스에서 공통적으로 사용되는 메서드들 중에서 데이터 타입과 무관한 메서드들이 순수 가상 함수로 선언되어 있습니다.

## METHOD

| METHOD         | DESCRIPTION                       |
| -------------- | --------------------------------- |
| size(): uint64 | return a size of items            |
| empty(): bool  | return a container's empty status |
