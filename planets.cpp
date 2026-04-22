#include "platform.h"
#include "globals.h"

void drawPlanetBody(float x, float y, int r, float cr, float cg, float cb) {

    for (int dy = -r; dy <= r; dy++) {
        int w = (int)sqrt(r*r - dy*dy);
        for (int dx = -w; dx <= w; dx++) {

            float nx = (float)dx / r;
            float ny = (float)dy / r;
            float nz = sqrt(1.0f - nx*nx - ny*ny);

            float lx = sunX - x;
            float ly = sunY - y;
            float dist = sqrt(lx*lx + ly*ly);
            lx /= dist; ly /= dist;
            float lz = 0.2f; 

            float diff = nx*lx + ny*ly + nz*lz;
            if (diff < 0) diff = 0;

            float ambient = 0.15f;
            float spec = pow(diff, 6.0f) * 0.3f;

            float rc = cr * (ambient + diff * 0.85f) + spec;
            float gc = cg * (ambient + diff * 0.85f) + spec;
            float bc = cb * (ambient + diff * 0.85f) + spec;

            glColor3f(rc > 1.0f ? 1.0f : rc, 
                      gc > 1.0f ? 1.0f : gc, 
                      bc > 1.0f ? 1.0f : bc);
            drawPixel(x + dx, y + dy);
        }
    }
}

void drawSaturnRing(float x, float y, int r) {
    float lx = sunX - x;
    float ly = sunY - y;
    float dist = sqrt(lx*lx + ly*ly);
    lx /= dist; ly /= dist;

    for(int i=0; i<720; i++) {
        float a = 2.0f*PI*i/720.0f;
        float cosA = cos(a), sinA = sin(a);

        float diff = cosA * lx + sinA * ly;
        diff = (diff + 1.0f) * 0.5f;

        float baseRx = r * 2.2f, baseRy = r * 0.6f;

        glColor3f(0.9f*diff, 0.8f*diff, 0.6f*diff);
        bresenhamLine((int)(x + cosA*baseRx), (int)(y + sinA*baseRy),
                      (int)(x + cosA*(baseRx-6)), (int)(y + sinA*(baseRy-3)));

        glColor3f(0.7f*diff, 0.6f*diff, 0.4f*diff);
        bresenhamLine((int)(x + cosA*(baseRx-8)), (int)(y + sinA*(baseRy-4)),
                      (int)(x + cosA*(baseRx-12)), (int)(y + sinA*(baseRy-6)));
    }
}

void drawPlanets() {
    int i;
    for(i=0; i<5; i++) {
        if(!planets[i].alive) continue;
        float px = sunX + cos(planets[i].angle) * planets[i].orbitRadius;
        float py = sunY + sin(planets[i].angle) * planets[i].orbitRadius * 0.55f;
        if(planets[i].ring) drawSaturnRing(px, py, planets[i].r);
        drawPlanetBody(px, py, planets[i].r, planets[i].cr, planets[i].cg, planets[i].cb);
    }
}

void updatePlanets() {
    int i;
    for(i=0; i<5; i++) planets[i].angle += planets[i].speed;
}

void updatePlanetRespawn() {
    int i;
    for(i=0; i<5; i++) {
        if(planets[i].respawnTime > 0) {
            planets[i].respawnTime--;
            if(planets[i].respawnTime == 0) {
                planets[i].alive = 1;
                planets[i].angle = randFloat(0.0f, 2*PI); 
            }
        }
    }
}

