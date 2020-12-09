#include <iostream>     //РГЗ 29 вариант Задание:
#include <glut.h>       //Движение под углом 45 градусов с отражением от границ экрана. 
#include <time.h>       //Размер объекта изменяется  при отражении от верхней и правой границы на +50%, от нижней  и левой границы на -50%.    
                        //Управление стрелочками
using namespace std;

GLfloat x_1 = 0.0;   // GLfloat потому что функции ругаются
GLfloat y_1 = 0.0;
GLfloat rsize = 25;

GLfloat xstep = 1.0;
GLfloat ystep = 1.0;

GLfloat windowWidth;
GLfloat windowHeight;

float koef_1 = 1.0;   //это для изменения размеров квадрата
float koef_2 = 1.0;   //на самом деле без этого прикольнее 
bool suka = 0;        //а это для таймера

void YOBA(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);  
    glRectf(x_1, y_1, x_1 + rsize, y_1 - rsize);   // рисуем квадрат
    glutSwapBuffers();
}

void ColorFona(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Reshape(GLsizei w, GLsizei h) {            //эту функцию я честно спиздил
    GLfloat aspectRatio;                           //тк хз как нормально реализовать
    if (h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    aspectRatio = (GLfloat)w / (GLfloat)h;
    if (w <= h) {
        windowWidth = 100;
        windowHeight = 100 / aspectRatio;
        glOrtho(-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
    }
    else {
        windowWidth = 100 * aspectRatio;
        windowHeight = 100;
        glOrtho(-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Upravlenie(int key, int x, int y) {    //управление стрелочками
    switch (key) {
    case GLUT_KEY_UP:
        if (ystep > 0)
            y_1 += ystep;
        else
            y_1 += ystep * -2;
        break;
    case GLUT_KEY_DOWN:
        if (ystep < 0)
            y_1 += ystep;
        else
            y_1 += -ystep * 2;
        break;
    case GLUT_KEY_RIGHT:
        if (xstep > 0)
            x_1 += xstep;
        else
            x_1 += xstep * -2;
        break;
    case GLUT_KEY_LEFT:
        if (xstep < 0)
            x_1 += xstep;
        else
            x_1 += -xstep * 2;
        break;
    }
}

void proverka1() {
    if (x_1 > windowWidth - rsize) {              // проверка на достижение границы окна
        xstep = -xstep; x_1 /= 1.01;  rsize *= koef_1;
    }
    if (x_1 < -windowWidth) {
        xstep = -xstep; x_1 /= 1.01; rsize *= koef_2;
    }
    if (y_1 > windowHeight) {                        
        ystep = -ystep; y_1 /= 1.01; rsize *= koef_1;
    }
    if (y_1 < -windowHeight + rsize) {
        ystep = -ystep; y_1 /= 1.01; rsize *= koef_2;
    }

}

void proverka2() {                              //проверка на выход за границы окна
    if (x_1 > (windowWidth - rsize + xstep))                                                                                                   
        x_1 = windowWidth - rsize - 1;
    else if (x_1 < -(windowWidth + xstep))                                                                                                              
        x_1 = -windowWidth - 1;
    if (y_1 > (windowHeight + ystep))                                                                                                                                
        y_1 = windowHeight - 1;
    else if (y_1 < -(windowHeight - rsize + ystep))
        y_1 = -windowHeight + rsize - 1;
}

void Timer1(int value) {
    if (suka == 0) {
        proverka1();
        x_1 += xstep;   
        y_1 += ystep;
        proverka2();
        glutPostRedisplay(); 
        glutTimerFunc(30, Timer1, 0);  
    }
    else {
        glutSpecialFunc(Upravlenie);
        proverka1();
        proverka2();
        glutPostRedisplay(); 
        glutTimerFunc(30, Timer1, 0);
    }
  
}

void processMenuEvents(int option) {           //менюшка на пкм
    switch (option) {
    case 1:
        suka = 0;
        break;
    case 2:
        suka = 1;
        break;
    case 3:
        exit(0);
        break;
    }
}

void createGLUTMenus() {
    int menu;                                    
    menu = glutCreateMenu(processMenuEvents);   
    glutAddMenuEntry("Flying kvadret", 1);
    glutAddMenuEntry("Uprovlenie kvadretom", 2);
    glutAddMenuEntry("Exit otsedova", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("YOBAniy kvadret");
    glutDisplayFunc(YOBA);
    glutReshapeFunc(Reshape);
    glutTimerFunc(30, Timer1, 0); 
    createGLUTMenus();
    ColorFona();
    glutMainLoop();
    return 0;
}