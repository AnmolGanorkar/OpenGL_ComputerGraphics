// DDA Algorithm for line drawing in OpenGL using mouse clicks to draw lines between two points on the screen. Different cases for different slopes and quadrants. (m<1 and m>1) with start and end points data displayed in the console.

#include <GL/glut.h>
#include <iostream>
#include <cmath>

int startX, startY, endX, endY;
bool firstClick = true;

void drawAxis() {
    glColor3f(0.0, 0.0, 0.0); // Black

    glBegin(GL_LINES);
    // X-axis
    glVertex2i(0, 300);
    glVertex2i(800, 300); 

    // Y-axis
    glVertex2i(400, 0); 
    glVertex2i(400, 600); 
    glEnd();
    glFlush();
}

void drawLineDDA(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;

    float slope = (float)dy / dx;
    std::cout << "Slope: " << slope << "\n";

    int steps = std::max(abs(dx), abs(dy)); 

    float xIncrement = dx / (float)steps;
    float yIncrement = dy / (float)steps;

    if (x2 < x1) xIncrement = -xIncrement;
    if (y2 < y1) yIncrement = -yIncrement;

    float x = (float)x1;
    float y = (float)y1;

    glBegin(GL_POINTS);

    for (int i = 0; i <= steps; i++) {
        glVertex2f(x, y); 

        // First quadrant (x1 <= x2, y1 <= y2)
        if (dx >= 0 && dy >= 0) {
            if (slope >= 0 && slope <= 1) { // 0 < m <= 1
                x += xIncrement;
                y += yIncrement;
            }
            else if (slope > 1) { // m > 1
                x += (1 / slope);
                y += yIncrement;
            }
        }
        // Second quadrant (x1 > x2, y1 <= y2)
        else if (dx < 0 && dy >= 0) {
            if (slope > -1 && slope < 0) { // -1 < m < 0
                x -= xIncrement;
                y += yIncrement;
            }
            else if (slope <= -1) { // m <= -1
                x -= (1 / abs(slope));
                y += yIncrement;
            }
        }
        // Third quadrant (x1 > x2, y1 > y2)
        else if (dx < 0 && dy < 0) {
            if (slope >= 0 && slope <= 1) { // 0 < m <= 1
                x -= xIncrement;
                y -= yIncrement;
            }
            else if (slope > 1) { // m > 1
                x -= (1 / slope);
                y -= yIncrement;
            }
        }
        // Fourth quadrant (x1 <= x2, y1 > y2)
        else if (dx >= 0 && dy < 0) {
            if (slope < 0 && slope > -1) { // -1 < m < 0
                x += xIncrement;
                y -= yIncrement;
            }
            else if (slope <= -1) { // m <= -1
                x += (1 / abs(slope));
                y -= yIncrement;
            }
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
    drawAxis();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  // White bg
    glColor3f(0.0, 0.0, 0.0);  // Black lines
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("DDA Algorithm with different cases for different slopes and quadrants");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutMainLoop();
    return 0;
}
