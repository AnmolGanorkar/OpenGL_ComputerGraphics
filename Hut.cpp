// PROGRAM FOR SIMPLE HUT WITH DAY/NIGHT BG

#include <GL/freeglut.h>
#include <cmath>

bool isDay = true;

void drawSunOrMoon(float x, float y, float radius) {
    if (isDay) {
        glColor3f(1.0f, 0.9f, 0.2f);
    }
    else {
        glColor3f(0.8f, 0.8f, 0.8f);
    }
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 360; i++) {
        float theta = i * (3.14159f / 180.0f);
        glVertex2f(x + radius * cosf(theta), y + radius * sinf(theta));
    }
    glEnd();
}

void drawMountain(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) {
    glColor3f(r, g, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawHut(float x, float y, float width, float height) {

    glColor3f(0.9f, 0.5f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(x - width / 2, y);
    glVertex2f(x + width / 2, y);
    glVertex2f(x + width / 2, y + height / 2);
    glVertex2f(x - width / 2, y + height / 2);
    glEnd();

    glColor3f(0.8f, 0.1f, 0.1f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x - width / 2, y + height / 2);
    glVertex2f(x + width / 2, y + height / 2);
    glVertex2f(x, y + height);
    glEnd();

    glColor3f(1.0f, 0.9f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(x - width / 6, y + height / 3);
    glVertex2f(x - width / 12, y + height / 3);
    glVertex2f(x - width / 12, y + height / 2.5f);
    glVertex2f(x - width / 6, y + height / 2.5f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(x + width / 12, y + height / 3);
    glVertex2f(x + width / 6, y + height / 3);
    glVertex2f(x + width / 6, y + height / 2.5f);
    glVertex2f(x + width / 12, y + height / 2.5f);
    glEnd();

    glColor3f(0.3f, 0.15f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(x - width / 8, y);
    glVertex2f(x + width / 8, y);
    glVertex2f(x + width / 8, y + height / 3);
    glVertex2f(x - width / 8, y + height / 3);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (isDay) {
        glColor3f(0.53f, 0.81f, 0.98f);
    }
    else {
        glColor3f(0.1f, 0.1f, 0.3f);
    }
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(-1.0f, 1.0f);
    glEnd();

    if (isDay) {
        glColor3f(0.3f, 0.8f, 0.3f);
    }
    else {
        glColor3f(0.2f, 0.2f, 0.2f);
    }
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(-1.0f, 0.0f);
    glEnd();


    drawMountain(-1.0f, 0.0f, -0.5f, 0.7f, 0.0f, 0.0f, 0.7f, 0.5f, 0.8f);
    drawMountain(0.0f, 0.0f, 0.5f, 0.7f, 1.0f, 0.0f, 0.7f, 0.5f, 0.8f);

    drawSunOrMoon(0.0f, 0.8f, 0.1f);

    drawHut(0.5f, -0.7f, 0.6f, 0.6f);

    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        float normalizedX = (float)x / glutGet(GLUT_WINDOW_WIDTH) * 2 - 1;
        float normalizedY = 1 - (float)y / windowHeight * 2;

        float sunCenterX = 0.0f;
        float sunCenterY = 0.8f;
        float radius = 0.1f;

        if (sqrt(pow(normalizedX - sunCenterX, 2) + pow(normalizedY - sunCenterY, 2)) <= radius) {
            isDay = !isDay;
            glutPostRedisplay();
        }
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Hut");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

