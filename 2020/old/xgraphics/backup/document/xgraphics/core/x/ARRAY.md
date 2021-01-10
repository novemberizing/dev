ARRAY&lt;T&gt;
==============

인덱스를 통해서 접근할 수 있는 배열 컨테이너입니다. 삽입과 삭제 시에 메모리 재할당을 최소화 시키지 의해서 페이징이란 개념을 두었습니다. 이 배열은 연속적으로 저장되어야 하는 자료를 위한 컨테이너입니다.

| MEMBER                                                           | DESCRIPTION                           |
| ---------------------------------------------------------------- | ------------------------------------- |
| [sub(offset: uint64, length: uint64): array](#method_sub)        | return sub array                      |
| data(): T[*]                                                     | return a memory space                 |
| resize(n: uint64)                                                | resize array                          |
| resize(n: uint64, item: T)                                       | resize array with a initial value     |
| push(source: T[*], n: uint64)                                    | push new items                        |
| push(item: T, n: uint64)                                         | push new items                        |
| push(item: T)                                                    | push a new item                       |
| push(o: array)                                                   | push new items                        |
| push(list: initializer)                                          | push new items                        |
| append(source: T[*], n: uint64)                                  | push new items                        |
| append(item: T, n: uint64)                                       | push new items                        |
| append(item: T)                                                  | push a new item                       |
| append(o: array)                                                 | push new items                        |
| append(list: initializer)                                        | push new items                        |
| assign(source: T[*], n: uint64)                                  | assign new items                      |
| assign(item: T, n: uint64)                                       | assign new items                      |
| assign(item: T)                                                  | assign a new item                     |
| assign(o: array)                                                 | assign new items                      |
| assign(list: initializer)                                        | assign new items                      |
| size(): uint64                                                   | retrieve the total of items           |
| empty(): bool                                                    | retrieve the container's empty status |
| clear()                                                          | clear container                       |
| clear(f: function)                                               | apply function and clear container    |
| each(f: function)                                                | apply function                        |
| operator[](n: uint64): T                                         | access item by index                  |
| operator+=(item: T): array                                       | append item                           |
| operator+=(o: array): array                                      | append new items                      |
| operator+=(list: initializer): array                             | append new items                      |
| operator=(item: T): array                                        | assign a new item                     |
| operator=(o: array): array                                       | assign new items                      |
| [operator=(o: initializer): array](#operator_assign_initializer) | assign new items                      |
| [constructor()](#default_constructor)                            | default constructor                   |
| [constructor(source: T[*], n: uint64)](#construct_source)        | construct with new items              |
| [constructor(item: T, n: uint64)](#construct_n_items)            | construct with new items              |
| [constructor(list: initializer)](#initializer_constructor)       | construct with new items              |
| [constructor(o: array)](#copy_constructor)                       | copy and move constructor             |
| [destructor()](#destructor)                                      | destructor                            |

![array](../../image/core/x/array.jpg)

## MEMBER

<a name="destructor"></a>
### DESTRUCTOR

객체가 소멸될 때 호출됩니다.

```c++
array<T>::~array()
```

<a name="default_constructor"></a>
### DEFAULT CONSTRUCTOR

```c++
array<T>::array()
```

아무것도 존재하지 않는 크기가 0인 배열을 만듭니다. 주의해야할 것은 메모리 공간이 미리 할당되어져 있는 크기가 0인 배열을 만든다는 것입니다. 프로텍트 멤버로 페이지 크기를 설정할 수 있거나 혹은 NULL 로 미리 할당된 용량의 크기와 페이지 사이즈를 설정할 수 있는 메서드를 정의하여 상속하여 사용하면 미리 할당되지 않은 메모리 공간을 사용할 수 있도록 하였습니다.

#### EXAMPLE

```c++
#include <x/array.hh>

int main()
{
    x::array<int> o;
    return 0;
}
```

<a name="copy_constructor"></a>
### COPY CONSTRUCTOR

같은 배열 객체를 카피하는 생성자입니다.

```c++
array<T>::array(const x::array<T> & o)
```

#### EXAMPLE

```c++
#include <x/array.hh>

int main()
{
    x::array<int> source = { 1, 2, 3, 4, 5 };
    x::array<int> o = source;
    x::array<int> second(source);
    return 0;
}
```

### MOVE CONSTRUCTOR

다른 배열 객체의 멤버 변수들을 이동시켜서 새로운 배열 객체를 생성합니다. 이 메서드들을 사용하면 메모리 할당을 하지 않고 새로운 객체로 이동시켜서 객체를 생성시킬 수 있습니다.

```c++
array<T>::array(x::array<T> && o) noexcept
```

#### EXAMPLE

```c++
#include <x/array.hh>

int main()
{
    x::array<int> source = { 1, 2, 3, 4, 5 };
    x::array<int> o = x::move(source);
    source = { 1, 2, 3, 4, 5 };
    x::array<int> second(x::move(source));
    return 0;
}
```

<a name="initializer_constructor"></a>
### INITIALIZER CONSTRUCTOR

배열을 생성하기 위해서 이니셜라이져 리스트를 사용할 수 있습니다.

```c++
array<T>::array(const x::initializer<T> & list)
```

#### EXAMPLE

```c++
#include <x/array.hh>

int main()
{
    x::array<int> o = { 1, 2, 3, 4, 5 };
    return 0;
}
```

<a name="construct_n_items"></a>
### CONSTRUCTOR (N ITEMS)

N개의 아이템을 삽입한 배열 객체를 생성합니다.

```c++
array<T>::array(const T & item, x::uint64 n)
```

#### EXAMPLE

```c++
#include <x/array.hh>

#include <iostream>

int main(int argc, char ** argv)
{
    x::array<int> o(1, 15);
    o.each([](const int & v){
        std::cout << v << std::endl;
    });
    return 0;
}

```

<a name="construct_source"></a>
### CONSTRUCTOR (FROM SOURCE)

연속적인 어떤 메모리 공간에 있는 데이터로 부터 배열 객체를 생성합니다.

```c++
array<T>::array(const T * source, x::uint64 n)
```

### EXAMPLE

```c++
#include <x/array.hh>
#include <iostream>

int main()
{
    int source[5] = { 0, 1, 2, 3, 4 };
    x::array<int> o(source, 3);
    o.each([](const int & v){
        std::cout << v << std::endl;
    });
    return 0;
}
```

<a name="method_sub"></a>
### METHOD RETRIEVE SUB ARRAY

오프셋에서 부터 특정 길이의 배열을 추출합니다.

```c++
array<T>::sub(x::uint64 offset, x::uint64 length)
```

### EXAMPLE

```c++
#include <x/array.hh>
#include <iostream>

int main()
{
    x::array<int> o;
    for(x::uint64 i = 0; i < 128; i++)
    {
        o.push(i);
    }
    x::array<int> destination = o.sub(16, 8);
    destination.each([](const int & v){
        std::cout << v << std::endl;
    });
}
```

<a name="operator_assign_initializer"></a>
### OPERATOR ASSIGN FROM INITIALIZER LIST

```c++
array<T>::operator=(const x::initializer<T> & list)
```

이니셜라이져 리스트를 사용하여 이미 생성된 객체를 초기화 하는 함수입니다.

#### EXAMPLE

```c++
#include <x/array.hh>
#include <iostream>

int main()
{
    x::array<int> o;
    for(x::uint64 i = 0; i < 128; i++)
    {
        o.push(i);
    }
    x::array<int> destination = { 1, 2, 3, 4, 5 };
    destination.each([](const int & v){
        std::cout << v << std::endl;
    });
}
```


## SEE

[CONTAINER](./CONTAINER.md),
[COLLECTION](./COLLECTION.md),
STRING,
BYTES
