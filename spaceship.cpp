#include "platform.h"
#include "globals.h"

void drawSpaceship(float x, float y) {

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glTranslatef(x, y, 0.0f);

    glScalef(1.2f, 1.2f, 1.0f);

    float wiggle = sin(glutGet(GLUT_ELAPSED_TIME) * 0.005f) * 5.0f;
    glRotatef(wiggle, 0, 0, 1);

    float shearMatrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.1f, 1.0f, 0.0f, 0.0f,  
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    glMultMatrixf(shearMatrix);

    float lx = 0;
    float ly = 0;

    int flameLen = randInt(15, 25);
    for (int i=0; i<flameLen; i++) {
        float heat = 1.0f - (float)i/flameLen;
        glColor3f(1.0f, 0.5f * heat, 0.0f);
        int w = (flameLen - i) / 3;
        ddaLine((int)lx-w, (int)ly-12-i, (int)lx+w, (int)ly-12-i); 
    }

    for(int dy = -12; dy <= 5; dy++) {
        int w = 28 - abs(dy+12);
        for(int dx = w; dx >= w-8; dx--) {
            if (dx < 0) continue;
            float shade = 0.5f + (dy+12)*0.02f;
            glColor3f(0.4f*shade, 0.45f*shade, 0.5f*shade);
            drawPixel(lx+dx, ly+dy); 

            float reflectedX = -(lx+dx);
            drawPixel(reflectedX, ly+dy); 
        }
    }

    for (int dy = -15; dy <= 18; dy++) {
        int w = (dy > 0) ? (18 - dy)/2 + 2 : (15 + dy)/3 + 5; 
        for (int dx = -w; dx <= w; dx++) {
            float shade = 1.0f - (float)(dx*dx)/(w*w); 
            glColor3f(0.7f*shade, 0.7f*shade, 0.75f*shade); 
            drawPixel(lx+dx, ly+dy);
        }
    }

    for(int dy = 2; dy <= 10; dy++) {
        int w = 4 - abs(dy - 6)/2;
        for(int dx = -w; dx <= w; dx++) {
            float shade = 1.0f - (float)(dx*dx)/(w*w) + 0.2f;
            glColor3f(0.1f, 0.6f*shade, 1.0f*shade);
            drawPixel(lx+dx, ly+dy);
        }
    }

    glPopMatrix();
}

void checkShipPlanet() {
    int i;
    for(i=0; i<5; i++) {
        if(!planets[i].alive) continue;
        float px = sunX + cos(planets[i].angle) * planets[i].orbitRadius;
        float py = sunY + sin(planets[i].angle) * planets[i].orbitRadius * 0.55f;
        float d = distance2D(ship.x, ship.y, px, py);
        if(d <= ship.size + planets[i].r + 5) {
            createBlast(ship.x, ship.y, (int)px, (int)py);
            ship.x = 130; ship.y = 110;
        }
    }
}

