// DDA Algorithm for line drawing in OpenGL using mouse clicks to draw lines between two points on the screen. (m<1 and m>1) optimized for all slopes and quadrants.

#include <GL/glut.h>
#include <iostream>

int startX, startY, endX, endY;
bool firstClick = true;

void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = std::max(abs(dx), abs(dy));

    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;

    float x = (float)x1;
    float y = (float)y1;

    float slope = (float)dy / dx;
    std::cout << "Slope: " << slope << "\n";

    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2i((int)round(x), (int)round(y));

        if (slope < 1) {     //m<1
            x += xIncrement;
            y += yIncrement;
        }
        else {               //m>1
            x += (1 / slope);
            y += yIncrement; 
        }
    }
    glEnd();
    glFlush();
}


void name() {
    glColor3f(0, 0, 0); // black
    glRasterPos2f(10.0f, 580.0f);
    const char* name = "Anmol Ganorkar, SAP - 500108253";
    for (const char* c = name; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
    //glFlush();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (firstClick) {
            startX = x;
            startY = glutGet(GLUT_WINDOW_HEIGHT) - y;
            std::cout << "Start Point: (" << startX << ", " << startY << ")\n";
            firstClick = false;
        }
        else {
            endX = x;
            endY = glutGet(GLUT_WINDOW_HEIGHT) - y;
            std::cout << "End Point: (" << endX << ", " << endY << ")\n";
            firstClick = true;
            drawLineDDA(startX, startY, endX, endY);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    name();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // White bg
    glColor3f(0.0, 0.0, 0.0);  // Black line
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("DDA Algorithm");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    return 0;
}
