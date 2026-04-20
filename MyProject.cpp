#include <GL/glut.h>
#include <math.h>

#define WIDTH  800
#define HEIGHT 600
#define PI     3.1415926f

int sunX = WIDTH / 2;
int sunY = HEIGHT / 2;
int sunR = 60;

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void plotCirclePoints(int xc, int yc, int x, int y) {
    drawPixel(xc + x, yc + y); drawPixel(xc - x, yc + y);
    drawPixel(xc + x, yc - y); drawPixel(xc - x, yc - y);
    drawPixel(xc + y, yc + x); drawPixel(xc - y, yc + x);
    drawPixel(xc + y, yc - x); drawPixel(xc - y, yc - x);
}

void midpointCircle(int xc, int yc, int r) {
    int x = 0, y = r, p = 1 - r;
    while (x <= y) {
        plotCirclePoints(xc, yc, x, y);
        x++;
        if (p < 0) p += 2 * x + 1;
        else { y--; p += 2 * (x - y) + 1; }
    }
}

void drawFilledCircle(int xc, int yc, int r) {
    int i;
    for (i = 0; i <= r; i++) midpointCircle(xc, yc, i);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    /* draw sun */
    glColor3f(1.0f, 0.85f, 0.15f);
    drawFilledCircle(sunX, sunY, sunR);

    glutSwapBuffers();
}

void init() {
    glClearColor(0, 0, 0, 1);
    glPointSize(2.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Solar Blast");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}