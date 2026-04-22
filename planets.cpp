#include "platform.h"
#include "globals.h"

void drawPlanetBody(float x, float y, int r, float cr, float cg, float cb) {

    for (int dy = -r; dy <= r; dy++) {
        int w = (int)sqrt(r*r - dy*dy);
        for (int dx = -w; dx <= w; dx++) {
            glColor3f(cr, cg, cb);
            drawPixel(x + dx, y + dy);
        }
    }
}

void drawSaturnRing(float x, float y, int r) {
    for(int i=0; i<720; i++) {
        float a = 2.0f*PI*i/720.0f;
        float cosA = cos(a), sinA = sin(a);
        float baseRx = r * 2.2f, baseRy = r * 0.6f;

        glColor3f(0.9f, 0.8f, 0.6f);
        bresenhamLine((int)(x + cosA*baseRx), (int)(y + sinA*baseRy),
                      (int)(x + cosA*(baseRx-6)), (int)(y + sinA*(baseRy-3)));

        glColor3f(0.7f, 0.6f, 0.4f);
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

