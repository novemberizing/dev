/**
 * @note    리눅스 환경에서 이미 FREEGLUT 와 GLEW 가 설치되어 있다면 아래 처럼 컴파일을 하시면 동작을 확인할 수 있습니다.
 *
 *          g++ -o glClearColor glClearColor.cc -lglut -lGLEW -lGL -lGLU
 */
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
