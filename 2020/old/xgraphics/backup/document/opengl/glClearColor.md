glClearColor
============

칼라 버퍼를 지우는데 사용할 색상 값을 지정합니다.

```c
void glClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
```

[glClearColor](./glClearColor.md) 는 [glClear](./glClear.md) 가 색상 버퍼를 지우는 데 사용하는 빨강, 녹색, 파랑 및 알파 값을 지정합니다. [glClearColor](./glClearColor.md) 로 지정된 값은 0 에서 1 사이의 값입니다.

## 파라미터

red, green, blue, alpha

컬러 버퍼를 지울 때 사용할 빨강, 녹색, 파랑 및 알파 값입니다. 초기 값은 모두 0 입니다.

## ASSOCIATED GETS

| PARAMETER VALUE      | - |
| -------------------- | - |
| GL_COLOR_CLEAR_VALUE | - |

## 예제

리눅스 환경에서 이미 FREEGLUT 와 GLEW 가 설치되어 있다면 아래 처럼 컴파일을 하시면 동작을 확인할 수 있습니다.

```
g++ -o glClearColor glClearColor.cc -lglut -lGLEW -lGL -lGLU
```

[glClearColor](./glClearColor.md) 함수의 파라미터는 현재 파란색으로 칼라 버퍼를 초기화하도록 하였습니다.
직접 파라미터를 조정하고 창의 크기를 줄이고 늘이면서 테스트해볼 수 있습니다.

```c
#include <GL/glew.h>
#include <GL/freeglut.h>

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitContextVersion(3, 3);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("glClearColor");

    glewInit();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glutDisplayFunc([](){
        // 칼라 버퍼를 지우는데 사용할 색상 값을 지정합니다.
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glutSwapBuffers();
    });

    glutMainLoop();

    return 0;
}
```

## 오리지널 레퍼런스 링크

[glClearColor](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glClearColor.xhtml)
