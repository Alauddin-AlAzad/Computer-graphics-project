#include "platform.h"
#include "globals.h"

float randFloat(float a, float b) {
    return a + (b-a) * ((float)rand() / (float)RAND_MAX);
}

int randInt(int a, int b) {
    return a + rand() % (b - a + 1);
}

float distance2D(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx*dx + dy*dy);
}

void drawText(float x, float y, const char* t) {
    glColor3f(1,1,1);
    glRasterPos2f(x,y);
    while(*t) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *t);
        t++;
    }
}

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

void plotCirclePoints(int xc, int yc, int x, int y) {
    drawPixel(xc+x, yc+y); drawPixel(xc-x, yc+y);
    drawPixel(xc+x, yc-y); drawPixel(xc-x, yc-y);
    drawPixel(xc+y, yc+x); drawPixel(xc-y, yc+x);
    drawPixel(xc+y, yc-x); drawPixel(xc-y, yc-x);
}

void midpointCircle(int xc, int yc, int r) {
    int x=0, y=r, p=1-r;
    while(x <= y) {
        plotCirclePoints(xc, yc, x, y); x++;
        if(p < 0) p += 2*x + 1;
        else { y--; p += 2*(x-y) + 1; }
    }
}

void drawFilledCircleMidpoint(int xc, int yc, int r) {
    int i;
    for(i=0; i<=r; i++) midpointCircle(xc, yc, i);
}

void bresenhamLine(int x1, int y1, int x2, int y2) {
    int dx=abs(x2-x1), dy=abs(y2-y1);
    int sx = (x1<x2)?1:-1, sy = (y1<y2)?1:-1;
    int err=dx-dy, e2;
    while(1) {
        drawPixel(x1,y1);
        if(x1==x2 && y1==y2) break;
        e2 = 2*err;
        if(e2 > -dy) { err -= dy; x1 += sx; }
        if(e2 < dx) { err += dx; y1 += sy; }
    }
}

void ddaLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = x1, y = y1;
    for (int i = 0; i <= steps; i++) {
        drawPixel(round(x), round(y));
        x += xInc;
        y += yInc;
    }
}

void drawEllipse(float cx, float cy, float rx, float ry) {
    int i;
    glBegin(GL_LINE_LOOP);
    for(i=0; i<200; i++) {
        float a = 2.0f * PI * i / 200.0f;
        glVertex2f(cx + cos(a)*rx, cy + sin(a)*ry);
    }
    glEnd();
}

