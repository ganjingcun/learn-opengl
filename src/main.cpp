#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <OpenGL/OpenGL.h>

#include <GLUT/glut.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include<stdio.h>
#include<stdlib.h>
#include <math.h>

using namespace std;

void display(void) {
    //渲染背景色为白色
    glClearColor(1.0f,1.0f, 1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //设置当前绘图使用的颜色:黑色   -- 相当于画笔颜色
    glColor4f(0.0f,0.0f, 0.0f,0.0f);

//    glRectf(-0.5f, -0.5f, 0.5f, 0.5f);

    glBegin(GL_LINES);

    glVertex2f(0.2f,0.2f);
    glVertex2f(0.3f,0.3f);
    glEnd();

    const GLfloat Pi = 3.1415926536f;
    GLfloat a = 1 / (2-2*cos(72*Pi/180));
    GLfloat bx = a * cos(18 * Pi/180);
    GLfloat by = a * sin(18 * Pi/180);
    GLfloat cy = -a * cos(18 * Pi/180);
    GLfloat
            PointA[2] = { 0, a },
            PointB[2] = { bx, by },
            PointC[2] = { 0.5, cy },
            PointD[2] = { -0.5, cy },
            PointE[2] = { -bx, by };

    // 按照A->C->E->B->D->A的顺序，可以一笔将五角星画出

    glBegin(GL_LINE_LOOP);
    glVertex2fv(PointA);
    glVertex2fv(PointC);
    glVertex2fv(PointE);
    glVertex2fv(PointB);
    glVertex2fv(PointD);
    glEnd();

    const int n = 50;
    const GLfloat R = 0.5f;
    //GL_POLYGON改为GL_LINE_LOOP、GL_POINTS
    glBegin(GL_LINE_LOOP);
    glPointSize(10.0f);

    for(int i=0; i<n; ++i)
        glVertex2f(R*cos(2*Pi/n*i), R*sin(2*Pi/n*i));
    glEnd();


    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.5f, 0.5f);
    glEnd();

    glFlush();
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            exit(0);
    }
}


int main2(int argc, char **argv) {
    cout << "hellow" <<endl ;
    cout << "hellow" <<endl ;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("first openGL program");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}

/** 角度转弧度 */
double radian(int deg){
    auto pi = 4 * atan(1.0) ;
    return deg * pi / 180 ;
}


int main1(){
    auto pi = 4 * atan(1.0) ;
    cout << pi << endl ;
    cout << radian(180) <<endl;
}

int main(){
//    GLuint objectId = 0;
//    glGenObject(1, &objectId);
//    glBindObject(GL_WINDOW_TARGET, objectId);
//    glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_WIDTH, 800);
//    glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_HEIGHT, 600);
//    glBindObject(GL_WINDOW_TARGET, 0);
    cout << radian(180) <<endl;
}

